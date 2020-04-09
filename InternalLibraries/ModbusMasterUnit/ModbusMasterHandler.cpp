#include "ModbusMasterHandler.h"

//------------------------------------------------------------------------------------
//!
ModbusMasterHandler::ModbusMasterHandler(QObject *parent)
                    :QObject(parent)
{
    setObjectName("ModbusMasterHandler");
    //-------------------------------------------


    //-------------------------------------------
    SEND_TO_LOG( QString("%1 - создан").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
ModbusMasterHandler::~ModbusMasterHandler()
{    
    SEND_TO_LOG( QString("%1 - удален").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterHandler::exequteRequest(ModbusRequest *modbusRequest)
{
    //m_curentModbusRequest = request;

    ModbusConnectionSettings modbusConnectionSettings = modbusRequest->connectionSettings();

    setObjectName( QString("ModbusMasterHandler[%1]").arg(modbusConnectionSettings.connectionName) );

    ModbusConnection modbusConnectionType = modbusConnectionSettings.modbusConnectionType;

    modbus_t *ctx = NULL;

    if (modbusConnectionType == ModbusConnection::Serial)
    {
        const char *device  = modbusConnectionSettings.serialPortNameParameter.toLatin1().data();
        int baud            = modbusConnectionSettings.serialBaudRateParameter;
        char parity         = modbusConnectionSettings.serialParityParameter;
        int data_bit        = modbusConnectionSettings.serialDataBitsParameter;
        int stop_bit        = modbusConnectionSettings.serialStopBitsParameter;

        ctx = modbus_new_rtu(device,baud,parity,data_bit,stop_bit);

    } else {
        const char *ip_address  = modbusConnectionSettings.networkAddressParameter.toLatin1().data();
        int port                = modbusConnectionSettings.networkPortParameter;

        ctx = modbus_new_tcp(ip_address, port);

        // Для modbus server (slave)
//        int socket = modbus_tcp_listen(ctx, 1);
//        modbus_tcp_accept(ctx, &socket);
    }

#define BCM_PIN_DE 17
#define BCM_PIN_RE 18

#define REGISTER_ADDRESS 97
#define NO_OF_REGISTERS 1

//    SEND_TO_LOG( QString("%1 - -----------------------------").arg(objectName()) );
//    SEND_TO_LOG( QString("%1 - --- start exequte request ---").arg(objectName()) );

    if (ctx == NULL)
    {
        SEND_TO_LOG( QString("%1 - Unable to allocate libmodbus context").arg(objectName()) );
        emit exequted();
        return;
    }

    //-----------------------------------------------------------------
/*
    qDebug() << "ModbusMasterHandler::exequteRequest"
             << m_curentModbusRequest->objectName();
*/
    //-----------------------------------------------------------------

    //modbus_set_debug(ctx, TRUE);
    modbus_set_debug(ctx, FALSE);

    //modbus_set_error_recovery(ctx, (modbus_error_recovery_mode)(MODBUS_ERROR_RECOVERY_LINK | MODBUS_ERROR_RECOVERY_PROTOCOL));
    //modbus_set_error_recovery(ctx, MODBUS_ERROR_RECOVERY_NONE);

    modbus_set_slave(ctx, modbusRequest->serverAddress());

    uint32_t sec_to = 0;
    uint32_t usec_to = 5*1000;
    modbus_get_response_timeout(ctx, &sec_to, &usec_to);

#ifdef __arm__
    //modbus_enable_rpi(ctx,TRUE);
    //modbus_configure_rpi_bcm_pins(ctx,BCM_PIN_DE,BCM_PIN_RE);
    //modbus_rpi_pin_export_direction(ctx);
#endif // __arm__

    if (modbus_connect(ctx) == -1)
    {
        SEND_TO_LOG( QString("%1 - Connection failed: %2").arg(objectName()).arg(modbus_strerror(errno)) );
        modbus_free(ctx);

        errorHandler(modbusRequest);

        emit exequted();
        return ;
    }

    switch (modbusRequest->functionCode())
    {
        case 0x01: exequteRead<uint8_t>  (ctx, modbusRequest, modbus_read_bits);            break;
        case 0x02: exequteRead<uint8_t>  (ctx, modbusRequest, modbus_read_input_bits);      break;
        case 0x03: exequteRead<uint16_t> (ctx, modbusRequest, modbus_read_registers);       break;
        case 0x04: exequteRead<uint16_t> (ctx, modbusRequest, modbus_read_input_registers); break;
        case 0x05: exequteWrite          (ctx, modbusRequest, modbus_write_bit);            break;
        case 0x06: exequteWrite          (ctx, modbusRequest, modbus_write_register);       break;
        case 0x0F: exequteWrite<uint8_t> (ctx, modbusRequest, modbus_write_bits);           break;
        case 0x10: exequteWrite<uint16_t>(ctx, modbusRequest, modbus_write_registers);      break;

        default:
            SEND_TO_LOG( QString("%1 - Попытка выполнить необрабатываемую функцию [%2]")
                         .arg(objectName()).arg(modbusRequest->functionCode()) );
            break;
    }

    /* Close the connection */
#ifdef __arm__
    //modbus_rpi_pin_unexport_direction(ctx);
#endif // __arm__

    modbus_close(ctx);
    modbus_free(ctx);

    emit exequted();
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterHandler::errorHandler(ModbusRequest *modbusRequest)
{
    SEND_TO_LOG( QString("%1 - errorHandler").arg(objectName()) );

    switch (modbusRequest->functionCode())
    {
        case 0x01: setDataErrorHandler<uint8_t>  (modbusRequest); break;
        case 0x02: setDataErrorHandler<uint8_t>  (modbusRequest); break;
        case 0x03: setDataErrorHandler<uint16_t> (modbusRequest); break;
        case 0x04: setDataErrorHandler<uint16_t> (modbusRequest); break;
//            case 0x05: setDataErrorHandler           (modbusRequest); break;
//            case 0x06: setDataErrorHandler           (modbusRequest); break;
        case 0x0F: setDataErrorHandler<uint8_t>  (modbusRequest); break;
        case 0x10: setDataErrorHandler<uint16_t> (modbusRequest); break;

        default:
            SEND_TO_LOG( QString("%1 - Попытка обработки ошибки неизвестной функции [%2]")
                         .arg(objectName()).arg(modbusRequest->functionCode()) );
            break;
    }
}
//------------------------------------------------------------------------------------
//!
template < typename T >
void ModbusMasterHandler::setDataErrorHandler(ModbusRequest *modbusRequest)
{
    int nb = modbusRequest->number();

    T* dest = (T*) malloc(nb * sizeof(T));
    memset(dest, 0, nb * sizeof(T));

    modbusRequest->setModbusDataComplex<T>(dest, -1);

    free(dest);
}
//------------------------------------------------------------------------------------
//!
template < typename T >
void ModbusMasterHandler::exequteRead(modbus_t *ctx,
                                      ModbusRequest *modbusRequest,
                                      int (*function)(modbus_t*,
                                                      int,
                                                      int,
                                                      T*) )
{
    int addr = modbusRequest->startAddress();
    int nb = modbusRequest->number();

    T* dest = (T*) malloc(nb * sizeof(T));
    memset(dest, 0, nb * sizeof(T));

    int rc = function(ctx, addr, nb, dest);

    modbusRequest->setModbusDataComplex<T>(dest, ((rc == -1) ? -1 : 1));

    free(dest);
}
//------------------------------------------------------------------------------------
//!
template < typename T >
void ModbusMasterHandler::exequteWrite( modbus_t *ctx,
                                        ModbusRequest *modbusRequest,
                                        int (*function)(modbus_t*,
                                                        int,
                                                        int,
                                                        const T*) )
{
    int addr = modbusRequest->startAddress();
    int nb = modbusRequest->number();

    T* dest = modbusRequest->modbusData<T>();

    //-----------
    int rc = function(ctx, addr,nb, dest);
    modbusRequest->setDeviceState( ((rc == -1) ? -1 : 1) );

    //modbusRequest->setModbusDataComplex<T>(dest, (rc == -1) ? -1 : 1);
    //-----------

    free(dest);
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterHandler::exequteWrite( modbus_t *ctx,
                                        ModbusRequest *modbusRequest,
                                        int (*function)(modbus_t*,
                                                        int,
                                                        int) )
{
    Q_UNUSED(ctx);
    Q_UNUSED(modbusRequest);
    Q_UNUSED(function);

    SEND_TO_LOG( QString("%1 - Not used!!!").arg(objectName()) );
    /*
    int addr = modbusRequest->startAddress();

    int dest = *modbusRequest->modbusData<int>();

    int rc = function(ctx, addr, dest);

    modbusRequest->setModbusDataComplex<ModbusDataType_t>(dest, (rc == -1) ? -1 : 1);

    free(dest);
    */
}



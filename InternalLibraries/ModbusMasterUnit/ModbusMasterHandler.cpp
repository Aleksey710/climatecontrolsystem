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
void ModbusMasterHandler::errorDataHandler()
{
    if(m_curentModbusRequest)
    {
        QModbusDataUnit modbusDataUnit = m_curentModbusRequest->modbusDataUnit();
        modbusDataUnit.setValues( QVector<quint16>(modbusDataUnit.valueCount(), std::numeric_limits<quint16>::max()) );
        m_curentModbusRequest->setModbusDataUnit(modbusDataUnit, -1);
    }
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterHandler::exequteRequest(ModbusRequest *request)
{
    m_curentModbusRequest = request;

    ModbusConnectionSettings modbusConnectionSettings = m_curentModbusRequest->connectionSettings();

    setObjectName( QString("ModbusMasterHandler[%1]").arg(modbusConnectionSettings.connectionName) );

    ModbusConnection modbusConnectionType = modbusConnectionSettings.modbusConnectionType;

    modbus_t *ctx = NULL;

    if (modbusConnectionType == ModbusConnection::Serial)
    {
        const char *device = modbusConnectionSettings.serialPortNameParameter.toLatin1().data();
        int baud = modbusConnectionSettings.serialBaudRateParameter;

        char parity;
        switch (modbusConnectionSettings.serialParityParameter)
        {
            case QSerialPort::NoParity:
                parity = 'N';
                break;
            case QSerialPort::EvenParity:
                parity = 'E';
                break;
            case QSerialPort::OddParity:
                parity = 'O';
                break;
            case QSerialPort::SpaceParity:
            case QSerialPort::MarkParity:
            case QSerialPort::UnknownParity:
            default:
                parity = 'x';
                break;
        }

        int data_bit = modbusConnectionSettings.serialDataBitsParameter;
        int stop_bit = modbusConnectionSettings.serialStopBitsParameter;

        ctx = modbus_new_rtu(device,baud,parity,data_bit,stop_bit);

    } else {
        const char *ip_address = modbusConnectionSettings.networkAddressParameter.toLatin1().data();
        int port = modbusConnectionSettings.networkPortParameter;

        ctx = modbus_new_tcp(ip_address, port);
    }

#define BCM_PIN_DE 17
#define BCM_PIN_RE 18

#define REGISTER_ADDRESS 97
#define NO_OF_REGISTERS 1

//    SEND_TO_LOG( QString("%1 - -----------------------------").arg(objectName()) );
//    SEND_TO_LOG( QString("%1 - --- start exequte request ---").arg(objectName()) );

    uint32_t sec_to = 0;
    uint32_t usec_to = 100;

    if (ctx == NULL)
    {
        SEND_TO_LOG( QString("%1 - Unable to allocate libmodbus context").arg(objectName()) );
        emit exequted();
        return;
    }
    modbus_set_debug(ctx, TRUE);
    modbus_set_error_recovery(ctx, (modbus_error_recovery_mode)(MODBUS_ERROR_RECOVERY_LINK | MODBUS_ERROR_RECOVERY_PROTOCOL));
    modbus_set_slave(ctx, m_curentModbusRequest->serverAddress());
    modbus_get_response_timeout(ctx, &sec_to, &usec_to);

#ifdef __arm__
    modbus_enable_rpi(ctx,TRUE);
    modbus_configure_rpi_bcm_pins(ctx,BCM_PIN_DE,BCM_PIN_RE);
    modbus_rpi_pin_export_direction(ctx);
#endif // __arm__

    if (modbus_connect(ctx) == -1)
    {
        SEND_TO_LOG( QString("%1 - Connection failed: %2").arg(objectName()).arg(modbus_strerror(errno)) );
        modbus_free(ctx);

        emit exequted();
        return ;
    }

    QModbusDataUnit &dataUnit = m_curentModbusRequest->modbusDataUnit();

    int addr = dataUnit.startAddress();

    switch (m_curentModbusRequest->functionCode())
    {
        case 0x01: exequteRead<uint8_t>(ctx, dataUnit, modbus_read_bits); break;
        case 0x02: exequteRead<uint8_t>(ctx, dataUnit, modbus_read_input_bits); break;
        case 0x03: exequteRead<uint16_t>(ctx, dataUnit, modbus_read_registers); break;
        case 0x04: exequteRead<uint16_t>(ctx, dataUnit, modbus_read_input_registers); break;
        case 0x05:
        {
            int status = dataUnit.value(0);
            int rc = modbus_write_bit(ctx, addr, status);
        }
            break;
        case 0x06:
        {
            int value = dataUnit.value(0);
            int rc = modbus_write_register(ctx, addr, value);
        }
            break;
        case 0x0F: exequteWrite<uint8_t>(ctx, dataUnit, modbus_write_bits); break;
        case 0x10: exequteWrite<uint16_t>(ctx, dataUnit, modbus_write_registers); break;

        default:
            SEND_TO_LOG( QString("%1 - Попытка выполнить необрабатываемую функцию [%2]")
                         .arg(objectName()).arg(m_curentModbusRequest->functionCode()) );
            break;
    }



    /* Close the connection */
#ifdef __arm__
    modbus_rpi_pin_unexport_direction(ctx);
#endif // __arm__

    modbus_close(ctx);
    modbus_free(ctx);

    emit exequted();
}
//------------------------------------------------------------------------------------
//!
template < typename T >
void ModbusMasterHandler::exequteRead( modbus_t *ctx,
                                       QModbusDataUnit &dataUnit,
                                       int (*function)(modbus_t*,
                                                       int,
                                                       int,
                                                       T*) )
{
    int addr = dataUnit.startAddress();
    int nb = dataUnit.valueCount();

    T* dest = (T*) malloc(nb * sizeof(T));
    memset(dest, 0, nb * sizeof(T));

    int rc = function(ctx, addr,nb, dest);

    if(rc == -1)
    {
        errorDataHandler();
    } else
    {
        for(int i = 0; i < nb; ++i)
        {
            dataUnit.setValue(addr+i, dest[i]);

            SEND_TO_LOG( QString("%1 - received : [%2]-[%3]")
                         .arg(objectName())
                         .arg(addr+i)
                         .arg(dest[i]) );
        }

        m_curentModbusRequest->setModbusDataUnit(dataUnit, 1);
    }

    free(dest);
}
//------------------------------------------------------------------------------------
//!
template < typename T >
void ModbusMasterHandler::exequteWrite( modbus_t *ctx,
                                        QModbusDataUnit &dataUnit,
                                        int (*function)(modbus_t*,
                                                        int,
                                                        int,
                                                        const T*) )
{
    int addr = dataUnit.startAddress();
    int nb = dataUnit.valueCount();

    T* dest = (T*) malloc(nb * sizeof(T));
    memset(dest, 0, nb * sizeof(T));

    int rc = function(ctx, addr,nb, dest);

    if(rc == -1)
    {
        errorDataHandler();
    } else
    {
        for(int i = 0; i < nb; ++i)
        {
            dataUnit.setValue(addr+i, dest[i]);

            SEND_TO_LOG( QString("%1 - transmited : [%2]-[%3]")
                         .arg(objectName())
                         .arg(addr+i)
                         .arg(dest[i]) );
        }

        m_curentModbusRequest->setModbusDataUnit(dataUnit, 1);
    }

    free(dest);
}

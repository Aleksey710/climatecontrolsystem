#include "ModbusSerial.h"

//------------------------------------------------------------------------------------
//!
ModbusSerial::ModbusSerial(const ModbusConnectionAddress &modbusConnectionAddress,
                           QObject *parent)
             :ModbusCore(modbusConnectionAddress, parent)
{
    setObjectName(QStringLiteral("ModbusSerial"));

    m_modbus_backend_type_t = _MODBUS_BACKEND_TYPE_SERIAL;

    set_serial_mode(MODBUS_RTU_RS485);

    //SEND_TO_LOG( QString("%1 - создан ModbusSerial").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
ModbusSerial::~ModbusSerial()
{    
    //SEND_TO_LOG( QString("%1 - удален ModbusSerial").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//! The modbus_rtu_set_serial_mode() function shall set the selected serial mode:
/*
MODBUS_RTU_RS485
MODBUS_RTU_RS232
*/
bool ModbusSerial::set_serial_mode(int mode)
{
    int error;

    error = modbus_serial_set_serial_mode(m_ctx, mode);

/*
    //If the call to ioctl() fails, the error code of ioctl will be returned.

    QString errorStr;
    switch (control)
    {
        case EINVAL:
            errorStr = QStringLiteral("The current libmodbus backend is not RTU");
            break;
        case ENOTSUP:
            errorStr = QStringLiteral("The function is not supported on your platform");
            break;
        default:
            break;
    }
*/
    return error;
}




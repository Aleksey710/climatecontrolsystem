#include "ModbusASCII.h"
//------------------------------------------------------------------------------------
//!
ModbusASCII::ModbusASCII(const ModbusConnectionAddress &modbusConnectionAddress,
                         QObject *parent)
            :ModbusSerial ( modbusConnectionAddress, parent )
{
    setObjectName(QStringLiteral("ModbusASCII[%1]").arg(modbusConnectionAddress.device));

    SEND_TO_LOG( QString("%1 - создан").arg(objectName()) );

    m_modbus_backend_type_t = _MODBUS_BACKEND_TYPE_SERIAL;

    init();
}
//------------------------------------------------------------------------------------
//!
ModbusASCII::~ModbusASCII()
{
    SEND_TO_LOG( QString("%1 - удален").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
bool ModbusASCII::mb_create()
{
    if(m_modbusConnectionAddress.type != ASCII)
    {
        return false;
    }

    m_ctx = modbus_new_ascii(m_modbusConnectionAddress.device,
                             m_modbusConnectionAddress.baud,
                             m_modbusConnectionAddress.parity,
                             m_modbusConnectionAddress.data_bit,
                             m_modbusConnectionAddress.stop_bit);

    if (m_ctx == NULL)
    {
        SEND_TO_LOG( QString("%1 - %2")
                     .arg(objectName())
                     .arg(QStringLiteral("Unable to create the libmodbus ASCII context")) );
        return false;
    } else
    {
        SEND_TO_LOG( QString("%1 - %2")
                     .arg(objectName())
                     .arg(QStringLiteral("libmodbus ASCII context created;")) );
    }

    set_serial_mode(MODBUS_RTU_RS485);

    commonInit();

    return true;
}
//------------------------------------------------------------------------------------
//!




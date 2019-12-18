#include "ModbusRTU.h"

//------------------------------------------------------------------------------------
//!
ModbusRTU::ModbusRTU(const ModbusConnectionAddress &modbusConnectionAddress,
                     QObject *parent)
          :ModbusSerial ( modbusConnectionAddress, parent )
{
    setObjectName(QString("ModbusRTU[%1]").arg(modbusConnectionAddress.device));

    //SEND_TO_LOG( QString("%1 - создан (%2)").arg(objectName()).arg( (quint64)thread() ) );

    m_modbus_backend_type_t = _MODBUS_BACKEND_TYPE_SERIAL;

    init();        
}
//------------------------------------------------------------------------------------
//!
ModbusRTU::~ModbusRTU()
{
    //SEND_TO_LOG( QString("%1 - удален (%2)").arg(objectName()).arg( (quint64)thread() ) );
}
//------------------------------------------------------------------------------------
//!
bool ModbusRTU::mb_create()
{
    if(m_modbusConnectionAddress.type != RTU)
    {
        return false;
    }

    m_ctx = modbus_new_rtu(m_modbusConnectionAddress.device,
                           m_modbusConnectionAddress.baud,
                           m_modbusConnectionAddress.parity,
                           m_modbusConnectionAddress.data_bit,
                           m_modbusConnectionAddress.stop_bit);

    if (m_ctx == nullptr)
    {
        SEND_TO_LOG( QString("%1 - %2")
                     .arg(objectName())
                     .arg(QStringLiteral("Unable to create the libmodbus RTU context")) );
        return false;
    }

    commonInit();

    set_serial_mode(MODBUS_RTU_RS485);

    return true;
}
//------------------------------------------------------------------------------------




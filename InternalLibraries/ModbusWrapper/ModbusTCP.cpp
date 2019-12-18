#include "ModbusTCP.h"

//------------------------------------------------------------------------------------
//!
ModbusTCP::ModbusTCP(const ModbusConnectionAddress &modbusConnectionAddress,
                     QObject *parent)
          :ModbusCore(modbusConnectionAddress, parent)
{
    setObjectName(QStringLiteral("ModbusTCP"));
    //SEND_TO_LOG( QString("%1 - создан (%2)").arg(objectName()).arg( (quint64)thread() ) );

    m_modbus_backend_type_t = _MODBUS_BACKEND_TYPE_TCP;

    init();
}
//------------------------------------------------------------------------------------
//!
ModbusTCP::~ModbusTCP()
{
    //SEND_TO_LOG( QString("%1 - удален (%2)").arg(objectName()).arg( (quint64)thread() ) );
}
//------------------------------------------------------------------------------------
//!
bool ModbusTCP::mb_create()
{
    //qDebug() << "ModbusTCP::mb_create()";

    if(m_modbusConnectionAddress.type != TCP)
    {
        return false;
    }

    m_ctx = modbus_new_tcp(m_modbusConnectionAddress.ip,
                           m_modbusConnectionAddress.port);

//    m_modbusConnectionAddress.s = modbus_tcp_listen(m_ctx, 1);
//    modbus_tcp_accept(m_ctx, &m_modbusConnectionAddress.s);

    if (m_ctx == NULL)
    {
        SEND_TO_LOG( QString("%1 - %2")
                     .arg(objectName())
                     .arg(QStringLiteral("Unable to create the libmodbus TCP context")) );
        return false;
    }

    commonInit();

    return true;
}

#include "ModbusCore.h"
//------------------------------------------------------------------------------------
//!
ModbusCore::ModbusCore(const ModbusConnectionAddress &modbusConnectionAddress,
                       QObject *parent)
           :QObject ( parent ),
            m_ctx( Q_NULLPTR ),
            m_modbus_backend_type_t( _MODBUS_BACKEND_TYPE_SERIAL ),
            m_modbusConnectionAddress ( modbusConnectionAddress ),
            m_slaveAddress ( MODBUS_TCP_SLAVE ),
            m_responseTimeout_ms ( 10 )
{
    setObjectName(QStringLiteral("ModbusCore"));
    //SEND_TO_LOG( QString("%1 - создан ModbusCore (%2)").arg(objectName()).arg( (quint64)thread() ) );

    //setResponseTimeoutUsec(20*1000);
}
//------------------------------------------------------------------------------------
//!
ModbusCore::~ModbusCore()
{
    mb_disconnnect();

    //SEND_TO_LOG( QString("%1 - удален ModbusCore (%2)").arg(objectName()).arg( (quint64)thread() ));
}
//------------------------------------------------------------------------------------
//!
bool ModbusCore::mb_connect()
{
    //qDebug() << "ModbusCore::mb_connect()";

    if (modbus_connect(m_ctx) == -1)
    {
        SEND_TO_LOG( QString("%1 - Connection failed: cod%2 (%3)")
                     .arg(objectName())
                     .arg(errno)
                     .arg(modbus_strerror(errno)) );

        modbus_close(m_ctx);
        modbus_free(m_ctx);
        m_ctx = Q_NULLPTR;
        return false;
    }

    return true;
}
//------------------------------------------------------------------------------------
//!
void ModbusCore::mb_disconnnect()
{
    //SEND_TO_LOG( QString("%1 - mb_disconnnect").arg(objectName()) );

    modbus_close(m_ctx);
    modbus_free(m_ctx);
    m_ctx = Q_NULLPTR;
}
//------------------------------------------------------------------------------------
//!
void ModbusCore::commonInit()
{
//    modbus_set_error_recovery(m_ctx,
//                              //MODBUS_ERROR_RECOVERY_LINK
//                              | MODBUS_ERROR_RECOVERY_PROTOCOL
//                              );

    if(m_ctx == Q_NULLPTR)
    {
        return;
    }

    modbus_set_response_timeout(m_ctx, 0, m_responseTimeout_ms*1000);

    modbus_set_slave(m_ctx, m_slaveAddress);

    //modbus_set_debug(m_ctx, true);

    if(errno)
    {
        // "Недопустимый аргумент" - название ошибки
        //SEND_TO_LOG( QString("%1 - commonInit - [%2] errno(%3)").arg(objectName()).arg(modbus_strerror(errno)).arg(errno) );
    } else
    {
        SEND_TO_LOG( QString("%1 - commonInit: responseTimeout_ms[%2], slaveAddress[%3]")
                     .arg(objectName()).arg(m_responseTimeout_ms).arg(m_slaveAddress) );
    }
}

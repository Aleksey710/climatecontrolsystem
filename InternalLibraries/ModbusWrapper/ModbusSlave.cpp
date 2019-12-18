#include "ModbusSlave.h"
//------------------------------------------------------------------------------------
//!
ModbusSlave::ModbusSlave(const QString &coreType,
                         const ModbusConnectionAddress &modbusConnectionAddress,
                         QObject *parent)
            :ModbusPartner(coreType, modbusConnectionAddress, parent),
             m_mb_mapping ( NULL ),
             m_query ( NULL )
{
    setObjectName(QString("ModbusSlave[%1]").arg("type"));

    /*
    if (use_backend == TCP) {
            ctx = modbus_new_tcp("127.0.0.1", 1502);
            s = modbus_tcp_listen(ctx, 1);
            modbus_tcp_accept(ctx, &s);

        } else {
            ctx = modbus_new_rtu("/dev/ttyUSB0", 115200, 'N', 8, 1);
            modbus_set_slave(ctx, 1);
            modbus_connect(ctx);
        }

    modbus_set_slave(ctx, 1);
    */

    //initData();

    //-------------------------------------------
    SEND_TO_LOG( QString("%1 - создан (%2)").arg(objectName()).arg( (quint64)thread() ) );
}
//------------------------------------------------------------------------------------
//!
ModbusSlave::~ModbusSlave()
{
//    /* Close the connection */
//    modbus_close(m_ctx);
//    modbus_free(m_ctx);

    //-------------------------------------------
    SEND_TO_LOG( QString("%1 - удален (%2)").arg(objectName()).arg( (quint64)thread() ) );
}
//------------------------------------------------------------------------------------
//!
void ModbusSlave::postInit()
{

}
//------------------------------------------------------------------------------------
//!
void ModbusSlave::loop()
{
    modbus_t *ctx = m_modbusCore->modbus();

    for(;;)
    {
        //! Прием данных запроса
        do {
            //qDebug() << "query: " << QByteArray((const char*)query, MODBUS_TCP_MAX_ADU_LENGTH);
            m_rc = modbus_receive(ctx, m_query);
            // Filtered queries return 0
        } while (m_rc == 0);

        //---------------------------------------------------------------------------------------
        // Если соединение не закрывается на ошибках, которые требуются при ответе, например, о плохом CRC в RTU
        if (m_rc == -1 &&
            errno != EMBBADCRC)
        {
            // Quit
            SEND_TO_LOG( QString("Connection closed by the client or error") );
            break;
        }

        //---------------------------------------------------------------------------------------
        //qDebug() << "modbus_reply(ctx, m_query, rc, mb_mapping);";

        m_rc = modbus_reply(ctx, m_query, m_rc, m_mb_mapping);

        if (m_rc == -1)
        {
            break;
        }
    }
}
//------------------------------------------------------------------------------------
//!

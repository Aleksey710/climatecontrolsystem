#include "ModbusMasterConnection.h"

//------------------------------------------------------------------------------------
//!
ModbusMasterConnection::ModbusMasterConnection(const QString &coreType,
                                               const ModbusConnectionAddress &modbusConnectionAddress,
                                               QObject *parent)
                       :QObject(parent),
                        m_coreType ( coreType ),
                        m_modbusConnectionAddress ( modbusConnectionAddress )
{
    setObjectName(QString("ModbusMasterConnection[%1]").arg(coreType));

    //-------------------------------------------
    //! Тестовое !!!
//    connect(this, &ModbusMasterConnection::newData,
//            [](const ModbusData &data, int slaveAddress){
//        qDebug() << "ModbusMasterConnection::testSlotNewData" << data.data << "from" << slaveAddress;
//    });
    //-------------------------------------------

    //SEND_TO_LOG( QString("%1 - создан (%2)").arg(objectName()).arg( (quint64)thread() ) )
}
//------------------------------------------------------------------------------------
//!
ModbusMasterConnection::~ModbusMasterConnection()
{    
    /*
    ModbusRequester *modbusRequester;

    while (!m_modbusRequesterList.isEmpty())
    {
        modbusRequester = m_modbusRequesterList.takeFirst();
        modbusRequester->stop();
        //modbusRequester->deleteLater();
    }
    */

    SEND_TO_LOG( QString("%1 - удален (%2)").arg(objectName()).arg( (quint64)thread() ) )
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterConnection::init()
{
    //SEND_TO_LOG( QString("%1 - инициализация начата (%2)").arg(objectName()).arg( (quint64)thread() ) );
    //-------------------------------------------

    m_modbusMaster = new ModbusMaster(m_coreType, m_modbusConnectionAddress, this);

    m_modbusMaster->reinit();

    //-------------------------------------------
    //SEND_TO_LOG( QString("%1 - инициализация окончена (%2)").arg(objectName()).arg( (quint64)thread() ) );
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterConnection::addRequester(const ModbusRequest &modbusRequest, int period)
{
    //SEND_TO_LOG( QString("%1 - addRequester (%2)").arg(objectName()).arg( (quint64)thread() ) );

    ModbusRequester *modbusRequester = new ModbusRequester(modbusRequest, period, m_modbusMaster, this);

    uint32_t responseTimeout_ms = modbusRequest.responseTimeout_ms;

    //! x*1000 ms!!!
    //! Задается в микросекундах mk = ms*1000
    m_modbusMaster->setResponseTimeoutUsec(responseTimeout_ms*1000);

    m_modbusRequesterList.append(modbusRequester);

    connect(modbusRequester, &ModbusRequester::newTask,
            [=]( ModbusRequest *modbusRequest ){

        //! Если очередь пуста - сразу исполнять
        if(m_requestQueue.isEmpty())
        {
            QMutexLocker locker(&m_mutex);
            {
                //Приостановка работы на  x(*1000) миллисекунд
                usleep (PAUSE_BETWEEN_REQUESTS_MS * 1000);
                //usleep (1000);

                ModbusData data = m_modbusMaster->executeRequest(*modbusRequest);

                emit newData(data, modbusRequest->slaveAddress);
            }
            return;
        }

        m_requestQueue.enqueue(modbusRequest);

        if(m_requestQueue.size() > 5)
        {
            m_requestQueue.clear();
            SEND_TO_LOG( QString("%1 - queue overhead!!! (size > 5) (%2)").arg(objectName()).arg( (quint64)thread() ) );
        }

        executeTask();
    });

    connect(modbusRequester, &ModbusRequester::newData,
            this, &ModbusMasterConnection::newData);

    modbusRequester->start();
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterConnection::executeTask()
{
    while( !m_requestQueue.isEmpty() )
    {
        ModbusRequest *modbusRequest = m_requestQueue.dequeue();

        //SEND_TO_LOG( QString("%1 - executeTask (%2)").arg(objectName()).arg( (quint64)thread() ) );

        if(modbusRequest)
        {
            QMutexLocker locker(&m_mutex);
            {
                //Приостановка работы на  x(*1000) миллисекунд
                usleep (PAUSE_BETWEEN_REQUESTS_MS * 1000);

                ModbusData data = m_modbusMaster->executeRequest(*modbusRequest);

                emit newData(data, modbusRequest->slaveAddress);
            }
        }

        executeTask();
    }
}


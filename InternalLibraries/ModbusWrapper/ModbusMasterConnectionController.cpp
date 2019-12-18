#include "ModbusMasterConnectionController.h"
//------------------------------------------------------------------------------------
//!
ModbusMasterConnectionController::ModbusMasterConnectionController(const QString &coreType,
                                                                   const ModbusConnectionAddress &modbusConnectionAddress,
                                                                   QObject *parent)
                                 :QObject(parent),
                                  m_modbusMasterConnection ( Q_NULLPTR )
{
    setObjectName(QString("ModbusMasterConnectionController[%1]").arg(coreType));    
    //SEND_TO_LOG( QString("%1 - создан (%2)").arg(objectName()).arg( reinterpret_cast<quint64>( thread()->currentThreadId() ) ) );
    //-------------------------------------------

    qRegisterMetaType<ModbusRequest>("ModbusRequest");
    qRegisterMetaType<ModbusData>("ModbusData");
    qRegisterMetaType< QVector<uint16_t> >("QVector<uint16_t>");

    //-------------------------------------------
    m_modbusMasterConnection = new ModbusMasterConnection(coreType, modbusConnectionAddress);

    m_modbusMasterConnection->moveToThread(&m_workerThread);

    connect(&m_workerThread, &QThread::started,
            m_modbusMasterConnection, &ModbusMasterConnection::init);

    connect(&m_workerThread, &QThread::finished,
            m_modbusMasterConnection, &QObject::deleteLater);

    //-------------------------------------------
    connect(this, &ModbusMasterConnectionController::addRequester,
            m_modbusMasterConnection, &ModbusMasterConnection::addRequester);

    connect(m_modbusMasterConnection, &ModbusMasterConnection::newData,
            this, &ModbusMasterConnectionController::newData);

    //-------------------------------------------
    //! Тестовое !!!
//    connect(this, &ModbusMasterConnectionController::newData,
//            [](const ModbusData &data, int slaveAddress){
//        qDebug() << "ModbusMasterConnectionController::testSlotNewData" << data.data << "from" << slaveAddress;
//    });
    //-------------------------------------------

    //SEND_TO_LOG( QString("%1 - запуск потока (%2)").arg(objectName()).arg( (quint64)thread() ) );
    m_workerThread.start();
    //SEND_TO_LOG( QString("%1 - поток [%2] запущен").arg(objectName()).arg( (quint64)(&m_workerThread) ) );

    //    SEND_TO_LOG( QString("%1 - перенесен и запущен(%2)")
//                 .arg(m_modbusMasterConnection->objectName())
//                 .arg( (quint64)m_modbusMasterConnection->thread() ) );
}
//------------------------------------------------------------------------------------
//!
ModbusMasterConnectionController::~ModbusMasterConnectionController()
{
    m_workerThread.quit();
    m_workerThread.wait();

    //-------------------------------------------
    SEND_TO_LOG( QString("%1 - удален (%2)").arg(objectName()).arg( reinterpret_cast<quint64>( thread()->currentThreadId() ) ) );
}
//------------------------------------------------------------------------------------
//!
//void ModbusMasterConnectionController::addRequester(const ModbusRequest &modbusRequest,
//                                                    int period)
//{
//    QMetaObject::invokeMethod(m_modbusMasterConnection,
//                              //reinterpret_cast<QObject*>(m_modbusConnection),
//                              "addRequester",
//                              Qt::QueuedConnection,
//                              Q_ARG(ModbusRequest, modbusRequest),
//                              Q_ARG(int, period));
//}







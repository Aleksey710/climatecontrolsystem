#include "ModbusPartner.h"

//------------------------------------------------------------------------------------
//!
ModbusPartner::ModbusPartner(const QString &coreType,
                             const ModbusConnectionAddress &modbusConnectionAddress,
                             QObject *parent)
              :QObject(parent),
               m_modbusCore ( Q_NULLPTR ),
               m_coreType(coreType),
               m_modbusConnectionAddress ( modbusConnectionAddress ),
               m_reinitCount ( 0 ),
               m_maskLogReinit ( false )
{
    setObjectName(QString("ModbusPartner[%1]").arg(coreType));
    //SEND_TO_LOG( QString("%1 - создан ModbusPartner (%2)").arg(objectName()).arg( (quint64)thread() ) );


    m_modbusCoreFactory.addType<ModbusRTU>  ("RTU");
    m_modbusCoreFactory.addType<ModbusASCII>("ASCII");
    m_modbusCoreFactory.addType<ModbusTCP>  ("TCP");

}
//------------------------------------------------------------------------------------
//!
ModbusPartner::~ModbusPartner()
{    
    m_modbusCoreThread.quit();
    m_modbusCoreThread.wait();

    //SEND_TO_LOG( QString("%1 - удален ModbusPartner (%2)").arg(objectName()).arg( (quint64)thread() ) );
}
//------------------------------------------------------------------------------------
//!
void ModbusPartner::reinit()
{
    //! Увеличить счетчик переподключений
    m_reinitCount++;

    //qDebug() << "ModbusPartner::reinit()" << m_reinitCount << MAX_REINIT_NUMBER_WRITING;

    //! Если счетчик переподключений превысил
    //! количество разрешенных сообщений в лог
    if(m_reinitCount > MAX_REINIT_NUMBER_WRITING)
    {
        //!
        m_reinitCount = MAX_REINIT_NUMBER_WRITING+1;

        m_maskLogReinit = true;

        /*
            Добавить механизм маскирования
        */
    }

    //! Если нет указания маскировать вывод в лог
    if ( !m_maskLogReinit )
    {
        //! Сделать запись в лог
        SEND_TO_LOG( QString("%1 - reinit (%2) count: (%3)").arg(objectName()).arg( (quint64)thread() ).arg(m_reinitCount) );
    }

    //! Если модбас ядро не очищено
    if(m_modbusCore != Q_NULLPTR)
    {
        m_modbusCore->deleteLater();
        //m_modbusCoreThread.wait();
        m_modbusCore = Q_NULLPTR;
    }

    //! Получить новый экземпляр ядра
    m_modbusCore = m_modbusCoreFactory.createInstance(m_coreType, m_modbusConnectionAddress);

    //! Переместить я дро в поток
    m_modbusCore->moveToThread( &m_modbusCoreThread );

    //! При окончании работы потока - удалить ядро
    connect(&m_modbusCoreThread, &QThread::finished, m_modbusCore, &QObject::deleteLater);

    //! Запустить работу потока ядра
    m_modbusCoreThread.start();
}

#ifndef MODBUSREQUESTER_H
#define MODBUSREQUESTER_H
//------------------------------------------------------------------------------------
#include <functional>
#include <QObject>
#include <QTimer>


#include "ModbusMaster.h"
#include "ModbusRequest.h"
//------------------------------------------------------------------------------------
//!
class ModbusRequester : public QObject
{
        Q_OBJECT
    public:
        inline explicit ModbusRequester(const ModbusRequest &modbusRequest,
                                        int period,
                                        ModbusMaster *modbusMaster,
                                        QObject *parent = nullptr)
            :QObject(parent),
             m_modbusMaster ( modbusMaster ),
             m_modbusRequest ( modbusRequest ),
             m_period ( period ),
             m_timer ( new QTimer(this) )
        {
            setObjectName(QString("ModbusRequester[%1 slave addr: %2 period: %3]")
                          .arg(modbusMaster->objectName())
                          .arg(modbusRequest.slaveAddress)
                          .arg(period));

            //SEND_TO_LOG( QString("%1 - создан (%2)").arg(objectName()).arg( (quint64)thread() ) );

            connect(m_timer, &QTimer::timeout,
                    [=](){
                emit newTask( &m_modbusRequest );
            });
        }

        //-------------------------------------------
        inline virtual ~ModbusRequester()
        {
            SEND_TO_LOG( QString("%1 - удален (%2)").arg(objectName()).arg( (quint64)thread() ) );
        }

        //-------------------------------------------
        inline void start()
        {
            SEND_TO_LOG( QString("%1 - запущен (%2)").arg(objectName()).arg( (quint64)thread() ) );
            m_timer->start(m_period);
        }

        //-------------------------------------------
        inline void stop()
        {            
            m_timer->stop();
            SEND_TO_LOG( QString("%1 - остановлен (%2)").arg(objectName()).arg( (quint64)thread() ) );
        }


    signals:
        //void newTask(std::function<void()> *task);
        void newTask(ModbusRequest *modbusRequest);

        void newData(const ModbusData &data,
                     int slaveAddress);

    public slots:



    private slots:


    private:
        ModbusMaster *m_modbusMaster;

        ModbusRequest m_modbusRequest;
        int m_period;
        QTimer *m_timer;

        std::function<void()>          m_task;
};
//------------------------------------------------------------------------------------
#endif // MODBUSREQUESTER_H

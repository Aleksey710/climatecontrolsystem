#ifndef MODBUSCONNECTIONCONTROLLER_H
#define MODBUSCONNECTIONCONTROLLER_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QThread>

#include "ModbusConnectionSettings.h"
//------------------------------------------------------------------------------------
//!
class ModbusConnectionController : public QThread
{
        Q_OBJECT

    public:
        ModbusConnectionController(const ModbusConnectionSettings &modbusConnectionSettings)
            :m_modbusConnectionSettings ( modbusConnectionSettings )
        {
//            ModbusConnectionInterrogator *interrogator
//                = new ModbusConnectionInterrogator(modbusConnectionSettings);

//            interrogator->moveToThread(&m_thread);

//            connect(&m_thread, &QThread::finished,
//                    interrogator, &QObject::deleteLater);

//            connect(this, &ModbusConnectionController::operate,
//                    interrogator, &ModbusConnectionInterrogator::doWork);

//            connect(interrogator, &ModbusConnectionInterrogator::resultReady,
//                    this, &ModbusConnectionController::handleResults);

//            m_thread.start();
        }

        ~ModbusConnectionController()
        {
//            m_thread.quit();
//            m_thread.wait();
        }

        void run() override
        {
            QString result;
                      /* ... here is the expensive or blocking operation ... */
                      emit resultReady(result);
        }

    public slots:
        //void handleResults(const QString &);

    signals:
          void resultReady(const QString &s);

    private:
          ModbusConnectionSettings m_modbusConnectionSettings;

          //ModbusMasterHandler m_modbusMasterHandler;

          //QList<ModbusRequest> m_requestList;
};
//------------------------------------------------------------------------------------
#endif // MODBUSCONNECTIONCONTROLLER_H

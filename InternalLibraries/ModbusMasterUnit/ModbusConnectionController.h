#ifndef MODBUSCONNECTIONCONTROLLER_H
#define MODBUSCONNECTIONCONTROLLER_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QThread>

#include "ModbusConnectionInterrogator.h"
//------------------------------------------------------------------------------------
//!
class ModbusConnectionController : public QObject
{
        Q_OBJECT

    public:
        ModbusConnectionController(const ModbusConnectionSettings &modbusConnectionSettings)
        {
            ModbusConnectionInterrogator *interrogator
                = new ModbusConnectionInterrogator(modbusConnectionSettings);

            interrogator->moveToThread(&m_thread);

            connect(&m_thread, &QThread::finished,
                    interrogator, &QObject::deleteLater);

//            connect(this, &ModbusConnectionController::operate,
//                    interrogator, &ModbusConnectionInterrogator::doWork);

//            connect(interrogator, &ModbusConnectionInterrogator::resultReady,
//                    this, &ModbusConnectionController::handleResults);

            m_thread.start();
        }

        ~ModbusConnectionController()
        {
            m_thread.quit();
            m_thread.wait();
        }

    public slots:
        //void handleResults(const QString &);

    signals:
        //void operate(const QString &);

    private:
        QThread m_thread;
};
//------------------------------------------------------------------------------------
#endif // MODBUSCONNECTIONCONTROLLER_H

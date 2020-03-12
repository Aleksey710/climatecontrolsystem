#ifndef MODBUSTHREADCONTROLLER_H
#define MODBUSTHREADCONTROLLER_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QThread>

#include "Log.h"
#include "ModbusMasterHandler.h"
#include "ModbusRequest.h"
//#include ".h"
//#include ".h"
//#include ".h"
//#include ".h"
//------------------------------------------------------------------------------------
//!
class ModbusThreadController : public QObject
{
        Q_OBJECT
    public:
        explicit ModbusThreadController(QObject *parent = nullptr);
        virtual ~ModbusThreadController();

    public slots:
        void exequteRequest(ModbusRequest *request)
            { emit operate(request); }

    signals:
        void exequted();
        void operate(ModbusRequest *request);

    private:
        QThread m_workerThread;
};
//------------------------------------------------------------------------------------
#endif // MODBUSTHREADCONTROLLER_H

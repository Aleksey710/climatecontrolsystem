#ifndef MODBUSMASTERCONNECTIONCONTROLLER_H
#define MODBUSMASTERCONNECTIONCONTROLLER_H
//------------------------------------------------------------------------------------
#include <functional>
#include <QObject>
#include "modbus.h"
#include <QVector>
#include <QMetaMethod>
#include <QMetaObject>
#include <QThread>
//#include <>
//#include <>
//#include <>


//#include ""
//#include ""
//#include ""

#include "Log.h"
#include "ModbusConsts.h"
#include "ModbusMasterConnection.h"
#include "ModbusRequest.h"
#include "ModbusData.h"
//------------------------------------------------------------------------------------
//!
class ModbusMasterConnectionController : public QObject
{
        Q_OBJECT
    public:
        explicit ModbusMasterConnectionController(const QString &coreType,
                                                  const ModbusConnectionAddress &modbusConnectionAddress,
                                                  QObject *parent = nullptr);

        virtual ~ModbusMasterConnectionController();



    public slots:
        //void addRequester(const ModbusRequest &modbusRequest, int period);

    signals:
        void addRequester(const ModbusRequest &modbusRequest,int period);

        void newData(const ModbusData &data, int slaveAddress);

    private slots:


    private:
        QThread m_workerThread;

        ModbusMasterConnection *m_modbusMasterConnection;


};
//------------------------------------------------------------------------------------
//!
#endif // MODBUSMASTERCONNECTIONCONTROLLER_H

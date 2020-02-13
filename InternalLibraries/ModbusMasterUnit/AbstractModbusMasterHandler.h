#ifndef ABSTRACTMODBUSMASTERHANDLER_H
#define ABSTRACTMODBUSMASTERHANDLER_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QModbusDataUnit>
#include <QModbusReply>
#include <QModbusClient>
#include <QModbusTcpClient>
#include <QModbusRtuSerialMaster>
#include <QUrl>
#include <QSerialPort>
#include <QThread>
//#include <>

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <modbus.h>


#include "Log.h"
#include "ModbusConnection.h"
#include "ModbusConnectionSettings.h"
#include "ModbusRequest.h"
//------------------------------------------------------------------------------------
//!
class AbstractModbusMasterHandler : public QObject
{
        Q_OBJECT
    public:
        explicit AbstractModbusMasterHandler(QObject *parent = nullptr);
        virtual ~AbstractModbusMasterHandler();

    signals:
        void exequted();

    public slots:
        virtual void exequteRequest(ModbusRequest *request) = 0;

    protected:
        virtual void errorDataHandler();


    protected:
        ModbusRequest *m_curentModbusRequest;
};
//------------------------------------------------------------------------------------
#endif // ABSTRACTMODBUSMASTERHANDLER_H

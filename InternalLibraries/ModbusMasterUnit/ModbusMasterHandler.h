#ifndef MODBUSMASTERHANDLER_H
#define MODBUSMASTERHANDLER_H
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


#include "Log.h"
#include "ModbusConnection.h"
#include "ModbusConnectionSettings.h"
#include "ModbusRequest.h"
//#include ""

#include "LibmodbusModbusMasterHandler.h"
#include "NativeModbusMasterHandler.h"
#include "ModbusMaster485Handler.h"
//------------------------------------------------------------------------------------
//!
//class ModbusMasterHandler : public NativeModbusMasterHandler
class ModbusMasterHandler : public LibmodbusModbusMasterHandler
//class ModbusMasterHandler : public ModbusMaster485Handler
{
        Q_OBJECT
    public:
        explicit ModbusMasterHandler(QObject *parent = nullptr);

        virtual ~ModbusMasterHandler();

};
//------------------------------------------------------------------------------------
#endif // MODBUSMASTERHANDLER_H

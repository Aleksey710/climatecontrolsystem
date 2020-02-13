#ifndef LIBMODBUSMODBUSMASTERHANDLER_H
#define LIBMODBUSMODBUSMASTERHANDLER_H
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
#include "AbstractModbusMasterHandler.h"


//------------------------------------------------------------------------------------
//!
class LibmodbusModbusMasterHandler : public AbstractModbusMasterHandler
{
        Q_OBJECT
    public:
        explicit LibmodbusModbusMasterHandler(QObject *parent = nullptr);
        virtual ~LibmodbusModbusMasterHandler();



    public slots:
        virtual void exequteRequest(ModbusRequest *request);


    private slots:
        bool reconnect(const ModbusConnectionSettings &modbusConnectionSettings);

        void readRequest(const int serverAddress, QModbusDataUnit &readDataUnit);
        void writeRequest(const int serverAddress, QModbusDataUnit &writeDataUnit);
        void readWriteRequest(const int serverAddress,
                              QModbusDataUnit &readDataUnit,
                              QModbusDataUnit &writeDataUnit);

    private:
        void deleteModbusDevice();
        void requestExecutionErrorHandler();

    private:



};
//------------------------------------------------------------------------------------
#endif // LIBMODBUSMODBUSMASTERHANDLER_H

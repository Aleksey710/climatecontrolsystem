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


    private:
        template < typename T >
        void exequteRead( modbus_t *ctx,
                          QModbusDataUnit &dataUnit,
                          int (*function)(modbus_t*,
                                          int,
                                          int,
                                          T*) );

        template < typename T >
        void exequteWrite( modbus_t *ctx,
                           QModbusDataUnit &dataUnit,
                           int (*function)(modbus_t*,
                                           int,
                                           int,
                                           const T*) );


    private:



};
//------------------------------------------------------------------------------------
#endif // LIBMODBUSMODBUSMASTERHANDLER_H

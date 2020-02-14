#ifndef MODBUSMASTERHANDLER_H
#define MODBUSMASTERHANDLER_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QUrl>
#include <QModbusDataUnit>

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
//#include ""

//------------------------------------------------------------------------------------
//!
class ModbusMasterHandler : public QObject
{
        Q_OBJECT
    public:
        explicit ModbusMasterHandler(QObject *parent = nullptr);

        virtual ~ModbusMasterHandler();

    signals:
        void exequted();

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
        virtual void errorDataHandler();


    private:
        ModbusRequest *m_curentModbusRequest;

};
//------------------------------------------------------------------------------------
#endif // MODBUSMASTERHANDLER_H

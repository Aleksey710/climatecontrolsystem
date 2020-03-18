#ifndef MODBUSMASTERHANDLER_H
#define MODBUSMASTERHANDLER_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QVector>
#include <QDebug>

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <modbus.h>

#include "Log.h"
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
        void exequteRequest(ModbusRequest *modbusRequest);

    private:
        template < typename T >
        void exequteRead( modbus_t *ctx,
                          ModbusRequest *modbusRequest,
                          int (*function)(modbus_t*,
                                          int,
                                          int,
                                          T*) );

        template < typename T >
        void exequteWrite( modbus_t *ctx,
                           ModbusRequest *modbusRequest,
                           int (*function)(modbus_t*,
                                           int,
                                           int,
                                           const T*) );

        void exequteWrite( modbus_t *ctx,
                           ModbusRequest *modbusRequest,
                           int (*function)(modbus_t*,
                                           int,
                                           int) );


        void errorHandler(ModbusRequest *modbusRequest);

        template < typename T >
        void setDataErrorHandler(ModbusRequest *modbusRequest);


    private:


};
//------------------------------------------------------------------------------------
#endif // MODBUSMASTERHANDLER_H

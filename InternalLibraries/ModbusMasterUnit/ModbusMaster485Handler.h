#ifndef MODBUSMASTER485HANDLER_H
#define MODBUSMASTER485HANDLER_H
//------------------------------------------------------------------------------------
#ifdef __arm__
    #ifndef NATIVE_MODBUS_HANDLER
//------------------------------------------------------------------------------------
#include <QObject>
#include <QModbusDataUnit>
#include <QModbusDevice>
//#include <QModbusClient>
//#include <QModbusTcpClient>
//#include <QModbusRtuSerialMaster>
//#include <QUrl>
//#include <QSerialPort>
//#include <QThread>

// Include these libraries for using the RS-485 and Modbus functions
#include "arduPi.h"
#include "ModbusMaster485.h"


#include "Log.h"
#include "ModbusRequest.h"
#include "ModbusConnectionSettings.h"
//------------------------------------------------------------------------------------
//!
class ModbusMaster485Handler : public QObject
{
        Q_OBJECT
    public:
        explicit ModbusMaster485Handler(QObject *parent = nullptr);
        virtual ~ModbusMaster485Handler();

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
        ModbusMaster485 *m_mm485;
};
//------------------------------------------------------------------------------------
    #endif // !NATIVE_MODBUS_HANDLER
//------------------------------------------------------------------------------------
#endif // __arm__
//------------------------------------------------------------------------------------
#endif // MODBUSMASTER485HANDLER_H

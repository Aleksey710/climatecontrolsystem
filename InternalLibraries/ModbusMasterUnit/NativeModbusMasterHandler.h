#ifndef NATIVEMODBUSMASTERHANDLER_H
#define NATIVEMODBUSMASTERHANDLER_H
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
#include "AbstractModbusMasterHandler.h"

//------------------------------------------------------------------------------------
//!
class NativeModbusMasterHandler : public AbstractModbusMasterHandler
{
        Q_OBJECT
    public:
        explicit NativeModbusMasterHandler(QObject *parent = nullptr);

        virtual ~NativeModbusMasterHandler();

    signals:
        void exequted();

    public slots:
        virtual void exequteRequest(ModbusRequest *request);

    private slots:
        bool reconnect(const ModbusConnectionSettings &modbusConnectionSettings);

        void readRequest(const int serverAddress, QModbusDataUnit &readDataUnit);
        void writeRequest(const int serverAddress, QModbusDataUnit &writeDataUnit);
        void readWriteRequest(const int serverAddress,
                              QModbusDataUnit &readDataUnit,
                              QModbusDataUnit &writeDataUnit);

    protected slots:
        void readReady();
        void writeReady();

    protected:
        void requestExecutionErrorHandler();
        void deleteModbusDevice();

        void readReplyHandler(QModbusReply *reply);
        void writeReplyHandler(QModbusReply *reply);

        void errorDataHandler();
        QString modbusExceptionCodeToString(const QModbusPdu::ExceptionCode &code);

    protected:
        QModbusClient *m_modbusDevice;


};
//------------------------------------------------------------------------------------
#endif // NATIVEMODBUSMASTERHANDLER_H

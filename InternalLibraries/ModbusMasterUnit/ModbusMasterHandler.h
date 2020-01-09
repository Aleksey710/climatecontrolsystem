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
//#include <>
//#include <>


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
        void exequteRequest(ModbusRequest *request);

        void reconnect(const ModbusConnectionSettings &modbusConnectionSettings);

        void readRequest(const int serverAddress, QModbusDataUnit &readDataUnit);
        void writeRequest(const int serverAddress, QModbusDataUnit &writeDataUnit);
        void readWriteRequest(const int serverAddress,
                              QModbusDataUnit &readDataUnit,
                              QModbusDataUnit &writeDataUnit);

    private slots:
        void readReady();

    private:
        void deleteModbusDevice();

        void replyHandler(QModbusReply *reply);
        void errorReplyHandler();
        QString modbusExceptionCodeToString(const QModbusPdu::ExceptionCode &code);

    private:
        QModbusClient *m_modbusDevice;

        ModbusRequest *m_curentModbusRequest;
};
//------------------------------------------------------------------------------------
#endif // MODBUSMASTERHANDLER_H

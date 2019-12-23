#ifndef MODBUSMASTERUNIT_H
#define MODBUSMASTERUNIT_H
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
//#include ""
//#include ""
//------------------------------------------------------------------------------------
//!
class ModbusMasterUnit : public QObject
{
        Q_OBJECT

    public:
        explicit ModbusMasterUnit(QObject *parent = nullptr);

        virtual ~ModbusMasterUnit();

    public slots:
        void reconnect(const ModbusConnectionSettings &modbusConnectionSettings);

        void readRequest(const int serverAddress, QModbusDataUnit &readDataUnit);
        void writeRequest(const int serverAddress, QModbusDataUnit &writeDataUnit);
        void readWriteRequest(const int serverAddress,
                              QModbusDataUnit &readDataUnit,
                              QModbusDataUnit &writeDataUnit);

    private slots:
        void readReady();

    private:
        void updateObjectName();

    private:
        QModbusClient *m_modbusDevice;

        std::shared_ptr<ModbusConnectionSettings> m_modbusConnectionSettings;
};
//------------------------------------------------------------------------------------
#endif // MODBUSMASTERUNIT_H

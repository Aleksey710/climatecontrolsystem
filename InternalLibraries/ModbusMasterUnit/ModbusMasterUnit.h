#ifndef MODBUSMASTERUNIT_H
#define MODBUSMASTERUNIT_H
//------------------------------------------------------------------------------------
#include <QObject>
//
#include <QModbusDataUnit>
#include <QModbusReply>
#include <QModbusClient>
#include <QModbusTcpClient>
#include <QModbusRtuSerialMaster>
#include <QModbusPdu>
//
#include <QSerialPort>
//
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
//
#include <QUrl>
#include <QThread>
#include <QMultiHash>
#include <QHash>
#include <QList>
#include <QDateTime>
//#include <>
//#include <>
//#include <>

//#include <>
//#include <>
//#include <>
//#include <>


#include "Log.h"
#include "ModbusConnection.h"
#include "ModbusConnectionSettings.h"
#include "ModbusMasterHandler.h"
#include "ModbusConnectionController.h"
//
#include "ScriptObject.h"
#include "ScriptUnit.h"
//#include ".h"
//#include ".h"
//------------------------------------------------------------------------------------
//!
class ModbusMasterUnit : public QObject
{
        Q_OBJECT

    public:
        explicit ModbusMasterUnit(QObject *parent = nullptr);

        virtual ~ModbusMasterUnit();

    public slots:

    private slots:

    private:
        QJsonObject loadFile(const QString &fileName);
        void setup(const QJsonObject &jsonObject);

        void connectionParsing(const QJsonObject &connectionJsonObject);
        void deviceParsing(const QJsonObject &deviceJsonObject);

        void startWorkInAThread(const ModbusConnectionSettings &modbusConnectionSettings);

    private:
        QHash <QString, ModbusConnectionSettings> m_modbusConnectionSettingsList;

};
//------------------------------------------------------------------------------------
#endif // MODBUSMASTERUNIT_H

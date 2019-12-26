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
#include <QThread>
//#include <>
//#include <>
//#include <>


#include "Log.h"
#include "ModbusConnection.h"
#include "ModbusConnectionSettings.h"
#include "ModbusMasterHandler.h"
//#include ""
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

    private slots:

    private:
        QStringList initQueryModbusUnitStringList();

    private:
        std::shared_ptr<ModbusMasterHandler> m_modbusMasterHandler;
};
//------------------------------------------------------------------------------------
#endif // MODBUSMASTERUNIT_H

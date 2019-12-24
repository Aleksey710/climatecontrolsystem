#ifndef MODBUSMASTERCONFIGURATOR_H
#define MODBUSMASTERCONFIGURATOR_H
//------------------------------------------------------------------------------------
//#include <>
#include <QModbusPdu>
#include <QSerialPort>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QMultiHash>
#include <QHash>
#include <QList>
#include <QDateTime>


#include "Log.h"
#include "DataModel.h"
#include "AbstractConfigurator.h"
#include "ModbusConnection.h"
#include "ModbusConnectionSettings.h"
#include "ModbusConnectionController.h"
//#include ""
//------------------------------------------------------------------------------------
//!
class ModbusMasterConfigurator : public AbstractConfigurator
{
    public:
        explicit ModbusMasterConfigurator(DataModel *dataModel,
                                          QObject *parent = nullptr);

        virtual ~ModbusMasterConfigurator();

        void startWorkInAThread(const ModbusConnectionSettings &modbusConnectionSettings);


    private:
        virtual void setup(const QJsonObject &jsonObject) override;

        void connectionParsing(const QJsonObject &connectionJsonObject);
        void deviceParsing(const QJsonObject &deviceJsonObject);
        void registerParsing(const QJsonObject &registerJsonObject);

    private:
        DataModel *m_dataModel;
};
//------------------------------------------------------------------------------------
#endif // MODBUSMASTERCONFIGURATOR_H

#ifndef MODBUSREQUEST_H
#define MODBUSREQUEST_H
//------------------------------------------------------------------------------------
#include <tuple>
#include <QObject>
#include <QModbusDataUnit>
#include <QTimer>
#include <QModbusPdu>
//#include <>
//#include <>
//#include <>
//#include <>
//#include <>


//#include ".h"
//#include ".h"
//#include ".h"

#include "Log.h"
#include "ModbusConnectionSettings.h"
#include "ScriptObject.h"
#include "ScriptUnit.h"
//------------------------------------------------------------------------------------
//!
class ModbusRequest : public QObject
{
        Q_OBJECT
    public:
        explicit ModbusRequest(const ModbusConnectionSettings &connectionSettings,
                               const quint16 &serverAddress,
                               const QModbusPdu::FunctionCode &functionCode,
                               QList< std::tuple<int, QString, QString> > &registerList, // Будет отсортирован
#ifndef CIRCULAR_PROCESSING_REQUEST
                               const int &period,
#endif // CIRCULAR_PROCESSING_REQUEST
                               QObject *parent = nullptr);
        virtual ~ModbusRequest();

        inline ModbusConnectionSettings connectionSettings() const
            { return m_connectionSettings; }

        inline quint16 serverAddress() const
            { return m_serverAddress; }

        inline QModbusPdu::FunctionCode functionCode()
            { return m_functionCode; }

        inline QModbusDataUnit& modbusDataUnit()
            { return m_modbusDataUnit; }

        void setModbusDataUnit(const QModbusDataUnit &dataUnit);

    public slots:



    signals:
        void wantExecuteQuery(ModbusRequest *request);

    private:
        QModbusDataUnit::RegisterType registerTypeFromFunctionCode(const QModbusPdu::FunctionCode &functionCode);

    private:
        ModbusConnectionSettings        m_connectionSettings;
        quint16                         m_serverAddress;
        QModbusPdu::FunctionCode        m_functionCode;
        QModbusDataUnit                 m_modbusDataUnit;

        QHash<quint16, ScriptObject*>   m_scriptObjectList;
};
//------------------------------------------------------------------------------------
#endif // MODBUSREQUEST_H

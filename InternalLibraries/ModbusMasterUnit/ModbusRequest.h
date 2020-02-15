#ifndef MODBUSREQUEST_H
#define MODBUSREQUEST_H
//------------------------------------------------------------------------------------
#include <tuple>
#include <QObject>
#include <QTimer>
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
#include "ModbusDataUnit.h"
//------------------------------------------------------------------------------------
//!
class ModbusRequest : public QObject
{
        Q_OBJECT
    public:
        explicit ModbusRequest(const ModbusConnectionSettings &connectionSettings,
                               const quint16 &serverAddress,
                               const int &functionCode,
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

        inline int functionCode()
            { return m_functionCode; }

        inline ScriptObject* deviceScriptObject()
            { return m_deviceScriptObject; }

        ModbusDataUnit &modbusDataUnit();

        void setModbusDataUnit(const ModbusDataUnit &dataUnit, int deviceState);

    public slots:



    signals:
        void wantExecuteQuery(ModbusRequest *request);

    private:
        ModbusConnectionSettings        m_connectionSettings;
        quint16                         m_serverAddress;

        int                             m_functionCode;
        ModbusDataUnit                  m_modbusDataUnit;

        ScriptObject                    *m_deviceScriptObject;

        QHash<quint16, ScriptObject*>   m_scriptObjectList;
};
//------------------------------------------------------------------------------------
#endif // MODBUSREQUEST_H

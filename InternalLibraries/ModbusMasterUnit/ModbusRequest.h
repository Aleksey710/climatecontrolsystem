#ifndef MODBUSREQUEST_H
#define MODBUSREQUEST_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QModbusDataUnit>
#include <QTimer>
#include <QModbusPdu>
//#include <>
//#include <>



#include "ModbusConnectionSettings.h"
//------------------------------------------------------------------------------------
//!
class ModbusRequest : public QObject
{
        Q_OBJECT
    public:
        explicit ModbusRequest(const ModbusConnectionSettings &connectionSettings,
                               const quint16 serverAddress,
                               const QModbusPdu::FunctionCode functionCode,
                               const QModbusDataUnit &modbusDataUnit,
#ifndef CIRCULAR_PROCESSING_REQUEST
                               const int period,
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

    public slots:
        void processRequest();


    signals:
        void wantExecuteQuery(ModbusRequest *request);

    private:
        ModbusConnectionSettings    m_connectionSettings;
        quint16                     m_serverAddress;
        QModbusPdu::FunctionCode    m_functionCode;
        QModbusDataUnit             m_modbusDataUnit;
};
//------------------------------------------------------------------------------------
#endif // MODBUSREQUEST_H

#ifndef MODBUSREQUEST_H
#define MODBUSREQUEST_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QModbusDataUnit>
#include <QTimer>
//#include <>
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
                               const quint16 deviceAddress,
                               const int period,
                               QObject *parent = nullptr);
        virtual ~ModbusRequest();

        inline ModbusConnectionSettings connectionSettings() const
            { return m_connectionSettings; }

    public slots:
        void processRequest();


    signals:
        void wantExecuteQuery(ModbusRequest *request);

    private:
        ModbusConnectionSettings m_connectionSettings;
        quint16 m_deviceAddress;

};
//------------------------------------------------------------------------------------
#endif // MODBUSREQUEST_H

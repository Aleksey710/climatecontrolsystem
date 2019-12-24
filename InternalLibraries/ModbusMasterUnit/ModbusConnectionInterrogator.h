#ifndef MODBUSCONNECTIONINTERROGATOR_H
#define MODBUSCONNECTIONINTERROGATOR_H
//------------------------------------------------------------------------------------
#include <QObject>

#include "ModbusConnection.h"
#include "ModbusConnectionSettings.h"
#include "ModbusMasterHandler.h"
//------------------------------------------------------------------------------------
//!
class ModbusConnectionInterrogator : public QObject
{
        Q_OBJECT
    public:
        explicit ModbusConnectionInterrogator(const ModbusConnectionSettings &modbusConnectionSettings,
                                              QObject *parent = nullptr);
        virtual ~ModbusConnectionInterrogator();

    signals:

    private:
        ModbusConnectionSettings m_modbusConnectionSettings;

        ModbusMasterHandler m_modbusMasterHandler;
};
//------------------------------------------------------------------------------------
#endif // MODBUSCONNECTIONINTERROGATOR_H

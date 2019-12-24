#ifndef MODBUSCONNECTIONSETTINGS_H
#define MODBUSCONNECTIONSETTINGS_H
//------------------------------------------------------------------------------------
#include <QString>

#include "ModbusConnection.h"
//------------------------------------------------------------------------------------
//!
class ModbusConnectionSettings
{
    public:
        //------------------------------------------------------------------------------------
        ModbusConnectionSettings(const ModbusConnection &__modbusConnectionType,
                                 //
                                 const QString &__serialPortNameParameter,
                                 const int __serialParityParameter,
                                 const int __serialBaudRateParameter,
                                 const int __serialDataBitsParameter,
                                 const int __serialStopBitsParameter,
                                 //
                                 const QString &__networkAddressParameter,
                                 const int __networkPortParameter,
                                 //
                                 const int __responseTime = 100,
                                 const int __numberOfRetries = 3)
            :modbusConnectionType ( __modbusConnectionType ),
             //
             serialPortNameParameter ( __serialPortNameParameter ),
             serialParityParameter ( __serialParityParameter ),
             serialBaudRateParameter ( __serialBaudRateParameter ),
             serialDataBitsParameter ( __serialDataBitsParameter ),
             serialStopBitsParameter ( __serialStopBitsParameter ),
             //
             networkAddressParameter ( __networkAddressParameter ),
             networkPortParameter ( __networkPortParameter ),
             //
             responseTime ( __responseTime ),
             numberOfRetries ( __numberOfRetries )
        {

        }
        //------------------------------------------------------------------------------------
/*
        ModbusConnectionSettings(const QString &__serialPortNameParameter,
                                 const int __serialParityParameter,
                                 const int __serialBaudRateParameter,
                                 const int __serialDataBitsParameter,
                                 const int __serialStopBitsParameter)
            :serialPortNameParameter ( __serialPortNameParameter ),
             serialParityParameter ( __serialParityParameter ),
             serialBaudRateParameter ( __serialBaudRateParameter ),
             serialDataBitsParameter ( __serialDataBitsParameter ),
             serialStopBitsParameter ( __serialStopBitsParameter ),
             //
             modbusConnectionType ( ModbusConnection::Serial )
        {

        }

        //------------------------------------------------------------------------------------
        ModbusConnectionSettings(const QString &__networkAddressParameter,
                                 const int __networkPortParameter)
            :networkAddressParameter ( __networkAddressParameter ),
             networkPortParameter ( __networkPortParameter ),
             //
             modbusConnectionType ( ModbusConnection::Tcp )
        {

        }
*/
        //------------------------------------------------------------------------------------
        ModbusConnection modbusConnectionType;

        QString serialPortNameParameter;
        int serialParityParameter;
        int serialBaudRateParameter;
        int serialDataBitsParameter;
        int serialStopBitsParameter;

        QString networkAddressParameter;
        int networkPortParameter;

        int responseTime;
        int numberOfRetries;
};
//------------------------------------------------------------------------------------
//!
#endif // MODBUSCONNECTIONSETTINGS_H

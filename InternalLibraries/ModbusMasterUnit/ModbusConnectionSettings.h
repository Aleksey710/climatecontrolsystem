#ifndef MODBUSCONNECTIONSETTINGS_H
#define MODBUSCONNECTIONSETTINGS_H
//------------------------------------------------------------------------------------
#include <QString>
/*
int parity = QSerialPort::EvenParity;
int baud = QSerialPort::Baud19200;
int dataBits = QSerialPort::Data8;
int stopBits = QSerialPort::OneStop;
int responseTime = 1000;
int numberOfRetries = 3;
*/
#include "ModbusConnection.h"
//------------------------------------------------------------------------------------
//!
class ModbusConnectionSettings
{
    public:
        //------------------------------------------------------------------------------------
        ModbusConnectionSettings(const QString &__serialPortNameParameter,
                                 const int __serialParityParameter,
                                 const int __serialBaudRateParameter,
                                 const int __serialDataBitsParameter,
                                 const int __serialStopBitsParameter,
                                 //
                                 const QString &__networkAddressParameter,
                                 const int __networkPortParameter,
                                 //
                                 const ModbusConnection &__modbusConnectionType,
                                 //
                                 const int __responseTime,
                                 const int __numberOfRetries)
            :serialPortNameParameter ( __serialPortNameParameter ),
             serialParityParameter ( __serialParityParameter ),
             serialBaudRateParameter ( __serialBaudRateParameter ),
             serialDataBitsParameter ( __serialDataBitsParameter ),
             serialStopBitsParameter ( __serialStopBitsParameter ),
             //
             networkAddressParameter ( __networkAddressParameter ),
             networkPortParameter ( __networkPortParameter ),
             //
             modbusConnectionType ( __modbusConnectionType ),
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
        QString serialPortNameParameter;
        int serialParityParameter;
        int serialBaudRateParameter;
        int serialDataBitsParameter;
        int serialStopBitsParameter;

        QString networkAddressParameter;
        int networkPortParameter;

        ModbusConnection modbusConnectionType;

        int responseTime;
        int numberOfRetries;

};
//------------------------------------------------------------------------------------
//!
#endif // MODBUSCONNECTIONSETTINGS_H

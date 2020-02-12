#ifndef MODBUSCONNECTIONSETTINGS_H
#define MODBUSCONNECTIONSETTINGS_H
//------------------------------------------------------------------------------------
#include <QString>
#include <QDebug>
#include <QSerialPort>

#include "ModbusConnection.h"
//------------------------------------------------------------------------------------
// #include "ModbusConnectionSettings.h"
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
                                 const int __responseTime = 50,
                                 const int __numberOfRetries = 1)
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
            //! Создать обработчик устройства
            if (modbusConnectionType == Serial)
            {
                QString parityString;

                switch (serialParityParameter)
                {
                    case QSerialPort::NoParity:
                        parityString = "N";
                        break;
                    case QSerialPort::EvenParity:
                        parityString = "E";
                        break;
                    case QSerialPort::OddParity:
                        parityString = "O";
                        break;
                    case QSerialPort::SpaceParity:
                        parityString = "S";
                        break;
                    case QSerialPort::MarkParity:
                        parityString = "M";
                        break;
                    case QSerialPort::UnknownParity:
                    default:
                        parityString = "U";
                        break;
                }

                connectionName = QString("RTU[%1(%2)%3%4%5]")
                                 .arg(serialPortNameParameter)
                                 .arg(serialBaudRateParameter)
                                 .arg(serialDataBitsParameter)
                                 .arg(parityString)
                                 .arg(serialStopBitsParameter)
                                 ;
            } else if (modbusConnectionType == Tcp)
            {
                connectionName = QString("TCP[%1:%2]")
                                .arg(networkAddressParameter)
                                .arg(networkPortParameter);
            }

            if(responseTime < 50) responseTime = 50;
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
        QString connectionName;

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

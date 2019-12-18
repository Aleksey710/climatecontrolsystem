#include "ModbusSerialConnectionItem.h"

//------------------------------------------------------------------------------------
//!
ModbusSerialConnectionItem::ModbusSerialConnectionItem(const QString &modbusType,
                                                       const QString &topicName,
                                                       const QString &uartPortName,
                                                       const int baudRate,
                                                       const char parity,
                                                       const int dataBits,
                                                       const int stopBits,
                                                       ModbusRegisterItem *parentItem)
                           :ModbusConnectionItem (topicName, parentItem)
{
    QString uartPortSystemLocation = uartPortName;

#ifdef Q_OS_LINUX
// Removes the prefix "/dev/" from the system location and returns the remainder of the string.
uartPortSystemLocation.replace("/dev/", "");
uartPortSystemLocation.prepend("/dev/");
#endif
#
#ifdef Q_OS_WIN
// Removes the prefix "\\.\" or "//./" from the system location and returns the remainder of the string.

uartPortSystemLocation.replace("\\.\\", "");
uartPortSystemLocation.replace("//./", "");
uartPortSystemLocation.prepend("\\.\\");
#endif

    if( !uartPortSystemLocation.isEmpty() )
    {
        //================================================================================================
        ModbusConnectionAddress  modbusConnectionAddress(modbusStringToType( modbusType ),
                                                         uartPortSystemLocation,
                                                         baudRate,
                                                         parity,
                                                         dataBits,
                                                         stopBits);


        //qDebug() << "MqttModbusMasterUnit::createActiveItem" << stationTopicName << modbusConnectionAddress.infoString();

        m_modbusMasterConnectionController =
                new ModbusMasterConnectionController(modbusType,
                                                     modbusConnectionAddress);

        SEND_TO_LOG( QString("ModbusSerialConnectionItem - (%1) port[%2] SystemLocation:[%3] [%4 %5] - создан")
                     .arg(modbusType)
                     .arg(uartPortName)
                     .arg( (uartPortSystemLocation.isEmpty()) ? "none" : uartPortSystemLocation)
                     .arg(baudRate)
                     .arg( QString("%1%2%3").arg(dataBits).arg(parity).arg(stopBits) )
                     );
    } else
    {
        SEND_TO_LOG( QString("ModbusSerialConnectionItem - (%1) port[%2] SystemLocation:[%3] - не корректно")
                     .arg(modbusType)
                     .arg(uartPortName)
                     .arg( (uartPortSystemLocation.isEmpty()) ? "none" : uartPortSystemLocation) );
    }
}
//------------------------------------------------------------------------------------
//!
ModbusSerialConnectionItem::~ModbusSerialConnectionItem()
{
    if(m_modbusMasterConnectionController)
        m_modbusMasterConnectionController->deleteLater();

    //SEND_TO_LOG( QString("%1 - удален").arg(itemName()) );
}
//------------------------------------------------------------------------------------
//!

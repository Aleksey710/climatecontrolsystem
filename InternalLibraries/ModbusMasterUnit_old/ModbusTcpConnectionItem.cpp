#include "ModbusTcpConnectionItem.h"

//------------------------------------------------------------------------------------
//!
ModbusTcpConnectionItem::ModbusTcpConnectionItem(const QString &topicName,
                                                 const QString &title,
                                                 QString ipAddress,
                                                 int tcpPort,
                                                 ModbusRegisterItem *parentItem)
                        :ModbusConnectionTopicItem (topicName, parentItem)
{
    m_modbusMasterConnectionController =
            new ModbusMasterConnectionController("TCP", ModbusConnectionAddress(ipAddress, tcpPort));

    SEND_TO_LOG( QString("ModbusTcpConnectionItem - (%1) [%2:%3]").arg(title).arg(ipAddress).arg(tcpPort) );
}
//------------------------------------------------------------------------------------
//!
ModbusTcpConnectionItem::~ModbusTcpConnectionItem()
{
    if(m_modbusMasterConnectionController)
        m_modbusMasterConnectionController->deleteLater();
}
//------------------------------------------------------------------------------------
//!



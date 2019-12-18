#include "ModbusConnectionItem.h"

//------------------------------------------------------------------------------------
//!
ModbusConnectionTopicItem::ModbusConnectionTopicItem(const QString &topicName,
                                                     AbstractModbusItem *parentItem)
                          :AbstractModbusItem (topicName, parentItem),
                           m_modbusMasterConnectionController ( Q_NULLPTR )
{

}
//------------------------------------------------------------------------------------
//!
ModbusConnectionTopicItem::~ModbusConnectionTopicItem()
{
    if(m_modbusMasterConnectionController)
        m_modbusMasterConnectionController->deleteLater();

    //SEND_TO_LOG( QString("%1 - удален").arg(itemName()) );
}
//------------------------------------------------------------------------------------
//!

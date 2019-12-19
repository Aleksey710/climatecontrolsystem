#include "AbstractModbusItem.h"

//------------------------------------------------------------------------------------
//!
AbstractModbusItem::AbstractModbusItem(const QString &topicName,
                                       AbstractModbusItem *parentItem)
                      :m_topicName ( topicName ),
                       m_data ( "" ),
                       m_parentItem ( parentItem )
{
    if(m_parentItem != Q_NULLPTR)
    {
        m_parentItem->appendChildren( this );
    }
}
//------------------------------------------------------------------------------------
//!
AbstractModbusItem::~AbstractModbusItem()
{
    qDeleteAll( m_childrens );
    //SEND_TO_LOG( QString("AbstractMqttTopicItem [%1] - удален").arg(fullTopicName()) );
}
//------------------------------------------------------------------------------------
//!
bool AbstractModbusItem::hasChildren() const
{
    return (m_childrens.size() > 0) ? true : false;
}
//------------------------------------------------------------------------------------
//!
void AbstractModbusItem::appendChildren(AbstractModbusItem *item)
{
    item->setParentItem(this);
    m_childrens.insert(item->topicName(), item);
}
//------------------------------------------------------------------------------------
//!
void AbstractModbusItem::removeChildrenAt(AbstractModbusItem *topicItem)
{
    if( topicItem )
    {
        removeChildrenAt(topicItem->topicName());
    }
}
//------------------------------------------------------------------------------------
//!
void AbstractModbusItem::removeChildrenAt(const QString &topicName)
{
    if( !topicName.isEmpty() )
        delete m_childrens.take(topicName);
}
//------------------------------------------------------------------------------------
//!
void AbstractModbusItem::deleteChildrens()
{
    qDeleteAll( m_childrens );
}
//------------------------------------------------------------------------------------
//!
AbstractModbusItem* AbstractModbusItem::childrenAt(const QString &topicName) const
{
    return m_childrens.value(topicName, Q_NULLPTR);
}
//------------------------------------------------------------------------------------
//!
QString AbstractModbusItem::data() const
{
    return m_data;
}
//------------------------------------------------------------------------------------
//!
void AbstractModbusItem::setData(const QString &value)
{
    m_data = value;
}
//------------------------------------------------------------------------------------
//!

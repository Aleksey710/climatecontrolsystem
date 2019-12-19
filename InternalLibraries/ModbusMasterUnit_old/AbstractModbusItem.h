#ifndef ABSTRACTMODBUSITEM_H
#define ABSTRACTMODBUSITEM_H
//------------------------------------------------------------------------------------
#include <QList>
#include <QHash>
//#include <>
//#include <>
//#include <>
//#include <>

#include "Log.h"
//#include ""
//#include ""
//------------------------------------------------------------------------------------
// #include "AbstractModbusItem.h"
//------------------------------------------------------------------------------------
//!
class AbstractModbusItem
{
    public:
        explicit AbstractModbusItem(const QString &topicName = QString(),
                                       AbstractModbusItem *parentItem = Q_NULLPTR);


        virtual ~AbstractModbusItem();

        inline QString topicName() const
            { return m_topicName; }

        inline QString rootTopicName() const
            {
                QString f = fullTopicName();

                QStringList l = f.split('/', QString::SkipEmptyParts);

                if(l.size() > 0)
                {
                    return l.at(0);
                }

                return f;
            }

        inline void setParentItem(AbstractModbusItem *parentItem)
            { m_parentItem = parentItem; }

        inline AbstractModbusItem *parentItem()
            { return m_parentItem; }

        inline QString fullTopicName() const
            {
                QString topicName = m_topicName;

                if( m_parentItem )
                {
                    if(!m_parentItem->topicName().isEmpty())
                    {
                        topicName.prepend('/');
                        topicName.prepend(m_parentItem->fullTopicName());
                    }
                }

                return topicName;
            }

        virtual bool hasChildren() const;

        virtual void appendChildren(AbstractModbusItem *item);

        virtual void removeChildrenAt(AbstractModbusItem *topicItem);

        virtual void removeChildrenAt(const QString &topicName);

        virtual void deleteChildrens();

        virtual AbstractModbusItem* childrenAt(const QString &topicName) const;

        virtual QString data() const;

        virtual void setData(const QString &value);

    protected:
        QString m_topicName;
        QString m_data;

        AbstractModbusItem *m_parentItem;

        QHash<QString, AbstractModbusItem*> m_childrens;
};
//------------------------------------------------------------------------------------
#endif // ABSTRACTMODBUSITEM_H

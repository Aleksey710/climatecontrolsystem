#ifndef DATAMODEL_H
#define DATAMODEL_H
//------------------------------------------------------------------------------------
//#include <>
//#include <>
//#include <>
#include <QObject>


#include "Log.h"
#include "DataItem.h"
//#include ""
//#include ""
//#include ""
//------------------------------------------------------------------------------------
//!
class DataModel : public QObject
{
        Q_OBJECT
    public:
        explicit DataModel(QObject *parent = nullptr);
        virtual ~DataModel();

        inline void appendItem(const QString &id, DataItem *item)
            { m_dataModel.insert(id, item); }

        inline DataItem* getItem(const QString &id)
            { return m_dataModel.value(id); }

    public slots:
        inline void setData(const QString &id, const QVariant &value)
        {
            DataItem *dataItem = m_dataModel.value(id, Q_NULLPTR);
            if(dataItem)
            {
                dataItem->setData(value);
            }
        }


    private:
        QHash<QString, DataItem*>   m_dataModel;

};
//------------------------------------------------------------------------------------
#endif // DATAMODEL_H

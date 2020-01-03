#include "DataItem.h"
//------------------------------------------------------------------------------------
//!
DataItem::DataItem(const QString id,
                   const QString title,
                   const QVariant value,
                   const QString dataType,
                   QObject *parent)
         :QObject(parent),
          m_id ( id ),
          m_title ( title ),
          m_dataType ( dataType ),
          m_value ( value )
{
    setObjectName(QString("DataItem[%1]").arg(id));

    //-------------------------------------------------------------------
    SEND_TO_LOG( QString("%1 = [%2] - (%3) - создан")
                 .arg(objectName())
                 .arg(value.toString())
                 .arg(m_title) );
}
//------------------------------------------------------------------------------------
//!
DataItem::~DataItem()
{
    SEND_TO_LOG( QString("%1 - удален").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!

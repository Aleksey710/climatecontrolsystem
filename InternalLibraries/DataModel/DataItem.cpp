#include "DataItem.h"
//------------------------------------------------------------------------------------
//!
DataItem::DataItem(const QString id,
                   QObject *parent)
         :QObject(parent),
          m_id ( id )
{
    setObjectName(QString("DataItem[%1]").arg(id));


    //-------------------------------------------------------------------
    SEND_TO_LOG( QString("%1 - создан").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
DataItem::~DataItem()
{
    SEND_TO_LOG( QString("%1 - удален").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!

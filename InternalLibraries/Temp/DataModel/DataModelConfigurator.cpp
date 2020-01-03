#include "DataModelConfigurator.h"
//------------------------------------------------------------------------------------
//!
DataModelConfigurator::DataModelConfigurator(std::shared_ptr<DataModel> dataModel,
                                             QObject *parent)
                      :AbstractConfigurator(QString("DataModelConfigurator"),
                                            parent),
                       m_dataModel ( dataModel )
{
    setup( loadFile( QString("./conf/data.conf") ) );

    //-------------------------------------------------------------------
    SEND_TO_LOG( QString("%1 - создан").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
DataModelConfigurator::~DataModelConfigurator()
{
    //SEND_TO_LOG( QString("%1 - удален").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
void DataModelConfigurator::setup(const QJsonObject &confJsonObject)
{
    SEND_TO_LOG( QString("%1 - конфигурирование запущено").arg(objectName()) );

    //---------------------------------------------------
    /*
    QByteArray dataArray = QJsonDocument(confJsonObject).toJson(QJsonDocument::Indented);
    SEND_TO_LOG( QString("%1 \r\n %2").arg(objectName()).arg( dataArray.data() ) );
    */
    //---------------------------------------------------

    QJsonArray groupJsonArray = confJsonObject.value("groups").toArray();

    foreach (const QJsonValue &value, groupJsonArray)
    {
        const QJsonObject groupJsonObject = value.toObject();
        groupParsing(groupJsonObject);
    }
}
//------------------------------------------------------------------------------------
//!
void DataModelConfigurator::groupParsing(const QJsonObject &groupJsonObject)
{
    QString id                  = groupJsonObject.value("id").toString();
    QString title               = groupJsonObject.value("title").toString();
    QJsonArray itemsJsonArray   = groupJsonObject.value("items").toArray();

    foreach (const QJsonValue &value, itemsJsonArray)
    {
        const QJsonObject itemJsonObject = value.toObject();
        itemParsing(itemJsonObject);
    }
}
//------------------------------------------------------------------------------------
//!
void DataModelConfigurator::itemParsing(const QJsonObject &itemJsonObject)
{
    const QString id          = itemJsonObject.value("id").toString();
    const QString title       = itemJsonObject.value("title").toString();
    const QString value       = itemJsonObject.value("value").toString();
    const QString dataType    = itemJsonObject.value("type").toString();

    QVariant v;

    if(dataType == "double")
    {
        v = QVariant( value.toDouble() );
    } else if(dataType == "string")
    {
        v = QVariant( value );
    }

    if( std::shared_ptr<DataModel> p = m_dataModel.lock() )
    {
        p->appendItem( id, new DataItem(id,
                                        title,
                                        value,
                                        dataType,
                                        this) );
    }
}







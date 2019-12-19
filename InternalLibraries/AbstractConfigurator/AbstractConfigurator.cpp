#include "AbstractConfigurator.h"

//------------------------------------------------------------------------------------
//!
AbstractConfigurator::AbstractConfigurator(const QString &configuratorName,
                                           QObject *parent)
                     : QObject(parent),
                       m_configuratorName ( configuratorName )
{
    setObjectName(m_configuratorName);



    //-------------------------------------------------------------------
    //SEND_TO_LOG( QString("%1 - создан").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
AbstractConfigurator::~AbstractConfigurator()
{
    SEND_TO_LOG( QString("%1 - удален").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
QJsonObject AbstractConfigurator::loadFile(const QString &fileName)
{
    QFile loadFile(fileName);

    if (!loadFile.open(QIODevice::ReadOnly))
    {
        SEND_TO_LOG( QString("%1 - couldn't open file[%2]").arg(objectName()).arg(fileName) );
        return QJsonObject();
    }

    QByteArray fileArray = loadFile.readAll();

    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(fileArray, &jsonParseError);

    if(jsonParseError.error == QJsonParseError::ParseError::NoError )
    {
        return jsonDocument.object();
    } else
    {
        SEND_TO_LOG( QString("%1 - ошибка формата [%2]").arg(objectName()).arg(jsonParseError.errorString()) );
        return QJsonObject();
    }
}
//------------------------------------------------------------------------------------
//!
void AbstractConfigurator::setup(const QJsonObject &jsonObject)
{
    QByteArray dataArray = QJsonDocument(jsonObject).toJson(QJsonDocument::Indented);


    SEND_TO_LOG( QString("%1 \r\n %2").arg(objectName()).arg( dataArray.data() ) );
}












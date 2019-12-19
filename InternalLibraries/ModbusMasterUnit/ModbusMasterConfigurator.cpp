#include "ModbusMasterConfigurator.h"

//------------------------------------------------------------------------------------
//!
ModbusMasterConfigurator::ModbusMasterConfigurator(const QString &configuratorName,
                                                   QObject *parent)
                         :AbstractConfigurator(configuratorName,
                                               parent)
{


    //-------------------------------------------------------------------
    SEND_TO_LOG( QString("%1 - конфигурирование окончено").arg(m_configuratorName) );
}
//------------------------------------------------------------------------------------
//!
ModbusMasterConfigurator::~ModbusMasterConfigurator()
{
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterConfigurator::setup(const QJsonObject &jsonObject)
{
    QByteArray dataArray = QJsonDocument(jsonObject).toJson(QJsonDocument::Indented);

    qDebug() << dataArray;
}

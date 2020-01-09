#include "ScriptUnit.h"

//------------------------------------------------------------------------------------
ScriptEngine* ScriptUnit::m_scriptEngine = nullptr;
QHash<QString, ScriptObject*> ScriptUnit::m_rootObjects;
//------------------------------------------------------------------------------------
//!
ScriptUnit::ScriptUnit(QObject *parent)
           :QObject(parent)
{
    setObjectName("ScriptUnit");

    m_scriptEngine = new ScriptEngine();

    setupSettingsData();

    setupScript(loadFile( qApp->applicationDirPath()+"/conf/script.conf" ));


    SEND_TO_LOG( QString("%1 - создан").arg(objectName()))
}
//------------------------------------------------------------------------------------
//!
ScriptUnit::~ScriptUnit()
{
    QHashIterator<QString, ScriptObject*> i(m_rootObjects);
    while (i.hasNext())
    {
        i.next();

        //SEND_TO_LOG( QString("%1 - [%2].deleteLater()").arg(objectName()).arg(i.key()))

        //i.value()->deleteLater();
        delete i.value();
    }

    //m_scriptEngine->deleteLater();
    delete m_scriptEngine;

    SEND_TO_LOG( QString("%1 - удален").arg(objectName()))
}
//------------------------------------------------------------------------------------
//!
ScriptObject* ScriptUnit::getScriptObject(const QString &name)
{
    if(name.isEmpty())
        return nullptr;

    //-------------------------------------------------
    QStringList partNameList = name.split(".");

    ScriptObject *rootScriptObject = m_rootObjects.value( partNameList.at(0), nullptr );

    if( !rootScriptObject )
    {
        return nullptr;
    }

    if(partNameList.size() == 1)
    {
        return rootScriptObject;
    }

    //-------------------------------------------------
    ScriptObject *groupScriptObject = rootScriptObject->getChildren(partNameList.at(1));

    if(partNameList.size() == 2)
    {
        return groupScriptObject;
    }

    //-------------------------------------------------
    if(groupScriptObject)
    {
        return groupScriptObject->getChildren(partNameList.at(2));
    }

    return nullptr;
}
//------------------------------------------------------------------------------------
//!
ScriptObject* ScriptUnit::createScriptObject(const QString &type,
                                             const QString &group,
                                             const QString &data,
                                             const QString &title,
                                             const double &value)
{
    //------------------------
    ScriptObject *rootScriptObject = m_rootObjects.value( type, nullptr );

    if( !rootScriptObject )
    {
        rootScriptObject = new ScriptObject(type, 0, nullptr);
        m_rootObjects.insert(type, rootScriptObject);

        m_scriptEngine->addGlobalQbject(rootScriptObject);
    }

    //------------------------
    ScriptObject *groupScriptObject = rootScriptObject->getChildren( group );

    if( !groupScriptObject )
    {
        groupScriptObject = new ScriptObject(group, 0, rootScriptObject);
    }
    //------------------------
    ScriptObject *scriptObject = groupScriptObject->getChildren( data );

    if( !scriptObject )
    {
        scriptObject = new ScriptObject(data, value, groupScriptObject);

        SEND_TO_LOG( QString("%1 - создан [%2]-[%3]")
                     .arg(objectName())
                     .arg(QString("%1.%2.%3").arg(type).arg(group).arg(data))
                     .arg(title)
                     );

        return scriptObject;
    } else
    {
        SEND_TO_LOG( QString("%1 - ERROR (Ошибка конфигурации[%2])")
                     .arg(objectName())
                     .arg(QString("%1.%2.%3").arg(type).arg(group).arg(data)) );
    }

    return nullptr;
}
//------------------------------------------------------------------------------------
//!
void ScriptUnit::setupSettingsData()
{
    QSqlDatabase db(QSqlDatabase::database(DbUnit::dbName()));

    QString query(
        "SELECT "
        "`types`.`name` AS `type`, "
        "`groups`.`name` AS `group`, "
        "`data`.`name` AS `data`, "
        "`data`.`title` AS `title`, "
        "`data`.`value` AS `value` "
        "FROM `types`,`groups`,`data` "
        "WHERE "
        "`types`.`id`=`groups`.`type_id` AND "
        "`groups`.`id`=`data`.`group_id` "
        "GROUP BY `type`,`group`,`data`; "
    );

    QSqlQuery sqlQuery(db);

    if( !sqlQuery.exec(query) )
    {
        QSqlError err = db.lastError();

        SEND_TO_LOG( QString("%1 - ERROR (ошибка запроса [%2] [%3])")
                     .arg(objectName()).arg(query).arg(err.text()))
        return;
    }

    int type_id     = sqlQuery.record().indexOf("type");
    int group_id    = sqlQuery.record().indexOf("group");
    int data_id     = sqlQuery.record().indexOf("data");
    int title_id    = sqlQuery.record().indexOf("title");
    int value_id    = sqlQuery.record().indexOf("value");

    while (sqlQuery.next())
    {
        QString type = sqlQuery.value(type_id).toString();
        QString group = sqlQuery.value(group_id).toString();
        QString data = sqlQuery.value(data_id).toString();
        QString title = sqlQuery.value(title_id).toString();
        double value = sqlQuery.value(value_id).toDouble();

        createScriptObject(type, group, data, title, value);
    }
}
//------------------------------------------------------------------------------------
//!
QJsonObject ScriptUnit::loadFile(const QString &fileName)
{
    QFile loadFile(fileName);

    if (!loadFile.open(QIODevice::ReadOnly))
    {
        SEND_TO_LOG( QString("%1 - ERROR (couldn't open file[%2])").arg(objectName()).arg(fileName) );
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
        SEND_TO_LOG( QString("%1 - ERROR (Ошибка формата [%2])").arg(objectName()).arg(jsonParseError.errorString()) );
        return QJsonObject();
    }
}
//------------------------------------------------------------------------------------
//!
void ScriptUnit::setupScript(const QJsonObject &jsonObject)
{
    /*
    QByteArray byteArray = QJsonDocument(jsonObject).toJson(QJsonDocument::Indented);
    SEND_TO_LOG( QString("%1 \r\n %2").arg(objectName()).arg( byteArray.data() ) );
    */
    //---------------------------------------
    setupData( jsonObject.value("data").toArray() );
    setupFunctions ( jsonObject.value("functions").toArray() );
}
//------------------------------------------------------------------------------------
//!
void ScriptUnit::setupData(const QJsonArray &jsonArray)
{
    foreach (const QJsonValue &jsonValue, jsonArray)
    {
        const QJsonObject dataJsonObject = jsonValue.toObject();

        QString name = dataJsonObject.value("name").toString();

        QStringList partName = name.split(".");

        if(partName.size()==3)
        {
            QString type    = partName[0];
            QString group   = partName[1];
            QString data    = partName[2];

            if(type.isEmpty()  ||
               group.isEmpty() ||
               data.isEmpty()
               )
            {
                SEND_TO_LOG( QString("%1 - ERROR (Не верный формат имени [%2].[%3].[%4])")
                             .arg(objectName()).arg( type ).arg( group ).arg( data ) );
            } else
            {
                QString title = dataJsonObject.value("title").toString();
                double value = 0;

                createScriptObject(type, group, data, title, value);
            }
        } else
        {
            SEND_TO_LOG( QString("%1 - ERROR (Не верный формат имени [%2])")
                         .arg(objectName()).arg(name) );
        }
    }
}
//------------------------------------------------------------------------------------
//!
void ScriptUnit::setupFunctions(const QJsonArray &jsonArray)
{
    foreach (const QJsonValue &functionJsonValue, jsonArray)
    {
        //------------------------------------------
        const QJsonObject functionJsonObject = functionJsonValue.toObject();

        QString name = functionJsonObject.value("name").toString();

        //------------------------------------------
        QJsonArray sourcesArray = functionJsonObject.value("sources").toArray();

        foreach (const QJsonValue &sourcesJsonValue, sourcesArray)
        {
            const QString sourceName = sourcesJsonValue.toString();

            ScriptObject *scriptObject = getScriptObject(sourceName);

            if( !scriptObject )
            {
                SEND_TO_LOG( QString("%1 - ERROR (Несуществующий источник [%2])")
                             .arg(objectName()).arg( sourceName ) );
            }
        }
        //------------------------------------------

//        QScriptValue redefinedScriptPrint_sv = newFunction( redefinedScriptPrint );
//        globalObject().setProperty(name, redefinedScriptPrint_sv);
        //------------------------------------------
    }
}
//------------------------------------------------------------------------------------
//!

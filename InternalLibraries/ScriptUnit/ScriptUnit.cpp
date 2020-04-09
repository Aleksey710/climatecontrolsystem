#include "ScriptUnit.h"

//------------------------------------------------------------------------------------
ScriptEngine* ScriptUnit::m_scriptEnginePtr = nullptr;
QHash<QString, ScriptObject*> ScriptUnit::m_rootObjects;
//------------------------------------------------------------------------------------
//!
ScriptUnit::ScriptUnit(QObject *parent)
           :QObject(parent)
{
    setObjectName("ScriptUnit");

    m_scriptEnginePtr = &m_scriptEngine;

    connect(&m_scriptEngine, &ScriptEngine::archiveMessage, this, &ScriptUnit::archiveMessage);

    setupSettingsData();
    createCurentTimeScriptObject();

    //! Инициализировать скрипт после инициализации ВСЕХ системных переменных
    setupScript(loadFile( qApp->applicationDirPath()+"/conf/script.json" ));

    SEND_TO_LOG( QString("%1 - создан").arg(objectName()));
}
//------------------------------------------------------------------------------------
//!
ScriptUnit::~ScriptUnit()
{
    QHashIterator<QString, ScriptObject*> i(m_rootObjects);
    while (i.hasNext())
    {
        i.next();

        delete i.value();

        m_rootObjects.remove(i.key());
    }

    m_scriptEnginePtr = nullptr;

    SEND_TO_LOG( QString("%1 - удален").arg(objectName()));
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
                                             const QString &value,
                                             const QString &valueType)
{
    //------------------------
    ScriptObject *rootScriptObject = m_rootObjects.value( type, nullptr );

    if( !rootScriptObject )
    {
        rootScriptObject = new ScriptObject(type, 0, nullptr);
        m_rootObjects.insert(type, rootScriptObject);

        m_scriptEngine.addGlobalQbject(rootScriptObject);
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
        if(valueType == "double")
        {
            scriptObject = new ScriptObject(data, value.toDouble(), groupScriptObject);
        } else
        {
            scriptObject = new ScriptObject(data, value, groupScriptObject);
        }

        SEND_TO_LOG( QString("%1 - создан [%2]-value[%3]-[%4]")
                     .arg(objectName())
                     .arg(QString("%1.%2.%3").arg(type).arg(group).arg(data))
                     .arg(value)
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
//!ScriptObject
void ScriptUnit::createCurentTimeScriptObject()
{
    const QString type      = "sys";
    const QString group     = "time";
    const QString title     = "Системное время в секундах";
    //------------------------
    ScriptObject *rootScriptObject = m_rootObjects.value( "sys", nullptr );

    if( !rootScriptObject )
    {
        rootScriptObject = new ScriptObject(type, 0, nullptr);
        m_rootObjects.insert(type, rootScriptObject);

        m_scriptEngine.addGlobalQbject(rootScriptObject);
    }

    //------------------------
    ScriptObject *groupScriptObject = new ScriptObject(group, 0, rootScriptObject);
    //------------------------
    ScriptObject *scriptObject = new CurentTimeScriptObject(groupScriptObject);

    Q_UNUSED(scriptObject);

    SEND_TO_LOG( QString("%1 - создан [sys.time.curent]-[%2]")
                 .arg(objectName())
                 .arg(title)
                 );

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
        "`data`.`value` AS `value`, "
        "`data_types`.`type` AS `value_type` "
        "FROM `types`,`groups`,`data`,`data_types` "
        "WHERE "
        "`data_types`.id = `data`.`data_type_id` AND "
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

    int type_id          = sqlQuery.record().indexOf("type");
    int group_id         = sqlQuery.record().indexOf("group");
    int data_id          = sqlQuery.record().indexOf("data");
    int title_id         = sqlQuery.record().indexOf("title");
    int value_id         = sqlQuery.record().indexOf("value");
    int value_type_id    = sqlQuery.record().indexOf("value_type");

    while (sqlQuery.next())
    {
        QString type            = sqlQuery.value(type_id).toString();
        QString group           = sqlQuery.value(group_id).toString();
        QString data            = sqlQuery.value(data_id).toString();
        QString title           = sqlQuery.value(title_id).toString();
        QString value           = sqlQuery.value(value_id).toString();
        QString valueType       = sqlQuery.value(value_type_id).toString();

        createScriptObject(type, group, data, title, value, valueType);
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

        QJsonValue commentValue = dataJsonObject.value("lineComment");

        //! Если не комментарий
        if(commentValue.isUndefined())
        {
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
                    QString value = "0";

                    createScriptObject(type, group, data, title, value, "double");
                }
            } else
            {
                SEND_TO_LOG( QString("%1 - ERROR (Не верный формат имени [%2])")
                             .arg(objectName()).arg(name) );
            }
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

        QString functionText = functionJsonObject.value("processing").toString();

        //------------------------------------------
        if( !functionText.isEmpty() )
        {
            //------------------------------------------
            QScriptSyntaxCheckResult scriptSyntaxCheckResult = m_scriptEngine.checkSyntax(functionText);

            if(scriptSyntaxCheckResult.state() != QScriptSyntaxCheckResult::Valid)
            {
                SEND_TO_LOG( QString("%1 - ERROR (Ошибка в тексте функции [%2] - %3) \r\n"
                                     "%4")
                             .arg(objectName())
                             .arg(name)
                             .arg(QString("line: %1, column %2 (%3)")
                                  .arg(scriptSyntaxCheckResult.errorLineNumber())
                                  .arg(scriptSyntaxCheckResult.errorColumnNumber())
                                  .arg(scriptSyntaxCheckResult.errorMessage())
                                  )
                             .arg(functionText)
                             );
                continue;
            }
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
                    continue;
                } else
                {
                    connect(scriptObject, &ScriptObject::dataChanged,[this, functionText](){
                        m_scriptEngine.evaluate( functionText );
                    });
                }
            }
            //------------------------------------------
        } else
        {
            SEND_TO_LOG( QString("%1 - ERROR (Функция [%2] не имеет кода)")
                         .arg(objectName()).arg(name) );
        }
    }
}
//------------------------------------------------------------------------------------
//!

#include "ScriptUnit.h"

//------------------------------------------------------------------------------------
ScriptEngine* ScriptUnit::m_scriptEngine = nullptr;
QHash<QString, ScriptObject*> ScriptUnit::m_rootObjects;
//------------------------------------------------------------------------------------
//!
ScriptUnit::ScriptUnit(QObject *parent)
           : QObject(parent),
             m_mainLoopTimer ( std::make_shared<QTimer>(this) )
{
    setObjectName("ScriptUnit");

    m_scriptEngine = new ScriptEngine();

    setupSettingsData();

    //loadFile( QString("./conf/data.conf") ) );

    connect(m_mainLoopTimer.get(), &QTimer::timeout, [=](){

    });



    SEND_TO_LOG( QString("%1 - создан").arg(objectName()))
}
//------------------------------------------------------------------------------------
//!
ScriptUnit::~ScriptUnit()
{
    SEND_TO_LOG( QString("%1 - удален").arg(objectName()))
}
//------------------------------------------------------------------------------------
//!
ScriptObject* ScriptUnit::getScriptObject(const QString &name)
{
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
    return groupScriptObject->getChildren(partNameList.at(2));
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

        SEND_TO_LOG( QString("%1 - Error [%2] [%3]")
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

            SEND_TO_LOG( QString("%1 - создан [%2]")
                         .arg(objectName())
                         .arg(QString("%1.%2.%3").arg(type).arg(group).arg(data)) );
        } else
        {
            SEND_TO_LOG( QString("%1 - Ошибка конфигурации[%2]")
                         .arg(objectName())
                         .arg(QString("%1.%2.%3").arg(type).arg(group).arg(data)) );
        }
    }
}
//------------------------------------------------------------------------------------
//!
QByteArray ScriptUnit::loadFile(const QString &fileName)
{
    QFile loadFile(fileName);

    if (!loadFile.open(QIODevice::ReadOnly))
    {
        SEND_TO_LOG( QString("%1 - couldn't open file[%2]").arg(objectName()).arg(fileName) );
        return QByteArray();
    }

    return loadFile.readAll();
}
//------------------------------------------------------------------------------------
//!
void ScriptUnit::setupMainLoop(const QStringList &functionList)
{
    m_scriptEngine;
}
//------------------------------------------------------------------------------------
//!
void ScriptUnit::startMainLoopTimer(int msec)
{
    m_mainLoopTimer->start(msec);
}

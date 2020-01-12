#ifndef SCRIPTUNIT_H
#define SCRIPTUNIT_H
//------------------------------------------------------------------------------------
#include <QCoreApplication>
#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTimer>
#include <QSqlRecord>
#include <QHash>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QStringList>
#include <QScriptSyntaxCheckResult>
//#include <>
//#include <>
//#include <>


#include "Log.h"
#include "ScriptEngine.h"
#include "DbUnit.h"
#include "ScriptObject.h"
//#include ""
//#include ""
//------------------------------------------------------------------------------------
//!
class ScriptUnit : public QObject
{
        Q_OBJECT
    public:
        explicit ScriptUnit(QObject *parent = nullptr);
        virtual ~ScriptUnit();

        inline static ScriptEngine* scriptEngine()
            { return m_scriptEnginePtr; }

        static ScriptObject* getScriptObject(const QString &name);

    signals:

    public slots:


    private:        
        ScriptObject* createScriptObject(const QString &type,
                                         const QString &group,
                                         const QString &data,
                                         const QString &title,
                                         const double &value);

        QJsonObject loadFile(const QString &fileName);
        void setupScript(const QJsonObject &jsonObject);
        void setupData(const QJsonArray &jsonObject);
        void setupFunctions(const QJsonArray &jsonObject);

        void setupSettingsData();

    private:
        static ScriptEngine *m_scriptEnginePtr;
        ScriptEngine m_scriptEngine;

        static QHash<QString, ScriptObject*> m_rootObjects;
};
//------------------------------------------------------------------------------------
#endif // SCRIPTUNIT_H

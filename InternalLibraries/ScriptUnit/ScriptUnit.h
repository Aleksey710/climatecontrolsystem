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
#include "CurentTimeScriptObject.h"
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

        inline static void systemActivation()
            { if(m_scriptEnginePtr) m_scriptEnginePtr->evaluate( m_systemActivationFunctionText ); }

        inline static void systemShutdown()
            { if(m_scriptEnginePtr) m_scriptEnginePtr->evaluate( m_systemShutdownFunctionText ); }

    signals:
        void archiveMessage(const int &msgId, const double &value);

    public slots:



    private:        
        ScriptObject* createScriptObject(const QString &type,
                                         const QString &group,
                                         const QString &data,
                                         const QString &title,
                                         const QString &value,
                                         const QString &valueType);

        QJsonObject loadFile(const QString &fileName);
        void setupScript(const QJsonObject &jsonObject);
        void setupData(const QJsonArray &jsonObject);
        void setupFunctions(const QJsonArray &jsonObject);

        void setupSettingsData();

        void createCurentTimeScriptObject();

    private:
        static ScriptEngine *m_scriptEnginePtr;
        ScriptEngine m_scriptEngine;

        static QHash<QString, ScriptObject*> m_rootObjects;

        //------------------
        static QString m_systemActivationFunctionText;
        static QString m_systemShutdownFunctionText;

};
//------------------------------------------------------------------------------------
#endif // SCRIPTUNIT_H

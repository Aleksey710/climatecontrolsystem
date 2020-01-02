#ifndef SCRIPTUNIT_H
#define SCRIPTUNIT_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTimer>
#include <QSqlRecord>
#include <QHash>
//#include <>
//#include <>


#include "Log.h"
#include "ScriptEngine.h"
#include "ScriptUnitConfigurator.h"
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
            { return m_scriptEngine; }

        static ScriptObject* getScriptObject(const QString &name);

    signals:

    public slots:
        void setupMainLoop(const QStringList &functionList);

        void startMainLoopTimer(int msec = 1000);


    private:
        QByteArray loadFile(const QString &fileName);

        void setupSettingsData();

    private:
        static ScriptEngine *m_scriptEngine;

        static QHash<QString, ScriptObject*> m_rootObjects;

        std::shared_ptr<QTimer> m_mainLoopTimer;
};
//------------------------------------------------------------------------------------
#endif // SCRIPTUNIT_H

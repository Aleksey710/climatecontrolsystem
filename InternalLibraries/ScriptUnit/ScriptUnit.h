#ifndef SCRIPTUNIT_H
#define SCRIPTUNIT_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QString>
//#include <QSqlDatabase>
//#include <QSqlError>
//#include <QSqlQuery>
#include <QTimer>
//#include <>
//#include <>
//#include <>
//#include <>


#include "Log.h"
#include "ScriptEngine.h"
//#include ""
//#include ""
//#include ""
//------------------------------------------------------------------------------------
//!
class ScriptUnit : public QObject
{
        Q_OBJECT

    public:
        static std::shared_ptr<ScriptEngine> m_scriptEngine;

    public:
        explicit ScriptUnit(QObject *parent = nullptr);
        virtual ~ScriptUnit();

    signals:

    public slots:
        void setupMainLoop(const QStringList &functionList);

        void startMainLoopTimer(int msec = 1000);


    private:
        void setupData();

    private:

        std::shared_ptr<QTimer> m_mainLoopTimer;
};
//------------------------------------------------------------------------------------
#endif // SCRIPTUNIT_H

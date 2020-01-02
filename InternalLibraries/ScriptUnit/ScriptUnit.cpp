#include "ScriptUnit.h"

//------------------------------------------------------------------------------------
std::shared_ptr<ScriptEngine> ScriptUnit::m_scriptEngine = std::make_shared<ScriptEngine>();
//------------------------------------------------------------------------------------
//!
ScriptUnit::ScriptUnit(QObject *parent)
           : QObject(parent)
{
    connect(m_mainLoopTimer.get(), &QTimer::timeout, [=](){

    });
}
//------------------------------------------------------------------------------------
//!
ScriptUnit::~ScriptUnit()
{

}
//------------------------------------------------------------------------------------
//!
void ScriptUnit::setupData()
{

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

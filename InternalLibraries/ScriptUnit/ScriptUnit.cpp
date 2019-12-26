#include "ScriptUnit.h"

//------------------------------------------------------------------------------------
ScriptEngine* ScriptUnit::m_scriptEngine = Q_NULLPTR;
//------------------------------------------------------------------------------------
//!
ScriptUnit::ScriptUnit(QObject *parent)
           : QObject(parent)
{
    m_scriptEngine = new ScriptEngine(this);
}
//------------------------------------------------------------------------------------
//!

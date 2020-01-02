#include "ScriptUnit.h"

//------------------------------------------------------------------------------------
std::shared_ptr<ScriptEngine> ScriptUnit::m_scriptEngine = std::make_shared<ScriptEngine>();
//------------------------------------------------------------------------------------
//!
ScriptUnit::ScriptUnit(QObject *parent)
           : QObject(parent)
{

}
//------------------------------------------------------------------------------------
//!

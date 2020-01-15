#include "ClimateControlSystem.h"

//------------------------------------------------------------------------------------
//!
ClimateControlSystem::ClimateControlSystem(QObject *parent)
                     :QObject(parent)
{
    SEND_TO_LOG("*****************************************************************************************");
    SEND_TO_LOG("************                                      ***************************************");
    SEND_TO_LOG("************    Запуск ClimateControlSystem       ***************************************");
    SEND_TO_LOG("************                                      ***************************************");
    SEND_TO_LOG("*****************************************************************************************");

    connect(this, &ClimateControlSystem::destroyed,[](){
        SEND_TO_LOG("*****************************************************************************************");
        SEND_TO_LOG("************     Окончание работы ClimateControlSystem                 ******************");
        SEND_TO_LOG("*****************************************************************************************");
    });
    //-------------------------------------------------------------------

    m_dbUnit            = std::make_shared<DbUnit>();
    m_scriptUnit        = std::make_shared<ScriptUnit>();
    m_modbusMasterUnit  = std::make_shared<ModbusMasterUnit>();

    //-------------------------------------------------------------------
    SEND_TO_LOG( QString("ClimateControlSystem - создан") );
}
//------------------------------------------------------------------------------------
//!
ClimateControlSystem::~ClimateControlSystem()
{
    if(m_modbusMasterUnit.get())
        m_modbusMasterUnit->deleteLater();

    if(m_scriptUnit.get())
        m_scriptUnit->deleteLater();

    if(m_dbUnit.get())
        m_dbUnit->deleteLater();

    //-------------------------------------------------------------------
    SEND_TO_LOG( QString("ClimateControlSystem - удален") );
}

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
    //-------------------------------------------------------------------

    m_dbUnit        = std::make_shared<DbUnit>();
    m_scriptUnit    = std::make_shared<ScriptUnit>();

    //ModbusMasterConfigurator modbusMasterConfigurator();

    m_mainDisplayWidget = new MainDisplayWidget(m_dbUnit);

    //-------------------------------------------------------------------
    SEND_TO_LOG( QString("ClimateControlSystem - создан") );
}
//------------------------------------------------------------------------------------
//!
ClimateControlSystem::~ClimateControlSystem()
{
    m_mainDisplayWidget->close();

    //-------------------------------------------------------------------
    SEND_TO_LOG( QString("ClimateControlSystem - удален") );
    SEND_TO_LOG("*****************************************************************************************");
    SEND_TO_LOG("************     Окончание работы ClimateControlSystem                 ******************");
    SEND_TO_LOG("*****************************************************************************************");
}

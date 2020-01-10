#include "ClimateControlSystem.h"

//------------------------------------------------------------------------------------
//!
ClimateControlSystem::ClimateControlSystem(QObject *parent)
                     :QObject(parent)
//                      ,m_dbUnit ( nullptr )
//                      ,m_scriptUnit ( nullptr )
//                      ,m_modbusMasterUnit ( nullptr )
//                      ,m_mainDisplayWidget ( nullptr )
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

    m_mainDisplayWidget = std::make_shared<MainDisplayWidget>(m_dbUnit.get());

//    m_dbUnit            = new DbUnit(this);
//    m_scriptUnit        = new ScriptUnit(this);
//    m_modbusMasterUnit  = new ModbusMasterUnit(this);

//    m_mainDisplayWidget = new MainDisplayWidget(m_dbUnit);

    //-------------------------------------------------------------------
    SEND_TO_LOG( QString("ClimateControlSystem - создан") );
}
//------------------------------------------------------------------------------------
//!
ClimateControlSystem::~ClimateControlSystem()
{
//    m_mainDisplayWidget.reset();
//    m_modbusMasterUnit.reset();
//    m_dbUnit.reset();
//    m_scriptUnit.reset();

    //-------------------------------------------------------------------
    SEND_TO_LOG( QString("ClimateControlSystem - удален") );
}

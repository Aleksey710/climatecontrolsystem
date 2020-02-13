#include "ClimateControlSystem.h"

//------------------------------------------------------------------------------------
//!
ClimateControlSystem::ClimateControlSystem(QObject *parent)
                     :QObject(parent)
{

    //-------------------------------------------------------------------

#ifdef __arm__
    setupRpi();
#endif // __arm__

    //-------------------------------------------------------------------
    //! Связать функцию архивирования в скрипте с функцией непосредственной работы с базой
    ArchiveFunction = [&](const int &msgId, const double &value = 0){

        //SEND_TO_LOG( QString("ClimateControlSystem - ArchiveFunction[%1][%2]").arg(msgId).arg(value) );
        m_dbUnit.writeMsg(msgId, value);
    };

    //-------------------------------------------------------------------
    //! Связать функцию архивирования в скрипте с функцией непосредственной работы с базой
    SaveSettingsFunction = [&](const QString &groupe, const QString &param, const double &value){

        //SEND_TO_LOG( QString("ClimateControlSystem - ArchiveFunction[%1][%2]").arg(msgId).arg(value) );
        m_dbUnit.saveSettings(groupe, param, value);
    };

    //-------------------------------------------------------------------
    SEND_TO_LOG( QString("ClimateControlSystem - создан") );
}
//------------------------------------------------------------------------------------
//!
ClimateControlSystem::~ClimateControlSystem()
{
    SEND_TO_LOG( QString("ClimateControlSystem - удален") );
}
//------------------------------------------------------------------------------------
//!
void ClimateControlSystem::setupRpi()
{
    SEND_TO_LOG("*****************************************************************************************");
    SEND_TO_LOG( QString("ClimateControlSystem - setup Raspberry Pi") );


    SEND_TO_LOG("*****************************************************************************************");  
}

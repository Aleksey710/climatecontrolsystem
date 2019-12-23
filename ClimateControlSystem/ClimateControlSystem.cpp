#include "ClimateControlSystem.h"

//------------------------------------------------------------------------------------
//!
ClimateControlSystem::ClimateControlSystem(QObject *parent)
                     :QObject(parent),
                      m_dataModel ( new DataModel(this) )
{
    SEND_TO_LOG("*****************************************************************************************");
    SEND_TO_LOG("************                                      ***************************************");
    SEND_TO_LOG("************    Запуск ClimateControlSystem       ***************************************");
    SEND_TO_LOG("************                                      ***************************************");
    SEND_TO_LOG("*****************************************************************************************");
    //-------------------------------------------------------------------


    DataModelConfigurator dataModelConfigurator(m_dataModel);



    m_mainDisplayWidget = new MainDisplayWidget(m_dataModel);

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

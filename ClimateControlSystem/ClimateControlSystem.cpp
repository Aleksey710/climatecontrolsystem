#include "ClimateControlSystem.h"

//------------------------------------------------------------------------------------
//!
ClimateControlSystem::ClimateControlSystem(QObject *parent)
                     :QObject(parent)
{
    //-------------------------------------------------------------------
#ifdef __arm__
    wiringPiSetup();
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
    //! Связать функцию архивирования в скрипте с функцией непосредственной работы с базой
    SaveStringSettingsFunction = [&](const QString &groupe, const QString &param, const QString &value){

        //SEND_TO_LOG( QString("ClimateControlSystem - ArchiveFunction[%1][%2]").arg(msgId).arg(value) );
        m_dbUnit.saveStringSettings(groupe, param, value);
    };


    //-------------------------------------------------------------------
    //! Связать функцию архивирования в скрипте с функцией непосредственной работы с базой
    SetCoolerModeFunction = [&](const bool &value){

        SEND_TO_LOG( QString("ClimateControlSystem - SetCoolerModeFunction[%1]").arg(value) );
#ifdef __arm__
        // GPIO22, pin 15
        // static int pinToGpioR2 [64]
        pinMode (3, OUTPUT) ;
        if(value)
            digitalWrite(3, 1);
        else
            digitalWrite(3, 0);
#endif // __arm__
    };

    //-------------------------------------------------------------------
    ScriptObject *scriptObject = ScriptUnit::getScriptObject("settings.password.new");

    if(scriptObject)
    {
        __PASSWORD__ = scriptObject->stringData();
        SEND_TO_LOG( QString("ClimateControlSystem - пароль задан: [%1]").arg(__PASSWORD__) );

        connect(scriptObject, &ScriptObject::dataChanged,
                this, &ClimateControlSystem::setPassword);
    }

    //-------------------------------------------------------------------
    coolerSetup();

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
void ClimateControlSystem::setPassword()
{
    ScriptObject *scriptObject = ScriptUnit::getScriptObject("settings.password.new");

    if(scriptObject)
    {
        __PASSWORD__ = scriptObject->stringData();

        SEND_TO_LOG( QString("ClimateControlSystem - пароль задан: [%1]").arg(__PASSWORD__) );
    }
}
//------------------------------------------------------------------------------------
//!
void ClimateControlSystem::coolerSetup()
{
    /*
    QProcess process;

    process.start("/bin/bash");
    process.waitForStarted(3000);

    //123456 - пароль. \n - имитирует нажатие Enter.
    process.write("echo 123456 | sudo -S rcnagios restart\n");
    process.waitForFinished(4000);
    */

#ifdef __arm__
    static const QString PROGRAM_NAME = "./temp_control.py";
    QProcess::startDetached( PROGRAM_NAME );
#endif // __arm__
}






















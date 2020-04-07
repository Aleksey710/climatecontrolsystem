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

        Q_UNUSED(value);
        //SEND_TO_LOG( QString("ClimateControlSystem - SetCoolerModeFunction[%1]").arg(value) );
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
    //! Задать функцию установки яркости
    SetScreenBrightness = [&](const int &value){

        Q_UNUSED(value);
        //SEND_TO_LOG( QString("ClimateControlSystem - SetScreenBrightness[%1]").arg(value) );
#ifdef __arm__

        if(value > 1 ||
           value < 7)
        {
            value = 440 + value*10;

            const QString command = QString("gpio -g mode 18 pwm; gpio pwmc 1000; gpio -g pwm 18 %1").arg(value);

            QProcess::startDetached( command );
        }
/*
            // Writes the value to the PWM register for the given pin.
            // The Raspberry Pi has one on-board PWM pin, pin 1 (BMC_GPIO 18, Phys 12) and
            // the range is 0-1024. Other PWM devices may have other PWM ranges.
            //
            // This function is not able to control the Pi’s on-board PWM when in Sys mode.
            pwmWrite (1, value) ;

            //--------------------------------------------------------
//            gpio -g pwm 18 1024
//            gpio -g mode 18 pwm
//            #set the pin as PWM
//            gpio pwmc 1000
//            gpio -g pwm 18 X #change the brightness, X ranges 0~1024
*/
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
    //! Настроить очистку базы
    setupDbSizeControl();

    //-------------------------------------------------------------------
    SEND_TO_LOG( QString("ClimateControlSystem - создан") );
}
//------------------------------------------------------------------------------------
//!
ClimateControlSystem::~ClimateControlSystem()
{
#ifdef __arm__
        // GPIO22, pin 15
        // static int pinToGpioR2 [64]
        pinMode (3, OUTPUT) ;

        digitalWrite(3, 0);
#endif // __arm__

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
void ClimateControlSystem::setupDbSizeControl()
{
    QTimer *timer = new QTimer(this);

    connect(timer, &QTimer::timeout, [=](){

        SEND_TO_LOG( QString("ClimateControlSystem - clearDb() timeout") );

        QFileInfo fileInfo("./conf/db.sqlite");

        if(fileInfo.exists())
        {
            qint64 size = fileInfo.size();

            if(size > CRITICAL_DB_SIZE)
            {
                SEND_TO_LOG( QString("ClimateControlSystem - clearDb()") );
                m_dbUnit.clearDb();
            }
        }
    });

    timer->start(1*60*1000);
}
//------------------------------------------------------------------------------------
//!




















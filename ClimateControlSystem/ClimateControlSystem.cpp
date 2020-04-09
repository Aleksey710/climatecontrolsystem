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
        int _value = value;

        if(_value >= 0 ||
           _value <= 7)
        {
            _value = 460 + (510-460)/7*_value;

            const QString command1 = QString("gpio -g pwm 18 1024");
            const QString command2 = QString("gpio -g mode 18 pwm");
            const QString command3 = QString("gpio pwmc 1000");
            const QString command4 = QString("gpio -g pwm 18 %1").arg(_value);

            QProcess::startDetached( command1 );
            QProcess::startDetached( command2 );
            QProcess::startDetached( command3 );
            QProcess::startDetached( command4 );
        }
#endif // __arm__
    };

    SetScreenBrightness(7);
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




















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
void ClimateControlSystem::rpiSetup()
{
    SEND_TO_LOG("*****************************************************************************************");
    SEND_TO_LOG( QString("ClimateControlSystem - setup Raspberry Pi") );


    //--------------------------------------------
    // LED Pin - wiringPi pin 0 is BCM_GPIO 17.
/*
#ifdef __arm__
    #define	LED	0

    SEND_TO_LOG("Raspberry Pi blink");

    wiringPiSetup () ;
    pinMode (0, OUTPUT) ;

    for (int i = 0; i < 10; ++i)
    {
        digitalWrite (LED, HIGH) ;	// On
        delay (500) ;		// mS
        digitalWrite (LED, LOW) ;	// Off
        delay (500) ;
    }
#endif // __arm__
*/
    SEND_TO_LOG("*****************************************************************************************");  
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






















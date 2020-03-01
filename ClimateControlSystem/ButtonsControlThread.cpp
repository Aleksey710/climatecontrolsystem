#include "ButtonsControlThread.h"

//------------------------------------------------------------------------------------
//!
ButtonsControlThread::ButtonsControlThread(QObject *parent)
                     :QThread(parent),
                      m_bt1_state ( 0 ),
                      m_bt2_state ( 0 ),
                      m_bt3_state ( 0 ),
                      m_bt4_state ( 0 )
{
#ifdef __arm__

    wiringPiSetup() ;

    pinMode (BUTTON_1_PIN, INPUT) ;
    pinMode (BUTTON_2_PIN, INPUT) ;
    pinMode (BUTTON_3_PIN, INPUT) ;
    pinMode (BUTTON_4_PIN, INPUT) ;
    //pinMode (BUTTON_1_PIN, INPUT) ;

#endif // __arm__
}
//------------------------------------------------------------------------------------
//!
void ButtonsControlThread::run()
{
    //emit resultReady(result);

    for (;;)
    {
        int button_1_state = 0;
        int button_2_state = 0;
        int button_3_state = 0;
        int button_4_state = 0;

#ifdef __arm__
        button_1_state = digitalRead (BUTTON_1_PIN);
        button_2_state = digitalRead (BUTTON_2_PIN);
        button_3_state = digitalRead (BUTTON_3_PIN);
        button_4_state = digitalRead (BUTTON_4_PIN);
#endif // __arm__

        qDebug() << "ButtonsControlThread"
                 << button_1_state
                 << button_2_state
                 << button_3_state
                 << button_4_state;
    }
}
//------------------------------------------------------------------------------------
//!

#include "ButtonsControlThread.h"

//------------------------------------------------------------------------------------
//!
ButtonsControlThread::ButtonsControlThread(QObject *parent)
                     :QThread(parent),
                      m_bt_1_state ( 0 ),
                      m_bt_2_state ( 0 ),
                      m_bt_3_state ( 0 ),
                      m_bt_4_state ( 0 ),
                      m_bt_off_state ( 0 )
{
#ifdef __arm__

    wiringPiSetup() ;

    pinMode (BUTTON_1_PIN,      INPUT) ;
    pinMode (BUTTON_2_PIN,      INPUT) ;
    pinMode (BUTTON_3_PIN,      INPUT) ;
    pinMode (BUTTON_4_PIN,      INPUT) ;
    pinMode (BUTTON_OFF_PIN,    INPUT) ;

#endif // __arm__
}
//------------------------------------------------------------------------------------
//!
void ButtonsControlThread::run()
{
    for (;;)
    {
        int bt_1_state      = 0;
        int bt_2_state      = 0;
        int bt_3_state      = 0;
        int bt_4_state      = 0;
        int bt_off_state    = 0;

#ifdef __arm__
        bt_1_state = digitalRead    (BUTTON_1_PIN);
        bt_2_state = digitalRead    (BUTTON_2_PIN);
        bt_3_state = digitalRead    (BUTTON_3_PIN);
        bt_4_state = digitalRead    (BUTTON_4_PIN);
        bt_off_state = digitalRead  (BUTTON_OFF_PIN);
#endif // __arm__

        //---------------------------------------------------
        if(m_bt_1_state == 1 && bt_1_state == 0)
            emit bt_1_pressed();

        if(m_bt_2_state == 1 && bt_2_state == 0)
            emit bt_2_pressed();

        if(m_bt_3_state == 1 && bt_3_state == 0)
            emit bt_3_pressed();

        if(m_bt_4_state == 1 && bt_4_state == 0)
            emit bt_4_pressed();

        if(m_bt_off_state == 1 && bt_off_state == 0)
            emit bt_off_pressed();
        //---------------------------------------------------
        if(m_bt_1_state == 0 && bt_1_state == 1)
            emit bt_1_released();

        if(m_bt_2_state == 0 && bt_2_state == 1)
            emit bt_2_released();

        if(m_bt_3_state == 0 && bt_3_state == 1)
            emit bt_3_released();

        if(m_bt_4_state == 0 && bt_4_state == 1)
            emit bt_4_released();

        if(m_bt_off_state == 0 && bt_off_state == 1)
            emit bt_off_released();
        //---------------------------------------------------
        /*
        qDebug() << "ButtonsControlThread"
                 << bt_1_state
                 << bt_2_state
                 << bt_3_state
                 << bt_4_state
                 << bt_off_state ;
        */
        //---------------------------------------------------
        m_bt_1_state    = bt_1_state;
        m_bt_2_state    = bt_2_state;
        m_bt_3_state    = bt_3_state;
        m_bt_4_state    = bt_4_state;
        m_bt_off_state  = bt_off_state;

        usleep(500);
    }
}
//------------------------------------------------------------------------------------
//!

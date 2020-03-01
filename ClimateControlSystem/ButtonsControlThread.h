#ifndef BUTTONSCONTROLTHREAD_H
#define BUTTONSCONTROLTHREAD_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QThread>
//#include <>
//#include <>
//#include <>
//#include <>


#include "Log.h"
//#include ".h"
//#include ".h"
//#include ".h"
//------------------------------------------------------------------------------------
#ifdef __arm__
#include "wiringPi.h"
#endif // __arm__
//------------------------------------------------------------------------------------
//!
class ButtonsControlThread : public QThread
{
        Q_OBJECT

        // wiringPiMode = WPI_MODE_PINS;
        // wiringPiMode = WPI_MODE_PHYS;
        // wiringPiMode = WPI_MODE_GPIO;

        static const int BUTTON_1_PIN   = 5;  // F1 - GPIO5   pin 29
        static const int BUTTON_2_PIN   = 6;  // F2 - GPIO6   pin 31
        static const int BUTTON_3_PIN   = 33;  // F3 - GPIO13  pin 33
        static const int BUTTON_4_PIN   = 35;  // F4 - GPIO19  pin 35
        static const int BUTTON_OFF_PIN = 37;   // F1 - GPIO26  pin 37

    public:
        explicit ButtonsControlThread(QObject *parent = nullptr);

        virtual void run() override;

    signals:
        void bt_1_pressed();
        void bt_2_pressed();
        void bt_3_pressed();
        void bt_4_pressed();
        void bt_off_pressed();

        void bt_1_released();
        void bt_2_released();
        void bt_3_released();
        void bt_4_released();
        void bt_off_released();

    private:
        int m_bt_1_state;
        int m_bt_2_state;
        int m_bt_3_state;
        int m_bt_4_state;
        int m_bt_off_state;

};
//------------------------------------------------------------------------------------
#endif // BUTTONSCONTROLTHREAD_H

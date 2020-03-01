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
extern int wiringPiMode;
//------------------------------------------------------------------------------------
//!
class ButtonsControlThread : public QThread
{
        Q_OBJECT

        // wiringPiMode = WPI_MODE_PINS;
        // wiringPiMode = WPI_MODE_PHYS;
        // wiringPiMode = WPI_MODE_GPIO;

        static const int BUTTON_1_PIN = 29;  // F1 - GPIO5   pin 29
        static const int BUTTON_2_PIN = 31;  // F2 - GPIO6   pin 31
        static const int BUTTON_3_PIN = 33;  // F3 - GPIO13  pin 33
        static const int BUTTON_4_PIN = 35;  // F4 - GPIO19  pin 35

        //static const int BUTTON_1_PIN = 0;  // F1 - GPIO5  pin 29

    public:
        explicit ButtonsControlThread(QObject *parent = nullptr);

        virtual void run() override;

    signals:
        void bt1_pressed();
        void bt2_pressed();
        void bt3_pressed();
        void bt4_pressed();
        //void bt1_pressed();

        void bt1_released();
        void bt2_released();
        void bt3_released();
        void bt4_released();
        //void bt1_released();

    private:
        int m_bt1_state;
        int m_bt2_state;
        int m_bt3_state;
        int m_bt4_state;
        //int bt1_state;

};
//------------------------------------------------------------------------------------
//#endif // __arm__
#endif // BUTTONSCONTROLTHREAD_H

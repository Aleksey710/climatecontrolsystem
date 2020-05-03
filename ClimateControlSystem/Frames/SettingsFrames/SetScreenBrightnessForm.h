#ifndef SETSCREENBRIGHTNESSFORM_H
#define SETSCREENBRIGHTNESSFORM_H
//------------------------------------------------------------------------------------
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QProcess>
#include <QString>
#include <QObject>

#include <functional>
//#include <>
//#include <>

/*
#ifdef __arm__
    #include <wiringPi.h>
#endif
*/
#include "Log.h"
#include "ScriptObject.h"
#include "ScriptUnit.h"

#define BRIGHTNESS_LEVEL_INVERT        1

#define BRIGHTNESS_LEVEL_MIN           0
#define BRIGHTNESS_LEVEL_MAX           7
#define BRIGHTNESS_LEVEL_COUNT         ( ( BRIGHTNESS_LEVEL_MAX - BRIGHTNESS_LEVEL_MIN ) + 1 )

#if ( BRIGHTNESS_LEVEL_INVERT == 0 )
    #define BRIGHTNESS_LEVEL_CUR( cur )    ( cur )
#else
    #define BRIGHTNESS_LEVEL_CUR( cur )    ( BRIGHTNESS_LEVEL_MAX - cur )
#endif

//------------------------------------------------------------------------------------
namespace Ui {
class SetScreenBrightnessForm;
}
//------------------------------------------------------------------------------------
//!
class SetScreenBrightnessForm : public QWidget
{
        Q_OBJECT

    public:    
        explicit SetScreenBrightnessForm(QWidget *parent = nullptr);
        virtual ~SetScreenBrightnessForm();

        enum { BrightnessLevelMin = 0, BrightnessLevelMax = 7 };
        static void initPWM();
        static void setBrightnessLevel( const int &value );

    private:
        Ui::SetScreenBrightnessForm *ui;
};
//------------------------------------------------------------------------------------
#endif // SETSCREENBRIGHTNESSFORM_H

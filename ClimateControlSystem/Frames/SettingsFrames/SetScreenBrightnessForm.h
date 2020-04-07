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

// /*
#ifdef __arm__
    #include <wiringPi.h>
#endif
// */
#include "Log.h"

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

    private:
        Ui::SetScreenBrightnessForm *ui;
};
//------------------------------------------------------------------------------------
#endif // SETSCREENBRIGHTNESSFORM_H

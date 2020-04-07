#include "SetScreenBrightnessForm.h"
#include "ui_SetScreenBrightnessForm.h"

//------------------------------------------------------------------------------------
//!
SetScreenBrightnessForm::SetScreenBrightnessForm(QWidget *parent)
                        :QWidget(parent),
                         ui(new Ui::SetScreenBrightnessForm)
{
    ui->setupUi(this);

    setWindowTitle(tr("SetScreenBrightnessForm"));

    setWindowFlags(Qt::ToolTip);
    setAttribute(Qt::WA_AlwaysShowToolTips);
    setAttribute(Qt::WA_DeleteOnClose);

    setWindowModality(Qt::ApplicationModal);


    connect(ui->pbSet, &QPushButton::released, [=](){
        int value = ui->leBrightness->text().toInt();

        Q_UNUSED(value);
        SEND_TO_LOG( QString("SetScreenBrightnessForm - set screen brightness[%1]").arg(value) );
#ifdef __arm__
        if(value < 0 ||
           value > 1024)
        {
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
        }
#endif // __arm__
    });

        connect(ui->pbClose, &QPushButton::released, [=](){
            close();
        });
}
//------------------------------------------------------------------------------------
//!
SetScreenBrightnessForm::~SetScreenBrightnessForm()
{
    delete ui;
    SEND_TO_LOG( QString("SetScreenBrightnessForm - удален") );
}
//------------------------------------------------------------------------------------
//!

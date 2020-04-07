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
            // https://github.com/WiringPi/WiringPi/blob/master/examples/pwm.c

            pinMode (1, PWM_OUTPUT) ;

            pwmWrite (1, value) ;
            delay (1) ;
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

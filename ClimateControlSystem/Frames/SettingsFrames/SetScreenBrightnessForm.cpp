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
        if(value > 1 ||
           value < 7)
        {
            value = 440 + value*10;

            const QString command = QString("gpio -g mode 18 pwm; gpio pwmc 1000; gpio -g pwm 18 %1").arg(value);

            QProcess::startDetached( command );
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

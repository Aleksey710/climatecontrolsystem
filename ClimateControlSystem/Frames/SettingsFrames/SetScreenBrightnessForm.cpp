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

    //-------------------------------------------------
    ScriptObject *dataScriptObject = ScriptUnit::getScriptObject("settings.screen.max");

    if(dataScriptObject)
        ui->sbBrightness->setValue(static_cast<int>(dataScriptObject->data()));

    //-------------------------------------------------
    connect(ui->pbSet, &QPushButton::released, [=](){
        int value = ui->sbBrightness->value();

        Q_UNUSED(value);
        SEND_TO_LOG( QString("SetScreenBrightnessForm - set screen brightness[%1]").arg(value) );
#ifdef __arm__
        if(value >= 0 ||
           value <= 7)
        {
            value = 440 + value*10;

            const QString command1 = QString("gpio -g mode 18 pwm; ");
            const QString command2 = QString("gpio pwmc 1000; ");
            const QString command3 = QString("gpio -g pwm 18 %1").arg(value);

            QProcess::startDetached( command1 );
            QProcess::startDetached( command2 );
            QProcess::startDetached( command3 );
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

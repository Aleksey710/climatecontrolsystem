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
        int _value = ui->sbBrightness->value();

        Q_UNUSED(_value);
        SEND_TO_LOG( QString("SetScreenBrightnessForm - set screen brightness[%1]").arg(_value) );
#ifdef __arm__
        if(_value >= 0 ||
           _value <= 7)
        {
            _value = 440 + _value*10;

            const QString command1 = QString("gpio -g mode 18 pwm; ");
            const QString command2 = QString("gpio pwmc 1000; ");
            const QString command3 = QString("gpio -g pwm 18 %1").arg(_value);

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

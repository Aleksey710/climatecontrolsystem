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
        // Задание нового значения
        int value = ui->sbBrightness->value();

        setBrightnessLevel( value );
    });

    // Настройка ШИМ
    initPWM( );

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


/*
https://www.youtube.com/watch?v=Zjr69DxgeW0
pwFreq = 19.2MHz/(pwmc*pwmr)
gpio mode 23 pwm - Set GPIO 13 to PWM mode
gpio pwm-ms - put PWM in mark-space ode
gpio pwmr 4000 = Range (default is 1024)
gpio pwmc 4092 - Clock divider 2 to 4095

gpio pwm 23 1000 =  Set PWM of GPIO 13 to 1000 (25% of 4000)
man gpio - detiled anual and all commands
gpio readall - See the status of all GPIO pins
https://books.google.com.ua/books?id=1FUnCgAAQBAJ&pg=PA154&lpg=PA154&dq=%22gpio+pwmc+%22;&source=bl&ots=Y2fKe4qI-P&sig=ACfU3U0_whbdQ8G66fMqU1Esuh9iJ163Og&hl=ru&sa=X&ved=2ahUKEwjuqOvjiIzpAhVxkosKHa_6DCsQ6AEwBXoECAkQAQ#v=onepage&q=%22gpio%20pwmc%20%22%3B&f=false
pwFreq = 19200000/(1000*1024) = 18.75 Hz


Период - 1500 мкс = 100%
Мин    - 10 мкс
Макс   - 1360 мкс
$ gpio pwmc 192
$ gpio pwmr 150
freq = (19200000/192)/150 = 666.66667; T = 0.0015 мс
*/
#define PWM_MIN_VALUE 10
#define PWM_MAX_VALUE 136
// Все умножается на 10 и делится результат для повышения точности
#define PWM_SEP_VALUE ( ( ( PWM_MAX_VALUE * 10 - PWM_MIN_VALUE * 10 ) / ( BRIGHTNESS_LEVEL_COUNT - 1 ) ) / 10 )


void SetScreenBrightnessForm::initPWM( )
{
    SEND_TO_LOG( QString("SetScreenBrightnessForm::initPWM") );
    QProcess::execute( "gpio -g mode 18 pwm" );
    QProcess::execute( "gpio pwm-ms" );
    QProcess::execute( "gpio pwmc 192" );
    QProcess::execute( "gpio pwmr 150" );
}

void SetScreenBrightnessForm::setBrightnessLevel( const int &value )
{
    if( value >= BRIGHTNESS_LEVEL_MIN && value <= BRIGHTNESS_LEVEL_MAX )
    {
        int pwm = PWM_MIN_VALUE + ( PWM_SEP_VALUE * BRIGHTNESS_LEVEL_CUR( value ) );

        QProcess::execute( QString("gpio -g pwm 18 %1").arg( pwm ) );

        SEND_TO_LOG( QString("SetScreenBrightnessForm::setBrightnessLevel - Level %1 PWM %2 %3 %4")
                     .arg( value ).arg( pwm ).arg( PWM_SEP_VALUE ).arg(BRIGHTNESS_LEVEL_COUNT ) );
    }
}





#include "MainFrame.h"

//------------------------------------------------------------------------------------
//!
MainFrame::MainFrame(QWidget *parent)
          :AbstractFrame(parent)
{
    setObjectName("MainFrame");

    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->setMargin(1);
    mainLayout->setVerticalSpacing(1);
    mainLayout->setHorizontalSpacing(1);

    GigitalIndicatorWidget *widget0 = new GigitalIndicatorWidget("Напруга мережi", "В", 0, 200);
    setupDisplay("display.U_I.U_net", widget0);

    GigitalIndicatorWidget *widget1 = new GigitalIndicatorWidget("Струм АКБ", "А", -150, 160);
    setupDisplay("display.U_I.I_bat", widget1);

    GigitalIndicatorWidget *widget2 = new GigitalIndicatorWidget("Струм генератора", "А", 0, 250);
    setupDisplay("display.U_I.I_gen", widget2);

    m_tUstWidget = new GigitalIndicatorWidget("Корекцiя температури", "°C", 22, 26);
    setupDisplay("display.temp.t_ust", m_tUstWidget);

    ScriptObject *settingsScriptObject = ScriptUnit::getScriptObject("settings.temp.sut");
    ScriptObject *displayScriptObject = ScriptUnit::getScriptObject("display.temp.t_ust");

    if(settingsScriptObject && displayScriptObject)
    {
        //! Начальная инициализация display.temp.t_ust
        displayScriptObject->setData(settingsScriptObject->data());
    }

    GigitalIndicatorWidget *widget4 = new GigitalIndicatorWidget("Темп. салона", "°C", -20, 60);
    setupDisplay("display.temp.t_sal", widget4);

    GigitalIndicatorWidget *widget5 = new GigitalIndicatorWidget("Темп. зовнiшня", "°C", -40, 60);
    setupDisplay("display.temp.t_nv", widget5);

    DateTimeWidget *dateTimeWidget = new DateTimeWidget();

    StatesDisplayWidget *statesDisplayWidget = new StatesDisplayWidget();

    mainLayout->addWidget(widget0,              0,0,1,1);
    mainLayout->addWidget(widget1,              0,1,1,1);
    mainLayout->addWidget(widget2,              0,2,1,1);
    mainLayout->addWidget(m_tUstWidget,         0,3,1,1);

    mainLayout->addWidget(widget4,              1,3,1,1);
    mainLayout->addWidget(widget5,              2,3,1,1);

    mainLayout->addWidget(dateTimeWidget,       3,3,1,1);

    mainLayout->addWidget(statesDisplayWidget,  1,0,3,3);

    //! Задать виджету слой
    setLayout(mainLayout);

    SEND_TO_LOG( QString("%1 - создан").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
MainFrame::~MainFrame()
{

}
//------------------------------------------------------------------------------------
//!
void MainFrame::tUstPlus()
{
    int value = static_cast<int>(m_tUstWidget->data());

    if(value == 26)
        return;

    ScriptObject *scriptObject = ScriptUnit::getScriptObject("settings.temp.sut");

    if(scriptObject)
    {
        scriptObject->setData(value + 1);
    }

    //m_tUstWidget->setData(value + 1);
}
//------------------------------------------------------------------------------------
//!
void MainFrame::tUstMinus()
{
    int value = static_cast<int>(m_tUstWidget->data());

    if(value == 22)
        return;

    ScriptObject *scriptObject = ScriptUnit::getScriptObject("settings.temp.sut");

    if(scriptObject)
    {
        scriptObject->setData(value - 1);
    }

    //m_tUstWidget->setData(value - 1);
}
//------------------------------------------------------------------------------------
//!


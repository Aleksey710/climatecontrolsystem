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

    GigitalIndicatorWidget *widget0 = createGigitalIndicatorWidget("display.U_I.U_net",
                                                                   "Напруга мережi",
                                                                   "В",
                                                                   "settings.lim.mivn",
                                                                   "settings.lim.mavn");

    GigitalIndicatorWidget *widget1 = createGigitalIndicatorWidget("display.U_I.I_bat",
                                                                   "Струм АКБ",
                                                                   "А",
                                                                   "settings.lim.micb",
                                                                   "settings.lim.macb");

    GigitalIndicatorWidget *widget2 = createGigitalIndicatorWidget("display.U_I.I_gen",
                                                                   "Струм генератора",
                                                                   "А",
                                                                   "settings.lim.micg",
                                                                   "settings.lim.macg");

    m_tUstWidget = createGigitalIndicatorWidget("display.temp.t_ust",
                                                "Корекцiя температури",
                                                "°C",
                                                22,
                                                26);

    ScriptObject *settingsScriptObject = ScriptUnit::getScriptObject("settings.temp.sut");
    ScriptObject *displayScriptObject = ScriptUnit::getScriptObject("display.temp.t_ust");

    if(settingsScriptObject && displayScriptObject)
    {
        //! Начальная инициализация display.temp.t_ust
        displayScriptObject->setData(settingsScriptObject->data());
    }

    GigitalIndicatorWidget *widget4 = createGigitalIndicatorWidget("display.temp.t_sal",
                                                                   "Темп. салона",
                                                                   "°C",
                                                                   "settings.lim.miti",
                                                                   "settings.lim.mati");

    GigitalIndicatorWidget *widget5 = createGigitalIndicatorWidget("display.U_I.I_gen",
                                                                   "Темп. зовнiшня",
                                                                   "°C",
                                                                   "settings.lim.mito",
                                                                   "settings.lim.mato");

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


#include "StatesDisplayWidget.h"

//------------------------------------------------------------------------------------
//!
StatesDisplayWidget::StatesDisplayWidget(QWidget *parent)
                    :QWidget(parent),
                     m_mainLayout ( new QGridLayout() )
{
    setObjectName("StatesDisplayWidget");

    setStyleSheet(
        "QWidget{ "
        "padding: 0px;"
        "margin: 0px;"
//        "border: 1px solid #000000;"
//        "border-radius : 5px;"
//        "color: blue;"
//        "background-color: yellow;"
        "}"
    );

    m_mainLayout->setMargin(0);
    m_mainLayout->setVerticalSpacing(0);
    m_mainLayout->setHorizontalSpacing(0);

    //---------------------------------------------------------

    setupRow1();
    setupRow2();
    setupRow3();
    setupRow4();
    setupRow5();
    setupRow6();
    setupRow7();
    setupRow8();

    //---------------------------------------------------------
    //! Задать виджету слой
    setLayout(m_mainLayout);

    SEND_TO_LOG( QString("%1 - создан").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
StatesDisplayWidget::~StatesDisplayWidget()
{
    SEND_TO_LOG( QString("%1 - удален").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
void StatesDisplayWidget::setupRow1()
{
    MsgWidget *lowColumn1MsgWidget = new MsgWidget("vr.msg.automodeDisabled",
                                                   "Не можливий авто.режим",
                                                   "#FFFFFF", "#FF0000");
    MsgWidget *lowColumn2MsgWidget = nullptr;
    MsgWidget *highColumn1MsgWidget = new MsgWidget("vr.msg.BVVConnError",
                                                    "Перейти в резервний режим управління",
                                                    /*"#FFFFFF",*/ "#FF0000");
    MsgWidget *highColumn2MsgWidget = nullptr;

    RowMsgWidget *rowMsgWidget = new RowMsgWidget(lowColumn1MsgWidget,
                                                  lowColumn2MsgWidget,
                                                  highColumn1MsgWidget,
                                                  highColumn2MsgWidget);
    m_mainLayout->addWidget(rowMsgWidget, 0,0);
}
//------------------------------------------------------------------------------------
//!
void StatesDisplayWidget::setupRow2()
{
    MsgWidget *lowColumn1MsgWidget = new MsgWidget("display.BVV.NVO",
                                                   "НВО увiмкнено",
                                                   "#005500");

    MsgWidget *lowColumn2MsgWidget = new MsgWidget("display.BVV.cooling",
                                                   "Охолодження увiмкнено",
                                                   "#005500");

    MsgWidget *highColumn1MsgWidget = new MsgWidget("display.BVV.crash",
                                                    "Аварiя",
                                                    "#FFFFFF", "#FF0000");

    MsgWidget *highColumn2MsgWidget = new MsgWidget("display.BVV.r_insulation",
                                                    "R iзоляцiї < 1 kOm",
                                                    /*"#FFFFFF", */"#FF0000");

    RowMsgWidget *rowMsgWidget = new RowMsgWidget(lowColumn1MsgWidget,
                                                  lowColumn2MsgWidget,
                                                  highColumn1MsgWidget,
                                                  highColumn2MsgWidget);
    m_mainLayout->addWidget(rowMsgWidget, 1,0);
}
//------------------------------------------------------------------------------------
//!
void StatesDisplayWidget::setupRow3()
{
    MsgWidget *lowColumn1MsgWidget = new MsgWidget("display.BVV.VVO_1",
                                                   "ВВО гр.1 увiмкнено",
                                                   "#005500");

    MsgWidget *lowColumn2MsgWidget = new MsgWidget("display.BVV.VVO_2",
                                                   "ВВО гр.2 увiмкнено",
                                                   "#005500");

    MsgWidget *highColumn1MsgWidget = new MsgWidget("vr.msg.u3000Error",
                                                    "Вiдсутня напруга 3000В",
                                                    /*"#FFFFFF",*/ "#FF0000");
    MsgWidget *highColumn2MsgWidget = nullptr;

    RowMsgWidget *rowMsgWidget = new RowMsgWidget(lowColumn1MsgWidget,
                                                  lowColumn2MsgWidget,
                                                  highColumn1MsgWidget,
                                                  highColumn2MsgWidget);
    m_mainLayout->addWidget(rowMsgWidget, 2,0);
}
//------------------------------------------------------------------------------------
//!
void StatesDisplayWidget::setupRow4()
{
    MsgWidget *lowColumn1MsgWidget = new MsgWidget("vr.msg.A9ConnError",
                                                   "Не можлива корекція температури",
                                                   "#FFFFFF", "#FF0000");
    MsgWidget *lowColumn2MsgWidget = nullptr;

    //---------------------------------------------------------------
    int tCotla = 0;

    ScriptObject *tCotlaScriptObject = ScriptUnit::getScriptObject("settings.temp.bt");

    if(tCotlaScriptObject)
    {
        tCotla = tCotlaScriptObject->data();
    }
    //---------------------------------------------------------------

    MsgWidget *highColumn1MsgWidget = new MsgWidget("vr.kotl.overheat",
                                                    QString("Температура води в котлі >%1 °C").arg(tCotla),
                                                    /*"#FFFFFF",*/ "#FF0000");
    MsgWidget *highColumn2MsgWidget = nullptr;

    RowMsgWidget *rowMsgWidget = new RowMsgWidget(lowColumn1MsgWidget,
                                                  lowColumn2MsgWidget,
                                                  highColumn1MsgWidget,
                                                  highColumn2MsgWidget);
    m_mainLayout->addWidget(rowMsgWidget, 3,0);
}
//------------------------------------------------------------------------------------
//!
void StatesDisplayWidget::setupRow5()
{
    MsgWidget *lowColumn1MsgWidget = nullptr;
    MsgWidget *lowColumn2MsgWidget = nullptr;
    MsgWidget *highColumn1MsgWidget = new MsgWidget("display.BVV.cont1Failure",
                                                    "Вiдмова контура охолодження 1",
                                                    /*"#FFFFFF",*/ "#FF0000");
    MsgWidget *highColumn2MsgWidget = new MsgWidget("display.BVV.cont2Failure",
                                                    "Вiдмова контура охолодження 2",
                                                    /*"#FFFFFF",*/ "#FF0000");

    RowMsgWidget *rowMsgWidget = new RowMsgWidget(lowColumn1MsgWidget,
                                                  lowColumn2MsgWidget,
                                                  highColumn1MsgWidget,
                                                  highColumn2MsgWidget);
    m_mainLayout->addWidget(rowMsgWidget, 4,0);
}
//------------------------------------------------------------------------------------
//!
void StatesDisplayWidget::setupRow6()
{
    MsgWidget *lowColumn1MsgWidget = new MsgWidget("display.BVV.automode",
                                                   "Авто. режим клімат. установки",
                                                   "#005500");
    MsgWidget *lowColumn2MsgWidget = nullptr;
    MsgWidget *highColumn1MsgWidget = new MsgWidget("vr.msg.ImaxGeneral",
                                                    "Високий струм",
                                                    /*"#FFFFFF",*/ "#FF0000");
    MsgWidget *highColumn2MsgWidget = new MsgWidget("vr.msg.Umax",
                                                    "Висока напруга",
                                                    /*"#FFFFFF",*/ "#FF0000");

    RowMsgWidget *rowMsgWidget = new RowMsgWidget(lowColumn1MsgWidget,
                                                  lowColumn2MsgWidget,
                                                  highColumn1MsgWidget,
                                                  highColumn2MsgWidget);
    m_mainLayout->addWidget(rowMsgWidget, 5,0);
}
//------------------------------------------------------------------------------------
//!
void StatesDisplayWidget::setupRow7()
{
    MsgWidget *lowColumn1MsgWidget = new MsgWidget("display.BVV.ventilation",
                                                   "Вентиляція увімкнена",
                                                   "#005500");
    MsgWidget *lowColumn2MsgWidget = nullptr;
    MsgWidget *highColumn1MsgWidget = new MsgWidget("vr.msg.Umin",
                                                    "Батарея розряджена",
                                                    /*"#FFFFFF",*/ "#FF0000");
    MsgWidget *highColumn2MsgWidget = nullptr;

    RowMsgWidget *rowMsgWidget = new RowMsgWidget(lowColumn1MsgWidget,
                                                  lowColumn2MsgWidget,
                                                  highColumn1MsgWidget,
                                                  highColumn2MsgWidget);
    m_mainLayout->addWidget(rowMsgWidget, 6,0);
}
//------------------------------------------------------------------------------------
//!
void StatesDisplayWidget::setupRow8()
{
    MsgWidget *lowColumn1MsgWidget = new MsgWidget("display.BVV.condWorked",
                                                   "Кондицiонер РОБОТА",
                                                   "#005500");
    MsgWidget *lowColumn2MsgWidget = new MsgWidget("display.BVV.heater",
                                                   "Нагрів увімкнено",
                                                   "#005500");

    MsgWidget *highColumn1MsgWidget = new MsgWidget("display.BVV.condFailure",
                                                    "Кондицiонер ВIДМОВА",
                                                    /*"#FFFFFF",*/ "#FF0000");
    MsgWidget *highColumn2MsgWidget = nullptr;

    RowMsgWidget *rowMsgWidget = new RowMsgWidget(lowColumn1MsgWidget,
                                                  lowColumn2MsgWidget,
                                                  highColumn1MsgWidget,
                                                  highColumn2MsgWidget);
    m_mainLayout->addWidget(rowMsgWidget, 7,0);
}
//------------------------------------------------------------------------------------
//!

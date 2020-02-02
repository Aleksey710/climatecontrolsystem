#include "StatesDisplayWidget.h"

//------------------------------------------------------------------------------------
//!
StatesDisplayWidget::StatesDisplayWidget(QWidget *parent)
                    :QWidget(parent),
                     m_mainLayout ( new QGridLayout() )
{
    setObjectName("StatesDisplayWidget");

//    setStyleSheet(
//        "QWidget{ "
//        "padding: 1px;"
//        "margin: 1px;"
////        "border: 1px solid #000000;"
////        "border-radius : 5px;"
////        "color: blue;"
////        "background-color: yellow;"
//        "}"
//    );

    m_mainLayout->setMargin(0);
    m_mainLayout->setVerticalSpacing(1);
    m_mainLayout->setHorizontalSpacing(1);

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
    MsgWidget *lowColumn1MsgWidget = nullptr;
    MsgWidget *lowColumn2MsgWidget = nullptr;
    MsgWidget *highColumn1MsgWidget = nullptr;
    MsgWidget *highColumn2MsgWidget = nullptr;

    RowMsgWidget *rowMsgWidget = new RowMsgWidget(lowColumn1MsgWidget,
                                                  lowColumn2MsgWidget,
                                                  highColumn1MsgWidget,
                                                  highColumn2MsgWidget);
    m_mainLayout->addWidget(rowMsgWidget, 0,0,1,1);
}
//------------------------------------------------------------------------------------
//!
void StatesDisplayWidget::setupRow2()
{
    MsgWidget *lowColumn1MsgWidget = new MsgWidget("display.BVV.crash",
                                                   "Аварiя");

    MsgWidget *lowColumn2MsgWidget = new MsgWidget("display.BVV.r_insulation",
                                                   "R iзоляцiї < 1 kOm");

    MsgWidget *highColumn1MsgWidget = new MsgWidget("display.BVV.NVO",
                                                    "НВО увiмкнено");

    MsgWidget *highColumn2MsgWidget = new MsgWidget("display.BVV.cooling",
                                                    "Охолодження увiмкнено");

    RowMsgWidget *rowMsgWidget = new RowMsgWidget(lowColumn1MsgWidget,
                                                  lowColumn2MsgWidget,
                                                  highColumn1MsgWidget,
                                                  highColumn2MsgWidget);
    m_mainLayout->addWidget(rowMsgWidget, 1,0,1,1);
}
//------------------------------------------------------------------------------------
//!
void StatesDisplayWidget::setupRow3()
{
    MsgWidget *lowColumn1MsgWidget = new MsgWidget("display.BVV.u3000",
                                                   "Вiдсутня напруга 3000В");

    MsgWidget *lowColumn2MsgWidget = nullptr;

    MsgWidget *highColumn1MsgWidget = new MsgWidget("display.BVV.VVO_1",
                                                    "ВВО гр.1 увiмкнено");
    MsgWidget *highColumn2MsgWidget = new MsgWidget("display.BVV.VVO_2",
                                                    "ВВО гр.2 увiмкнено");

    RowMsgWidget *rowMsgWidget = new RowMsgWidget(lowColumn1MsgWidget,
                                                  lowColumn2MsgWidget,
                                                  highColumn1MsgWidget,
                                                  highColumn2MsgWidget);
    m_mainLayout->addWidget(rowMsgWidget, 2,0,1,1);
}
//------------------------------------------------------------------------------------
//!
void StatesDisplayWidget::setupRow4()
{
    MsgWidget *lowColumn1MsgWidget = new MsgWidget("display.BVV.u3000",
                                                   "Температура води в котлі >ХХ о С");
    MsgWidget *lowColumn2MsgWidget = nullptr;
    MsgWidget *highColumn1MsgWidget = new MsgWidget("display.BVV.u3000",
                                                    "Не можлива корекція температури");
    MsgWidget *highColumn2MsgWidget = nullptr;

    RowMsgWidget *rowMsgWidget = new RowMsgWidget(lowColumn1MsgWidget,
                                                  lowColumn2MsgWidget,
                                                  highColumn1MsgWidget,
                                                  highColumn2MsgWidget);
    m_mainLayout->addWidget(rowMsgWidget, 3,0,1,1);
}
//------------------------------------------------------------------------------------
//!
void StatesDisplayWidget::setupRow5()
{
    MsgWidget *lowColumn1MsgWidget = new MsgWidget("display.BVV.cont1Failure",
                                                   "Вiдмова контура охолодження 1");
    MsgWidget *lowColumn2MsgWidget = new MsgWidget("display.BVV.cont2Failure",
                                                   "Вiдмова контура охолодження 2");
    MsgWidget *highColumn1MsgWidget = nullptr;
    MsgWidget *highColumn2MsgWidget = nullptr;

    RowMsgWidget *rowMsgWidget = new RowMsgWidget(lowColumn1MsgWidget,
                                                  lowColumn2MsgWidget,
                                                  highColumn1MsgWidget,
                                                  highColumn2MsgWidget);
    m_mainLayout->addWidget(rowMsgWidget, 4,0,1,1);
}
//------------------------------------------------------------------------------------
//!
void StatesDisplayWidget::setupRow6()
{
    MsgWidget *lowColumn1MsgWidget = new MsgWidget("display.BVV.cont1Failure",
                                                   "Високий струм");
    MsgWidget *lowColumn2MsgWidget = new MsgWidget("display.BVV.cont1Failure",
                                                   "Висока напруга");
    MsgWidget *highColumn1MsgWidget = new MsgWidget("display.BVV.automode",
                                                    "Авто. режим клімат. установки");
    MsgWidget *highColumn2MsgWidget = nullptr;

    RowMsgWidget *rowMsgWidget = new RowMsgWidget(lowColumn1MsgWidget,
                                                  lowColumn2MsgWidget,
                                                  highColumn1MsgWidget,
                                                  highColumn2MsgWidget);
    m_mainLayout->addWidget(rowMsgWidget, 5,0,1,1);
}
//------------------------------------------------------------------------------------
//!
void StatesDisplayWidget::setupRow7()
{
    MsgWidget *lowColumn1MsgWidget = new MsgWidget("display.BVV.cont1Failure",
                                                   "Батарея розряджена");
    MsgWidget *lowColumn2MsgWidget = nullptr;
    MsgWidget *highColumn1MsgWidget = new MsgWidget("display.BVV.cont1Failure",
                                                    "Вентиляція увімкнена");
    MsgWidget *highColumn2MsgWidget = nullptr;

    RowMsgWidget *rowMsgWidget = new RowMsgWidget(lowColumn1MsgWidget,
                                                  lowColumn2MsgWidget,
                                                  highColumn1MsgWidget,
                                                  highColumn2MsgWidget);
    m_mainLayout->addWidget(rowMsgWidget, 6,0,1,1);
}
//------------------------------------------------------------------------------------
//!
void StatesDisplayWidget::setupRow8()
{
    MsgWidget *lowColumn1MsgWidget = new MsgWidget("display.BVV.condWorked",
                                                   "Кондицiонер РОБОТА");
    MsgWidget *lowColumn2MsgWidget = new MsgWidget("display.BVV.heater",
                                                   "Ел. калорифер увiмкнено");

    MsgWidget *highColumn1MsgWidget = new MsgWidget("display.BVV.condFailure",
                                                    "Кондицiонер ВIДМОВА");
    MsgWidget *highColumn2MsgWidget = nullptr;

    RowMsgWidget *rowMsgWidget = new RowMsgWidget(lowColumn1MsgWidget,
                                                  lowColumn2MsgWidget,
                                                  highColumn1MsgWidget,
                                                  highColumn2MsgWidget);
    m_mainLayout->addWidget(rowMsgWidget, 7,0,1,1);
}
//------------------------------------------------------------------------------------
//!

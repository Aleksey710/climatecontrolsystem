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

    /*
    { "name":"display.d30000.u3000",			"title":"Напруга 3000В",					"value": 0 },
    { "name":"display.d30000.VVO_1",			"title":"ВВО 1гр",							"value": 0 },
    { "name":"display.d30000.VVO_2",			"title":"ВВО 2гр",							"value": 0 },
    { "name":"display.d30000.NVO",				"title":"NVO",								"value": 0 },
    { "name":"display.d30000.generator",		"title":"Вн. мережа 380В/генератор",		"value": 0 },
    { "name":"display.d30000.automode",			"title":"Автоматичний режим",				"value": 0 },
    { "name":"display.d30000.crash",			"title":"Аварiя",							"value": 0 },
    { "name":"display.d30000.elEquipmentOn",	"title":"ЕО включене",						"value": 0 },
    { "name":"display.d30000.condFailure",		"title":"Кондицiонер ВIДМОВА",				"value": 0 },
    { "name":"display.d30000.cont2Failure",		"title":"Вiдмова контура охолодження 2",	"value": 0 },
    { "name":"display.d30000.cont1Failure",		"title":"Вiдмова контура охолодження 1",	"value": 0 },
    { "name":"display.d30000.condWorked",		"title":"Кондицiонер РОБОТА",				"value": 0 },
    { "name":"display.d30000.cooling",			"title":"Охолодження",						"value": 0 },
    { "name":"display.d30000.heater",			"title":"Калорифер",						"value": 0 },
    { "name":"display.d30000.umax_zrk",			"title":"Umax ЗРК",							"value": 0 },
    { "name":"display.d30000.r_insulation",		"title":"R iзоляцiї < 1 kOm",				"value": 0 }
    */

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
    MsgWidget *lowColumn1MsgWidget = new MsgWidget("display.d30000.crash",
                                                   "Аварiя");

    MsgWidget *lowColumn2MsgWidget = new MsgWidget("display.d30000.r_insulation",
                                                   "R iзоляцiї < 1 kOm");

    MsgWidget *highColumn1MsgWidget = new MsgWidget("display.d30000.NVO",
                                                    "НВО увiмкнено");

    MsgWidget *highColumn2MsgWidget = new MsgWidget("display.d30000.cooling",
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
    MsgWidget *lowColumn1MsgWidget = new MsgWidget("display.d30000.u3000",
                                                   "Вiдсутня напруга 3000В");

    MsgWidget *lowColumn2MsgWidget = nullptr;

    MsgWidget *highColumn1MsgWidget = new MsgWidget("display.d30000.VVO_1",
                                                    "ВВО гр.1 увiмкнено");
    MsgWidget *highColumn2MsgWidget = new MsgWidget("display.d30000.VVO_2",
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
    MsgWidget *lowColumn1MsgWidget = nullptr;
    MsgWidget *lowColumn2MsgWidget = nullptr;
    MsgWidget *highColumn1MsgWidget = nullptr;
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
    MsgWidget *lowColumn1MsgWidget = new MsgWidget("display.d30000.cont1Failure",
                                                   "Вiдмова контура охолодження 1");
    MsgWidget *lowColumn2MsgWidget = new MsgWidget("display.d30000.cont2Failure",
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
    MsgWidget *lowColumn1MsgWidget = nullptr;
    MsgWidget *lowColumn2MsgWidget = nullptr;
    MsgWidget *highColumn1MsgWidget = nullptr;
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
    MsgWidget *lowColumn1MsgWidget = nullptr;
    MsgWidget *lowColumn2MsgWidget = nullptr;
    MsgWidget *highColumn1MsgWidget = nullptr;
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
    MsgWidget *lowColumn1MsgWidget = new MsgWidget("display.d30000.condWorked",
                                                   "Кондицiонер РОБОТА");
    MsgWidget *lowColumn2MsgWidget = new MsgWidget("display.d30000.heater",
                                                   "Ел. калорифер увiмкнено");

    MsgWidget *highColumn1MsgWidget = new MsgWidget("display.d30000.condFailure",
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

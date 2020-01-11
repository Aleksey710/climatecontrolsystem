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
        "padding: 1px;"
        "margin: 1px;"
//        "border: 1px solid #000000;"
//        "border-radius : 5px;"
//        "color: blue;"
//        "background-color: yellow;"
        "}"
    );

    m_mainLayout->setMargin(1);
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
    QList<MsgWidget*> highPriorityMsgWidgetList;
    QList<MsgWidget*> lowPriorityMsgWidgetList;

    RowMsgWidget *rowMsgWidget = new RowMsgWidget(highPriorityMsgWidgetList,
                                                  lowPriorityMsgWidgetList);
    m_mainLayout->addWidget(rowMsgWidget, 0,0,1,1);
}
//------------------------------------------------------------------------------------
//!
void StatesDisplayWidget::setupRow2()
{
    QList<MsgWidget*> highPriorityMsgWidgetList;
    QList<MsgWidget*> lowPriorityMsgWidgetList;
    //----------------------------------------------

    //MsgWidget *msgWidget = new MsgWidget();

    //----------------------------------------------
    RowMsgWidget *rowMsgWidget = new RowMsgWidget(highPriorityMsgWidgetList,
                                                  lowPriorityMsgWidgetList);
    m_mainLayout->addWidget(rowMsgWidget, 1,0,1,1);
}
//------------------------------------------------------------------------------------
//!
void StatesDisplayWidget::setupRow3()
{
    QList<MsgWidget*> highPriorityMsgWidgetList;
    QList<MsgWidget*> lowPriorityMsgWidgetList;

    RowMsgWidget *rowMsgWidget = new RowMsgWidget(highPriorityMsgWidgetList,
                                                  lowPriorityMsgWidgetList);
    m_mainLayout->addWidget(rowMsgWidget, 2,0,1,1);
}
//------------------------------------------------------------------------------------
//!
void StatesDisplayWidget::setupRow4()
{
    QList<MsgWidget*> highPriorityMsgWidgetList;
    QList<MsgWidget*> lowPriorityMsgWidgetList;

    RowMsgWidget *rowMsgWidget = new RowMsgWidget(highPriorityMsgWidgetList,
                                                  lowPriorityMsgWidgetList);
    m_mainLayout->addWidget(rowMsgWidget, 3,0,1,1);
}
//------------------------------------------------------------------------------------
//!
void StatesDisplayWidget::setupRow5()
{
    QList<MsgWidget*> highPriorityMsgWidgetList;
    QList<MsgWidget*> lowPriorityMsgWidgetList;

    RowMsgWidget *rowMsgWidget = new RowMsgWidget(highPriorityMsgWidgetList,
                                                  lowPriorityMsgWidgetList);
    m_mainLayout->addWidget(rowMsgWidget, 4,0,1,1);
}
//------------------------------------------------------------------------------------
//!
void StatesDisplayWidget::setupRow6()
{
    QList<MsgWidget*> highPriorityMsgWidgetList;
    QList<MsgWidget*> lowPriorityMsgWidgetList;

    RowMsgWidget *rowMsgWidget = new RowMsgWidget(highPriorityMsgWidgetList,
                                                  lowPriorityMsgWidgetList);
    m_mainLayout->addWidget(rowMsgWidget, 5,0,1,1);
}
//------------------------------------------------------------------------------------
//!
void StatesDisplayWidget::setupRow7()
{
    QList<MsgWidget*> highPriorityMsgWidgetList;
    QList<MsgWidget*> lowPriorityMsgWidgetList;

    RowMsgWidget *rowMsgWidget = new RowMsgWidget(highPriorityMsgWidgetList,
                                                  lowPriorityMsgWidgetList);
    m_mainLayout->addWidget(rowMsgWidget, 6,0,1,1);
}
//------------------------------------------------------------------------------------
//!
void StatesDisplayWidget::setupRow8()
{
    QList<MsgWidget*> highPriorityMsgWidgetList;
    QList<MsgWidget*> lowPriorityMsgWidgetList;

    RowMsgWidget *rowMsgWidget = new RowMsgWidget(highPriorityMsgWidgetList,
                                                  lowPriorityMsgWidgetList);
    m_mainLayout->addWidget(rowMsgWidget, 7,0,1,1);
}
//------------------------------------------------------------------------------------
//!

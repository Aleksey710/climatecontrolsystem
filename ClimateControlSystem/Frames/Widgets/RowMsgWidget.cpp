#include "RowMsgWidget.h"

//------------------------------------------------------------------------------------
//!
RowMsgWidget::RowMsgWidget(MsgWidget *lowColumn1MsgWidget,
                           MsgWidget *lowColumn2MsgWidget,
                           MsgWidget *highColumn1MsgWidget,
                           MsgWidget *highColumn2MsgWidget,
                           QWidget *parent)
             :QWidget(parent),
              m_mainLayout ( new QGridLayout() ),
              m_lowPriorityWidget ( new QWidget() ),
              m_highPriorityWidget ( new QWidget() ),
              m_lowIndex ( 0 ),
              m_highIndex ( 0 )
{
    setObjectName("RowMsgWidget");

    setStyleSheet(
        "QWidget{ "
        "padding: 0px;"
        "margin: 0px;"
        //"border: 1px solid #6c6c6c;"
        //"border-radius : 25px;"
        "}"
    );

    m_mainLayout->setMargin(1);
    m_mainLayout->setVerticalSpacing(1);
    m_mainLayout->setHorizontalSpacing(1);

    //---------------------------------------------------------
    m_lowPriorityWidget->setStyleSheet(
        "QLabel{ "
        "padding: 1px;"
        "margin: 1px;"
        //"border: 1px solid #000000;"
        "border: 2px solid #ff0000;"
        "border-radius : 5px;"
        "color: red;"
        //"background-color: yellow;"
        "}"
    );

    m_highPriorityWidget->setStyleSheet(
        "QLabel{ "
        "padding: 1px;"
        "margin: 1px;"
        //"border: 1px solid #000000;"
        //"border: 2px solid #ff0000;"
        "border-radius : 5px;"
        "color: white;"
        "background-color: red;"
        "}"
    );
    //---------------------------------------------------------
    QHBoxLayout *lowPriorityWidgetLayout = new QHBoxLayout();

    if(lowColumn1MsgWidget)
    {
        lowPriorityWidgetLayout->addWidget(lowColumn1MsgWidget);
        connect(lowColumn1MsgWidget, &MsgWidget::displayed,
                this, &RowMsgWidget::lowIndexHandler);
    }

    if(lowColumn2MsgWidget)
    {
        lowPriorityWidgetLayout->addWidget(lowColumn2MsgWidget);
        connect(lowColumn2MsgWidget, &MsgWidget::displayed,
                this, &RowMsgWidget::lowIndexHandler);
    }

    m_lowPriorityWidget->setLayout(lowPriorityWidgetLayout);

    m_lowPriorityWidget->setVisible(false);

    m_mainLayout->addWidget(m_lowPriorityWidget);
    //---------------------------------------------------------
    QHBoxLayout *highPriorityWidgetLayout = new QHBoxLayout();

    if(highColumn1MsgWidget)
    {
        highPriorityWidgetLayout->addWidget(highColumn1MsgWidget);
        connect(highColumn1MsgWidget, &MsgWidget::displayed,
                this, &RowMsgWidget::highIndexHandler);
    }

    if(highColumn2MsgWidget)
    {
        highPriorityWidgetLayout->addWidget(highColumn2MsgWidget);
        connect(highColumn2MsgWidget, &MsgWidget::displayed,
                this, &RowMsgWidget::highIndexHandler);
    }

    m_highPriorityWidget->setLayout(highPriorityWidgetLayout);

    m_highPriorityWidget->setVisible(false);

    m_mainLayout->addWidget(m_highPriorityWidget);

    //---------------------------------------------------------
    //! Задать виджету слой
    setLayout(m_mainLayout);

    SEND_TO_LOG( QString("%1 - создан").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
RowMsgWidget::~RowMsgWidget()
{
    SEND_TO_LOG( QString("%1 - удален").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
void RowMsgWidget::lowIndexHandler(bool state)
{
    if(state) m_lowIndex++; else { if(m_lowIndex > 0) m_lowIndex--; }
    priorityHandler();
}
//------------------------------------------------------------------------------------
//!
void RowMsgWidget::highIndexHandler(bool state)
{
    if(state) m_highIndex++; else { if(m_highIndex > 0) m_highIndex--; }
    priorityHandler();
}
//------------------------------------------------------------------------------------
//!
void RowMsgWidget::priorityHandler()
{
    qDebug() << "RowMsgWidget::priorityHandler()" << m_lowIndex << m_highIndex;
    m_lowPriorityWidget->setVisible(true);


    if(m_highIndex > 0)
    {
        m_lowPriorityWidget->setVisible(false);
        m_highPriorityWidget->setVisible(true);
    } else
    {
        m_highPriorityWidget->setVisible(false);

        if(m_lowIndex > 0)
            m_lowPriorityWidget->setVisible(true);
        else
            m_lowPriorityWidget->setVisible(false);
    }

}

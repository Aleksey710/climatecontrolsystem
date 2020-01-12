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
    QHBoxLayout *lowPriorityWidgetLayout = new QHBoxLayout();

    if(lowColumn1MsgWidget)
    {
        lowPriorityWidgetLayout->addWidget(lowColumn1MsgWidget);
    }

    if(lowColumn2MsgWidget)
    {
        lowPriorityWidgetLayout->addWidget(lowColumn2MsgWidget);
    }

    m_lowPriorityWidget->setLayout(lowPriorityWidgetLayout);
    m_mainLayout->addWidget(m_lowPriorityWidget);
    //---------------------------------------------------------
    QHBoxLayout *highPriorityWidgetLayout = new QHBoxLayout();

    if(highColumn1MsgWidget)
    {
        highPriorityWidgetLayout->addWidget(highColumn1MsgWidget);
        connect(highColumn1MsgWidget, &MsgWidget::displayed,
                this, &RowMsgWidget::priorityHandler);
    }

    if(highColumn2MsgWidget)
    {
        highPriorityWidgetLayout->addWidget(highColumn2MsgWidget);
        connect(highColumn2MsgWidget, &MsgWidget::displayed,
                this, &RowMsgWidget::priorityHandler);
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
void RowMsgWidget::priorityHandler(bool state)
{
    if(state) m_highIndex++; else m_highIndex--;

    if(m_highIndex)
    {
        m_lowPriorityWidget->setVisible(false);
        m_highPriorityWidget->setVisible(true);
    } else
    {
        m_lowPriorityWidget->setVisible(true);
        m_highPriorityWidget->setVisible(false);
    }
}

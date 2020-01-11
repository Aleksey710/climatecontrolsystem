#include "RowMsgWidget.h"

//------------------------------------------------------------------------------------
//!
RowMsgWidget::RowMsgWidget(const QList<MsgWidget *> &highPriorityMsgWidgetList,
                           const QList<MsgWidget *> &lowPriorityMsgWidgetList,
                           QWidget *parent)
             :QWidget(parent),
              m_mainLayout ( new QGridLayout() ),
              m_curentPriorityWidget ( PriorityWidget::LowPriorityWidget ),
              m_highPriorityWidget ( new QWidget() ),
              m_lowPriorityWidget ( new QWidget() )
{
    setObjectName("RowMsgWidget");

        setStyleSheet(
            "QWidget{ "
            "padding: 1px;"
            "margin: 1px;"
            "border: 1px solid #6c6c6c;"
            //"border-radius : 25px;"
            "}"
        );

    m_mainLayout->setMargin(1);
    m_mainLayout->setVerticalSpacing(1);
    m_mainLayout->setHorizontalSpacing(1);

    //---------------------------------------------------------
    QFont titleFont = font();
    titleFont.setPointSize(titleFont.pointSize() + 3);

    QLabel *titleLabel = new QLabel("СТРОКА");
    titleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    titleLabel->setFont(titleFont);
    m_mainLayout->addWidget(titleLabel);

    //---------------------------------------------------------
    QFont dataFont = font();
    dataFont.setPointSize(dataFont.pointSize() + 10);

    //---------------------------------------------------------
//    m_dataLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//    m_dataLabel->setFont(dataFont);
//    m_mainLayout->addWidget(m_dataLabel);

    //---------------------------------------------------------
    //m_mainLayout->addWidget(m_digitalStripIndicator);
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
void RowMsgWidget::setVisibleMsgWidget(const PriorityWidget type)
{

    switch (type)
    {
        case PriorityWidget::HighPriorityWidget:

            break;
        case PriorityWidget::LowPriorityWidget:

            break;
        default:
            break;
    }
}

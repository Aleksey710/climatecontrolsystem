#include "StatesDisplayWidget.h"

//------------------------------------------------------------------------------------
//!
StatesDisplayWidget::StatesDisplayWidget(QWidget *parent)
                    :QWidget(parent),
                     m_mainLayout ( new QGridLayout() )
{
    setObjectName("GigitalIndicatorWidget");

    setStyleSheet(
        "QWidget{ "
        "padding: 1px;"
        "margin: 1px;"
        "border: 1px solid #6c6c6c;"
        "border-radius : 25px;"
        "color: blue;"
        "background-color: yellow;"
        "}"
    );

    //    m_mainLayout->setVerticalSpacing(1);
    //    m_mainLayout->setHorizontalSpacing(1);

    //---------------------------------------------------------
    QFont titleFont = font();
    titleFont.setPointSize(titleFont.pointSize() + 3);

//    QLabel *titleLabel = new QLabel(title);
//    titleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//    titleLabel->setFont(titleFont);
//    m_mainLayout->addWidget(titleLabel);

//    //---------------------------------------------------------
//    QFont dataFont = font();
//    dataFont.setPointSize(dataFont.pointSize() + 10);

//    m_dataLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//    m_dataLabel->setFont(dataFont);
//    m_mainLayout->addWidget(m_dataLabel);

//    //---------------------------------------------------------
//    m_mainLayout->addWidget(m_digitalStripIndicator);
    //---------------------------------------------------------
    //! Задать виджету слой
    //setLayout(m_mainLayout);

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

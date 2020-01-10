#include "GigitalIndicatorWidget.h"
//------------------------------------------------------------------------------------
//!
GigitalIndicatorWidget::GigitalIndicatorWidget(const QString &title,
                                               const QString &measureTitle,
                                               const int minimum,
                                               const int maximum,
                                               QWidget *parent)
                       :QWidget(parent),
                        m_mainLayout ( new QGridLayout() ),
                        m_dataLabel ( new QLabel(measureTitle) ),
                        m_measureTitle ( measureTitle ),
                        m_digitalStripIndicator ( new DigitalStripIndicator(minimum, maximum) )
{
    setObjectName("GigitalIndicatorWidget");

//    setStyleSheet(
//        "QWidget{ "
//        "padding: 1px;"
//        "margin: 1px;"
//        "border: 1px solid #6c6c6c;"
//        "border-radius : 25px;"
//        "}"
//    );

//    m_mainLayout->setVerticalSpacing(1);
//    m_mainLayout->setHorizontalSpacing(1);

    //---------------------------------------------------------
    QFont titleFont = font();
    titleFont.setPointSize(titleFont.pointSize() + 3);

    QLabel *titleLabel = new QLabel(title);
    titleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    titleLabel->setFont(titleFont);
    m_mainLayout->addWidget(titleLabel);

    //---------------------------------------------------------
    QFont dataFont = font();
    dataFont.setPointSize(dataFont.pointSize() + 10);

    m_dataLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_dataLabel->setFont(dataFont);
    m_mainLayout->addWidget(m_dataLabel);

    //---------------------------------------------------------
    m_mainLayout->addWidget(m_digitalStripIndicator);
    //---------------------------------------------------------
    //! Задать виджету слой
    setLayout(m_mainLayout);

    SEND_TO_LOG( QString("%1 - создан").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
GigitalIndicatorWidget::~GigitalIndicatorWidget()
{
    SEND_TO_LOG( QString("%1 - удален").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
void GigitalIndicatorWidget::setData(const double &value)
{
    m_digitalStripIndicator->setData(value);

    m_dataLabel->setText(QString("%1 %2").arg(value).arg(m_measureTitle));
}
/*
QTableWidget{
border: 0.5px solid gray;
border-radius : 25px;
selection-background-color : transparent black;
}

QTableView{
border : 0.5px solid gray;
border-radius : 25px;
}
QHeaderView::section:first {
 background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                   stop:0 #616161, stop: 0.5 #505050,
                                   stop: 0.6 #434343, stop:1 #656565);
 color: white;
 border: 1px solid #6c6c6c;
[b]     border-radius : 25px;[/b] //не работает
 padding-left: 4px;
 margin-left  : 25px;



QProgressBar {
border: 2px solid grey;
border-radius: 5px;
}

QProgressBar::chunk {
background-color: #05B8CC;
width: 20px;
}
This leaves the text-align, which we customize by positioning the text in the center of the progress bar.

QProgressBar {
border: 2px solid grey;
border-radius: 5px;
text-align: center;
}
 */

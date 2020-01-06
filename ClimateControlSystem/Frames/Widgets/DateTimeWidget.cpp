#include "DateTimeWidget.h"

//------------------------------------------------------------------------------------
//!
DateTimeWidget::DateTimeWidget(QWidget *parent)
               :QWidget(parent)
{
    setObjectName("AbstractDisplayWidget");

    QGridLayout *mainLayout = new QGridLayout();

    setStyleSheet(
        "QWidget{ "
        "padding: 1px;"
        "margin: 1px;"
        "border: 1px solid #6c6c6c;"

        "border-radius: 10px;"
        //"border-color: beige;"
        //"font: bold 14px;      "
        "}"
    );


    mainLayout->setVerticalSpacing(1);
    mainLayout->setHorizontalSpacing(1);

    //QWidget *mainWidget()

    //---------------------------------------------------------
    QFont dateFont = font();
    dateFont.setPointSize(dateFont.pointSize() + 5);

    QLabel *dateLabel = new QLabel();
    dateLabel->setFont(dateFont);
    dateLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    mainLayout->addWidget(dateLabel);

    //---------------------------------------------------------
    QFont timeFont = font();
    timeFont.setPointSize(timeFont.pointSize() + 10);

    QLabel *timeLabel = new QLabel();
    timeLabel->setFont(timeFont);
    timeLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    mainLayout->addWidget(timeLabel);

    //---------------------------------------------------------
    //! Задать виджету слой
    setLayout(mainLayout);
    //---------------------------------------------------------

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=](){

        QDateTime dateTime = QDateTime::currentDateTime();

        dateLabel->setText(dateTime.toString("dd.MM.yyyy"));
        timeLabel->setText(dateTime.toString("HH:mm"));
    });

    timer->start(1000);

    //---------------------------------------------------------
    SEND_TO_LOG( QString("%1 - создан").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
DateTimeWidget::~DateTimeWidget()
{

}

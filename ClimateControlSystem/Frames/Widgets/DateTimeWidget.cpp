#include "DateTimeWidget.h"

//------------------------------------------------------------------------------------
//!
DateTimeWidget::DateTimeWidget(QWidget *parent)
               :QWidget(parent)
{
    setObjectName("AbstractDisplayWidget");

    QGridLayout *mainLayout = new QGridLayout();

    setLayout(mainLayout);

    mainLayout->setMargin(1);
    mainLayout->setVerticalSpacing(1);
    mainLayout->setHorizontalSpacing(1);

    QString baseStyleSheet = styleSheet();

    QGridLayout *rootLayout = new QGridLayout();
    rootLayout->setMargin(1);
    rootLayout->setVerticalSpacing(1);
    rootLayout->setHorizontalSpacing(1);

    QWidget *rootWidget = new QWidget();
    rootWidget->setObjectName("rootWidget");
    rootWidget->setStyleSheet(
        "QWidget#rootWidget {"
        "padding: 1px;"
        "margin: 1px;"
        "border: 1px solid #000000;"
        "border-radius : 5px;"
//        "color: blue;"
//        "background-color: yellow;"
        "}"
    );

    rootWidget->setLayout(rootLayout);

    mainLayout->addWidget(rootWidget);
    //---------------------------------------------------------
    QFont dateFont = font();
    dateFont.setPointSize(dateFont.pointSize() + 5);

    QLabel *dateLabel = new QLabel();
    dateLabel->setFont(dateFont);
    dateLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    rootLayout->addWidget(dateLabel);

    //---------------------------------------------------------
    QFont timeFont = font();
    timeFont.setPointSize(timeFont.pointSize() + 10);

    QLabel *timeLabel = new QLabel();
    timeLabel->setFont(timeFont);
    timeLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    rootLayout->addWidget(timeLabel);

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

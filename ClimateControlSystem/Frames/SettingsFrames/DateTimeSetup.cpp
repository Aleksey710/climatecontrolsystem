#include "DateTimeSetup.h"
#include "ui_DateTimeSetup.h"

//------------------------------------------------------------------------------------
//!
DateTimeSetup::DateTimeSetup(QWidget *parent)
              :QWidget(parent),
               ui(new Ui::DateTimeSetup)
{
    ui->setupUi(this);

    setWindowTitle("Встановити час");

    connect(ui->pbSet, &QPushButton::released,
            this, &DateTimeSetup::setDateTime);

    connect(ui->pbExit, &QPushButton::released,
            this, &QWidget::close);

    ui->calendarWidget->setDateRange(QDate(2020, 1, 1),
                                     QDate(2120,12,31));

    ui->calendarWidget->setSelectedDate( QDateTime::currentDateTime().date() );

    ui->timeEdit->setTime( QDateTime::currentDateTime().time() );
}
//------------------------------------------------------------------------------------
//!
DateTimeSetup::~DateTimeSetup()
{
    delete ui;
}
//------------------------------------------------------------------------------------
//!
void DateTimeSetup::setDateTime()
{
    QDate date = ui->calendarWidget->selectedDate();
    QTime time = ui->timeEdit->time();

    QDateTime dateTime(date, time);

    qDebug() << "DateTimeSetup::setDateTime()" << dateTime;

/*
#ifdef __arm__
    //static const QString setSystemDateTime = "";
    //QProcess::startDetached( setSystemDateTime );

    //static const QString readFromRealTimeClock  = "sudo hwclock -r";
    static const QString writeToRealTimeClock   = "sudo hwclock -w";
    QProcess::startDetached( writeToRealTimeClock );
#endif // __arm__
*/
}

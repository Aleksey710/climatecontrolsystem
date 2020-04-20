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

#ifdef __arm__
    //-----------------------------------------------------------------
//    //! Установка времени из командной строки
//    //! sudo date +%T -s "11:14:00"
//    static const QString setTimeCommandString =
//        QString("sudo date +%T -s \"\"")
//            .arg(QDateTime::currentDateTime().toString("HH:mm:ss"));
//    QProcess::startDetached( setTimeCommandString );
    //-----------------------------------------------------------------
    //static const QString readFromRealTimeClock  = "sudo hwclock -r";
    //static const QString writeToRealTimeClock   = "sudo hwclock -w";
    //-----------------------------------------------------------------
    // Записать время в RTC
    // sudo hwclock --set --date="2011-04-17 16:45:05"
    static const QString writeToRealTimeClock   = QString("sudo hwclock --set --date=\"%1\"")
            .arg(dateTime.toString("yyyy-MM-dd HH:mm:ss"));

    SEND_TO_LOG( QString("DateTimeSetup::setDateTime - [%1]").arg(writeToRealTimeClock) );

    QProcess::startDetached( writeToRealTimeClock );

    //-----------------------------------------------------------------
    //! Задать системное время из часов реального времени
    //! sudo hwclock -s
    const QString setDateCommandString = QString("sudo hwclock -s");

    SEND_TO_LOG( QString("DateTimeSetup::setDateTime - [%1]").arg(setDateCommandString) );

    QProcess::startDetached( setDateCommandString );
    //-----------------------------------------------------------------
#endif // __arm__

}

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

    qDebug() << "DateTimeSetup::setDateTime()\n"
                "sudo date -s \"" << dateTime.toString("yyyy-MM-dd HH:mm:ss") << "\"";

#ifdef __arm__
    //-----------------------------------------------------------------
    //! Установка даты из командной строки
    //! sudo date -s "2020-03-30 01:20:00"
    const QString setDateCommandString =
        QString("sudo date -s \"%1\"")
            .arg(dateTime.toString("yyyy-MM-dd HH:mm:ss"));

    QProcess::startDetached( setDateCommandString );
    //-----------------------------------------------------------------
//    //! Установка времени из командной строки
//    //! sudo date +%T -s "11:14:00"
//    static const QString setTimeCommandString =
//        QString("sudo date +%T -s \"\"")
//            .arg(QDateTime::currentDateTime().toString("HH:mm:ss"));
//    QProcess::startDetached( setTimeCommandString );
    //-----------------------------------------------------------------
    //static const QString setSystemDateTime = "";
    //QProcess::startDetached( setSystemDateTime );

    //static const QString readFromRealTimeClock  = "sudo hwclock -r";
    //static const QString writeToRealTimeClock   = "sudo hwclock -w";
    // sudo hwclock --set --date="2011-04-17 16:45:05"
    static const QString writeToRealTimeClock   = QString("sudo hwclock --set --date=\"%1\"")
            .arg(dateTime.toString("yyyy-MM-dd HH:mm:ss"));

    QProcess::startDetached( writeToRealTimeClock );
    //-----------------------------------------------------------------
#endif // __arm__

}

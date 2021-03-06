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
    ui->calendarWidget->showSelectedDate();

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
    //static const QString readFromRealTimeClock  = "sudo hwclock -r";
    //static const QString writeToRealTimeClock   = "sudo hwclock -w";
    //-----------------------------------------------------------------
    //!
    //!
    //! sudo hwclock --set --date="2011-04-17 16:45:05 ; sudo hwclock -s
    QString writeToRealTimeClock   =
        QString("sudo hwclock --set --date=\"%1\" ; sudo hwclock -s")
            .arg(dateTime.toString("yyyy-MM-dd HH:mm:ss"));

    SEND_TO_LOG( QString("\n"
                         "DateTimeSetup::setDateTime - \n"
                         "%1\n"
                         "").arg(writeToRealTimeClock) );

    //QProcess::startDetached( writeToRealTimeClock );

    std::system(writeToRealTimeClock.toLatin1());

    //-----------------------------------------------------------------
#endif // __arm__

}

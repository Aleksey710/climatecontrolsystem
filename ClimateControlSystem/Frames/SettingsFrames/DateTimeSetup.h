#ifndef DATETIMESETUP_H
#define DATETIMESETUP_H
//------------------------------------------------------------------------------------
#include <QWidget>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QDebug>
#include <QProcess>


//------------------------------------------------------------------------------------
namespace Ui {
class DateTimeSetup;
}
//------------------------------------------------------------------------------------
//!
class DateTimeSetup : public QWidget
{
        Q_OBJECT

    public:
        explicit DateTimeSetup(QWidget *parent = nullptr);
        virtual ~DateTimeSetup();

    private slots:
        void setDateTime();

    private:
        Ui::DateTimeSetup *ui;
};
//------------------------------------------------------------------------------------
#endif // DATETIMESETUP_H

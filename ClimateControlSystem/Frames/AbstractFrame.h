#ifndef ABSTRACTFRAME_H
#define ABSTRACTFRAME_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
//#include <>
//#include <>
//#include <>
//#include <>


//#include ""
//#include ""
//#include ""
#include "Log.h"
#include "ScriptUnit.h"
#include "GigitalIndicatorWidget.h"
#include "FrameName.h"
//------------------------------------------------------------------------------------
//!
class AbstractFrame : public QWidget
{
        Q_OBJECT
    public:
        explicit AbstractFrame(QWidget *parent = nullptr);
        virtual ~AbstractFrame();

        virtual FrameName frameName() = 0;

    signals:
        void showed();

    protected:
        void setupDisplay(const QString &name, QLabel *label);
        void setupDisplay(const QString &name, QLineEdit *lineEdit);
        void setupDisplay(const QString &name, GigitalIndicatorWidget *displayWidget);

        void setupDigDisplay(const QString &name, QLineEdit *lineEdit);

        void setupDateDisplay(const QString &yearName,
                              const QString &monthName,
                              const QString &dayName,
                              QLabel *label);
    signals:


    private:

};
//------------------------------------------------------------------------------------
#endif // ABSTRACTFRAME_H

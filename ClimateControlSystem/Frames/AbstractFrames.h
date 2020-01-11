#ifndef ABSTRACTFRAMES_H
#define ABSTRACTFRAMES_H
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
//------------------------------------------------------------------------------------
//!
class AbstractFrames : public QWidget
{
        Q_OBJECT
    public:
        explicit AbstractFrames(QWidget *parent = nullptr);
        virtual ~AbstractFrames();

    protected:
        void setupDisplay(const QString &name, QLabel *label);

        void setupDisplay(const QString &name, QLineEdit *lineEdit);
        void setupDigDisplay(const QString &name, QLineEdit *lineEdit);

        void setupDisplay(const QString &name, GigitalIndicatorWidget *displayWidget);

    signals:


    private:

};
//------------------------------------------------------------------------------------
#endif // ABSTRACTFRAMES_H

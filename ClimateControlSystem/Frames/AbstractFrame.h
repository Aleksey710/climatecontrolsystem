#ifndef ABSTRACTFRAME_H
#define ABSTRACTFRAME_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
//
#include <iomanip>
//#include <>
//#include <>
//#include <>
//#include <>


//#include ""
//#include ""
//
#include "Log.h"
#include "ScriptUnit.h"
#include "GigitalIndicatorWidget.h"
#include "FrameName.h"
#include "DataAverager.h"
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
        void setupStringDisplay(const QString &name, QLabel *label);

        void setupDisplay(const QString &name,
                          const bool onlyT,
                          QLabel *label);

        void setupDisplay(const QString &dataRegName,
                          const QString &deviceRegName,
                          QLineEdit *lineEdit,
                          const bool onlyT,
                          const QString &averageSizeScriptObjectName = QString());

        GigitalIndicatorWidget* createGigitalIndicatorWidget(const QString &name,
                                                             const QString &title,
                                                             const QString &measureTitle,
                                                             const QString &minimumRegData,
                                                             const QString &maximumRegData,
                                                             const bool onlyT,
                                                             const QString &averageSizeScriptObjectName = QString());

        GigitalIndicatorWidget* createGigitalIndicatorWidget(const QString &name,
                                                             const QString &title,
                                                             const QString &measureTitle,
                                                             const int minimum,
                                                             const int maximum,
                                                             const bool onlyT,
                                                             const QString &averageSizeScriptObjectName = QString());


        void setupDigDisplay(const QString &dataRegName,
                             const QString &deviceRegName,
                             QLineEdit *lineEdit);

        void setupDateDisplay(const QString &yearName,
                              const QString &monthName,
                              const QString &dayName,
                              QLabel *label);
    signals:


    private:

};
//------------------------------------------------------------------------------------
#endif // ABSTRACTFRAME_H

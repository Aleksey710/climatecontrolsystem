#ifndef DIGITALINDICATORWIDGET_H
#define DIGITALINDICATORWIDGET_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QFont>
#include <QLabel>
#include <QProgressBar>
#include <QCoreApplication>
//#include <>
//#include <>
//#include <>



#include "Log.h"
#include "DigitalStripIndicator.h"
//#include ".h"
//#include ".h"
//#include ".h"
//#include ".h"
//#include ".h"
//#include ".h"
//#include "AbstractDisplayWidget.h"
//------------------------------------------------------------------------------------
//!
class GigitalIndicatorWidget : public QWidget
{
        Q_OBJECT
    public:
        explicit GigitalIndicatorWidget(const QString &title,
                                        const QString &measureTitle,
                                        const int minimum,
                                        const int maximum,
                                        QWidget *parent = nullptr);
        virtual ~GigitalIndicatorWidget();

        double data();


    signals:


    public slots:
        void setData(const double &value);

    protected:
        QGridLayout *m_mainLayout;
        QLabel *m_dataLabel;
        QString m_measureTitle;

        DigitalStripIndicator *m_digitalStripIndicator;


    private:

};
//------------------------------------------------------------------------------------
#endif // DIGITALINDICATORWIDGET_H

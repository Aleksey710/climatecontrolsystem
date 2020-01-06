#ifndef ABSTRACTDISPLAYWIDGET_H
#define ABSTRACTDISPLAYWIDGET_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QFont>
#include <QLabel>
#include <QProgressBar>
//#include <>
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
class AbstractDisplayWidget : public QWidget
{
        Q_OBJECT
    public:
        explicit AbstractDisplayWidget(const QString &title,
                                       const QString &measureTitle,
                                       const int minimum,
                                       const int maximum,
                                       QWidget *parent = nullptr);
        virtual ~AbstractDisplayWidget();

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
#endif // ABSTRACTDISPLAYWIDGET_H

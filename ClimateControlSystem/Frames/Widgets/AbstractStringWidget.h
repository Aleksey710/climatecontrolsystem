#ifndef ABSTRACTSTRINGWIDGET_H
#define ABSTRACTSTRINGWIDGET_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QFont>
#include <QLabel>
//#include <>
//#include <>
//#include <>
//#include <>


#include "Log.h"
//#include ".h"
//#include ".h"
//#include ".h"
//------------------------------------------------------------------------------------
//!
class AbstractStringWidget : public QWidget
{
        Q_OBJECT
    public:
        explicit AbstractStringWidget(QWidget *parent = nullptr);
        virtual ~AbstractStringWidget();


    signals:

    public slots:
        //void setData(const double &value);


    protected:
        enum PriorityWidget {
            HighPriorityWidget,
            LowPriorityWidget
        };

    protected:
        void setVisibleMsgWidget(const PriorityWidget type);


    protected:
        QGridLayout *m_mainLayout;

        PriorityWidget m_curentPriorityWidget;

        QWidget *m_highPriorityWidget;
        QWidget *m_lowPriorityWidget;

};
//------------------------------------------------------------------------------------
#endif // ABSTRACTSTRINGWIDGET_H

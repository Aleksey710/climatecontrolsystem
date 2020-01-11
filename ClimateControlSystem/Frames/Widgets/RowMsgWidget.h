#ifndef ROWMSGWIDGET_H
#define ROWMSGWIDGET_H
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
#include "MsgWidget.h"
//#include ".h"
//#include ".h"
//#include ".h"
//------------------------------------------------------------------------------------
//!
class RowMsgWidget : public QWidget
{
        Q_OBJECT
    public:
        explicit RowMsgWidget(const QList<MsgWidget*> &highPriorityMsgWidgetList,
                              const QList<MsgWidget*> &lowPriorityMsgWidgetList,
                              QWidget *parent = nullptr);
        virtual ~RowMsgWidget();


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
#endif // ROWMSGWIDGET_H

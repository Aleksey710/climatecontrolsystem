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
        explicit RowMsgWidget(MsgWidget *lowColumn1MsgWidget = nullptr,
                              MsgWidget *lowColumn2MsgWidget = nullptr,
                              MsgWidget *highColumn1MsgWidget = nullptr,
                              MsgWidget *highColumn2MsgWidget = nullptr,
                              QWidget *parent = nullptr);
        virtual ~RowMsgWidget();


    signals:

    protected slots:
        void priorityHandler(bool state);

    protected:


    protected:
        QGridLayout *m_mainLayout;

        QWidget *m_lowPriorityWidget;
        QWidget *m_highPriorityWidget;

        int m_highIndex;
};
//------------------------------------------------------------------------------------
#endif // ROWMSGWIDGET_H

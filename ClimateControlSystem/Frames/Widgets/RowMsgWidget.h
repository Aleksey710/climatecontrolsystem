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
#include "AbstractMsgWidget.h"
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
        explicit RowMsgWidget(AbstractMsgWidget *lowColumn1MsgWidget = nullptr,
                              AbstractMsgWidget *lowColumn2MsgWidget = nullptr,
                              AbstractMsgWidget *highColumn1MsgWidget = nullptr,
                              AbstractMsgWidget *highColumn2MsgWidget = nullptr,
                              QWidget *parent = nullptr);
        virtual ~RowMsgWidget();


    signals:

    protected slots:
        void lowIndexHandler(bool state);
        void highIndexHandler(bool state);
        void priorityHandler();

    protected:


    protected:
        QGridLayout *m_mainLayout;

        QWidget *m_lowPriorityWidget;
        QWidget *m_highPriorityWidget;

        uint m_lowIndex;
        uint m_highIndex;
};
//------------------------------------------------------------------------------------
#endif // ROWMSGWIDGET_H

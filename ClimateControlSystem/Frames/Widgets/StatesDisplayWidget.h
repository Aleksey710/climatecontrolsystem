#ifndef STATESDISPLAYWIDGET_H
#define STATESDISPLAYWIDGET_H
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
#include "RowMsgWidget.h"
#include "MultiMsgWidget.h"
//#include ".h"
//#include ".h"
//------------------------------------------------------------------------------------
//!
class StatesDisplayWidget : public QWidget
{
        Q_OBJECT
    public:
        explicit StatesDisplayWidget(QWidget *parent = nullptr);
        virtual ~StatesDisplayWidget();


    signals:

    private:
        void setupRow1();
        void setupRow2();
        void setupRow3();
        void setupRow4();
        void setupRow5();
        void setupRow6();
        void setupRow7();
        void setupRow8();

    private:
        QGridLayout *m_mainLayout;

        RowMsgWidget *m_rowMsgWidget1;
        RowMsgWidget *m_rowMsgWidget2;
        RowMsgWidget *m_rowMsgWidget3;
        RowMsgWidget *m_rowMsgWidget4;
        RowMsgWidget *m_rowMsgWidget5;
        RowMsgWidget *m_rowMsgWidget6;
        RowMsgWidget *m_rowMsgWidget7;
        RowMsgWidget *m_rowMsgWidget8;
};
//------------------------------------------------------------------------------------
#endif // STATESDISPLAYWIDGET_H

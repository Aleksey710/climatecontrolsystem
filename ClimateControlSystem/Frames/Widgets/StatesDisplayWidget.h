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
        QGridLayout *m_mainLayout;
};
//------------------------------------------------------------------------------------
#endif // STATESDISPLAYWIDGET_H

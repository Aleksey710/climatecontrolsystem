#ifndef BUTTONSWIDGET_H
#define BUTTONSWIDGET_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QWidget>
#include <QString>
#include <QVBoxLayout>
#include <QPushButton>
//#include <>
//#include <>
//#include <>
//#include <>


//#include ""
//#include ""
//#include ""
#include "Log.h"
#include "FrameName.h"
//------------------------------------------------------------------------------------
//!
class ButtonsWidget : public QWidget
{
        Q_OBJECT
    public:
        explicit ButtonsWidget(QWidget *parent = nullptr);
        virtual ~ButtonsWidget();


    signals:
        void mainFrameClicked();
        void nextFrameClicked();
        void previousFrameClicked();

        void pgUpClicked();
        void pgDownClicked();

        void plusClicked();
        void minusClicked();


    private:




};
//------------------------------------------------------------------------------------
#endif // BUTTONSWIDGET_H

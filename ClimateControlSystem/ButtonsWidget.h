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


    public slots:
        void setFrameName(const FrameName &frameName);

    signals:
        void mainFrameClicked();
        void nextFrameClicked();
        void previousFrameClicked();

        void pgUpClicked();
        void pgDownClicked();

        void plusClicked();
        void minusClicked();


    private:

        QPushButton *m_mainFrameButton;
        QPushButton *m_previousFrameButton;
        QPushButton *m_nextFrameButton;
        QPushButton *m_pgUpFrameButton;
        QPushButton *m_pgDownFrameButton;
        QPushButton *m_minusFrameButton;
        QPushButton *m_plusFrameButton;


};
//------------------------------------------------------------------------------------
#endif // BUTTONSWIDGET_H

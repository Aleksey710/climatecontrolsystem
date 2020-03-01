#ifndef BUTTONSWIDGET_H
#define BUTTONSWIDGET_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QWidget>
#include <QString>
#include <QVBoxLayout>
#include <QPushButton>
#include <QProcess>
//#include <>
//#include <>
//#include <>


//#include ""
//#include ""
//#include ""
#include "Log.h"
#include "FrameName.h"
#include "ButtonsControlThread.h"
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
        void setButtonState(bool mainFrameButtonState,
                            bool nextFrameButtonState,
                            bool pgUpFrameButtonState,
                            bool pgDownFrameButtonState,
                            bool minusFrameButtonState,
                            bool plusFrameButtonState,
                            bool emptyButton1State,
                            bool emptyButton2State,
                            bool emptyButton3State,
                            bool emptyButton4State);
    private:

        QPushButton *m_emptyButton1;
        QPushButton *m_emptyButton2;
        QPushButton *m_emptyButton3;
        QPushButton *m_emptyButton4;

        QPushButton *m_mainFrameButton;
        QPushButton *m_previousFrameButton;
        QPushButton *m_nextFrameButton;

        QPushButton *m_pgUpFrameButton;
        QPushButton *m_pgDownFrameButton;

        QPushButton *m_minusFrameButton;
        QPushButton *m_plusFrameButton;


        ButtonsControlThread *m_buttonsControlThread;
};
//------------------------------------------------------------------------------------
#endif // BUTTONSWIDGET_H

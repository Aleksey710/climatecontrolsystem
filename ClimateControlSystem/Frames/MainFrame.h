#ifndef MAINFRAME_H
#define MAINFRAME_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QWidget>
#include <QString>
//#include <>
//#include <>
//#include <>


//#include ""
//#include ""
//#include ""
#include "Log.h"
#include "AbstractFrames.h"
#include "AbstractDisplayWidget.h"
#include "DateTimeWidget.h"
//------------------------------------------------------------------------------------
namespace Ui {
class MainFrame;
}
//------------------------------------------------------------------------------------
//!
class MainFrame : public AbstractFrames
{
        Q_OBJECT

    public:
        explicit MainFrame(QWidget *parent = nullptr);
        virtual ~MainFrame();

    private:
        Ui::MainFrame *ui;
};
//------------------------------------------------------------------------------------
#endif // MAINFRAME_H

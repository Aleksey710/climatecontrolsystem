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
#include "GigitalIndicatorWidget.h"
#include "DateTimeWidget.h"
#include "StatesDisplayWidget.h"
//------------------------------------------------------------------------------------
//!
class MainFrame : public AbstractFrames
{
        Q_OBJECT

    public:
        explicit MainFrame(QWidget *parent = nullptr);
        virtual ~MainFrame();

    private:

};
//------------------------------------------------------------------------------------
#endif // MAINFRAME_H

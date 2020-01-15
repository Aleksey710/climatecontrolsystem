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
#include "AbstractFrame.h"
#include "GigitalIndicatorWidget.h"
#include "DateTimeWidget.h"
#include "StatesDisplayWidget.h"
//------------------------------------------------------------------------------------
//!
class MainFrame : public AbstractFrame
{
        Q_OBJECT

    public:
        explicit MainFrame(QWidget *parent = nullptr);
        virtual ~MainFrame();

        inline virtual FrameName frameName() { return FrameName::Main; }

    private:

};
//------------------------------------------------------------------------------------
#endif // MAINFRAME_H

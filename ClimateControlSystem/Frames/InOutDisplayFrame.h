#ifndef INOUTDISPLAYFRAME_H
#define INOUTDISPLAYFRAME_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QWidget>
#include <QString>
//#include <>
//#include <>
//#include <>


//#include ""
//#include ""

#include "Log.h"
#include "AbstractFrame.h"
//------------------------------------------------------------------------------------
namespace Ui {
class InOutDisplayFrame;
}
//------------------------------------------------------------------------------------
//!
class InOutDisplayFrame : public AbstractFrame
{
        Q_OBJECT

    public:
        explicit InOutDisplayFrame(QWidget *parent = nullptr);
        virtual ~InOutDisplayFrame();

        inline virtual FrameName frameName() { return FrameName::InOutDisplay; }


    private:
        Ui::InOutDisplayFrame *ui;
};
//------------------------------------------------------------------------------------
#endif // INOUTDISPLAYFRAME_H

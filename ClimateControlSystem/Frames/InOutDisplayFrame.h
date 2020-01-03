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
#include "AbstractFrames.h"
//------------------------------------------------------------------------------------
namespace Ui {
class InOutDisplayFrame;
}
//------------------------------------------------------------------------------------
//!
class InOutDisplayFrame : public AbstractFrames
{
        Q_OBJECT

    public:
        explicit InOutDisplayFrame(QWidget *parent = nullptr);
        virtual ~InOutDisplayFrame();


    private:
        Ui::InOutDisplayFrame *ui;
};
//------------------------------------------------------------------------------------
#endif // INOUTDISPLAYFRAME_H

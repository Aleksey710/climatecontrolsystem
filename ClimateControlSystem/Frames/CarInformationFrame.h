#ifndef CARINFORMATIONFRAME_H
#define CARINFORMATIONFRAME_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QWidget>
#include <QString>
#include <QTimer>
#include <QDateTime>
#include <QStyle>
//#include <>
//#include <>


//#include ""
//#include ""
//#include ""
#include "Log.h"
#include "AbstractFrame.h"
//------------------------------------------------------------------------------------
namespace Ui {
class CarInformationFrame;
}
//------------------------------------------------------------------------------------
//!
class CarInformationFrame : public AbstractFrame
{
        Q_OBJECT

    public:
        explicit CarInformationFrame(QWidget *parent = nullptr);
        virtual ~CarInformationFrame();

        inline virtual FrameName frameName() { return FrameName::CarInformation; }

    private:
        Ui::CarInformationFrame *ui;
};
//------------------------------------------------------------------------------------
#endif // CARINFORMATIONFRAME_H

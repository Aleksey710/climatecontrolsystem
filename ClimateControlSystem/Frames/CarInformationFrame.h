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
#include "AbstractFrames.h"
//------------------------------------------------------------------------------------
namespace Ui {
class CarInformationFrame;
}
//------------------------------------------------------------------------------------
//!
class CarInformationFrame : public AbstractFrames
{
        Q_OBJECT

    public:
        explicit CarInformationFrame(QWidget *parent = nullptr);
        virtual ~CarInformationFrame();

    private:
        Ui::CarInformationFrame *ui;
};
//------------------------------------------------------------------------------------
#endif // CARINFORMATIONFRAME_H

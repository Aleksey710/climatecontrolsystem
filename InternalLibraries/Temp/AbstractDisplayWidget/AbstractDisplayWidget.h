#ifndef ABSTRACTDISPLAYWIDGET_H
#define ABSTRACTDISPLAYWIDGET_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QWidget>
//#include <>
//#include <>


#include "Log.h"
//#include ""
//#include ""
//------------------------------------------------------------------------------------
QT_BEGIN_NAMESPACE
namespace Ui { class AbstractDisplayWidget; }
QT_END_NAMESPACE
//------------------------------------------------------------------------------------
//!
class AbstractDisplayWidget : public QWidget
{
        Q_OBJECT

    public:
        AbstractDisplayWidget(QWidget *parent = nullptr);
        virtual ~AbstractDisplayWidget();

    private:
        Ui::AbstractDisplayWidget *ui;
};
//------------------------------------------------------------------------------------
#endif // ABSTRACTDISPLAYWIDGET_H

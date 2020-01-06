#ifndef DATETIMEWIDGET_H
#define DATETIMEWIDGET_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QWidget>
#include <QFont>
#include <QLabel>
#include <QGridLayout>
#include <QTimer>
//#include <>
//#include <>
//#include <>
//#include <>



#include "Log.h"
//#include ".h"
//#include ".h"
//#include ".h"
//#include ".h"
//#include ".h"
//------------------------------------------------------------------------------------
//!
class DateTimeWidget : public QWidget
{
        Q_OBJECT
    public:
        explicit DateTimeWidget(QWidget *parent = nullptr);
        virtual ~DateTimeWidget();


    signals:

};
//------------------------------------------------------------------------------------
#endif // DATETIMEWIDGET_H

#ifndef ABSTRACTFRAMES_H
#define ABSTRACTFRAMES_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QWidget>
//#include <>
//#include <>
//#include <>


//#include ""
//#include ""
//#include ""
#include "Log.h"
//------------------------------------------------------------------------------------
//!
class AbstractFrames : public QWidget
{
        Q_OBJECT
    public:
        explicit AbstractFrames(QWidget *parent = nullptr);
        virtual ~AbstractFrames();


    signals:


    private:

};
//------------------------------------------------------------------------------------
#endif // ABSTRACTFRAMES_H

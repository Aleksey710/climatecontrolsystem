#ifndef CURENTTIMESCRIPTOBJECT_H
#define CURENTTIMESCRIPTOBJECT_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QTimer>
#include <QDateTime>
//#include <>
//#include <>
//#include <>

#include "Log.h"
#include "ScriptObject.h"
//------------------------------------------------------------------------------------
//!
class CurentTimeScriptObject : public ScriptObject
{
    Q_OBJECT
public:
    CurentTimeScriptObject(ScriptObject *parent)
        :ScriptObject("curent",
                      static_cast<qint64>(QDateTime::currentSecsSinceEpoch()),
                      parent)
    {
            QTimer *timer = new QTimer(this);
            connect(timer, &QTimer::timeout, this, [=](){
                setData(static_cast<qint64>(QDateTime::currentSecsSinceEpoch()));

                //qDebug() << fullName() << data();
            });
            timer->start(1000);
    }
};
//------------------------------------------------------------------------------------
#endif // CURENTTIMESCRIPTOBJECT_H

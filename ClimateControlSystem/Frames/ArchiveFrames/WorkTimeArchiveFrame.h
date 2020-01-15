#ifndef WORKTIMEARCHIVEFRAME_H
#define WORKTIMEARCHIVEFRAME_H
//------------------------------------------------------------------------------------
#include <QObject>
//#include <>
//#include <>
//#include <>
//#include <>


#include "AbstractArchiveFrame.h"
//------------------------------------------------------------------------------------
//!
class WorkTimeArchiveFrame : public AbstractArchiveFrame
{
        Q_OBJECT
    public:
        explicit WorkTimeArchiveFrame(QWidget *parent = nullptr)
            :AbstractArchiveFrame(parent)
        {
            setObjectName(QString("WorkTimeArchiveFrame"));
            setup();
            SEND_TO_LOG(QString("%1 - создан").arg(objectName()));
        }

        virtual ~WorkTimeArchiveFrame()
            {  }

    private:
        virtual QString headLabel() override
            { return QString("Журнал часу роботи"); }

        virtual QString queryString() override
        {
            return QString(
                "SELECT "
                "strftime('%Y-%m-%d %H:%M:%f',`datetime`/1000,'unixepoch', 'localtime') AS dt, "
                "`msg` "
                "FROM `%1` "
                ";").arg("work_time_events");
        }

};
//------------------------------------------------------------------------------------
#endif // WORKTIMEARCHIVEFORM_H

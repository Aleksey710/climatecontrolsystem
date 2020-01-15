#ifndef WORKTIMEARCHIVEFORM_H
#define WORKTIMEARCHIVEFORM_H
//------------------------------------------------------------------------------------
#include <QObject>
//#include <>
//#include <>
//#include <>
//#include <>


#include "AbstractArchiveForm.h"
//------------------------------------------------------------------------------------
//!
class WorkTimeArchiveForm : public AbstractArchiveForm
{
        Q_OBJECT
    public:
        explicit WorkTimeArchiveForm(QWidget *parent = nullptr)
            :AbstractArchiveForm(parent)
        {
            setObjectName(QString("WorkTimeArchiveForm"));
            setup();
            SEND_TO_LOG(QString("%1 - создан").arg(objectName()));
        }

        virtual ~WorkTimeArchiveForm()
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

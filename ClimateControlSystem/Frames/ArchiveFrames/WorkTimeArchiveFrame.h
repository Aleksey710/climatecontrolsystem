#ifndef WORKTIMEARCHIVEFRAME_H
#define WORKTIMEARCHIVEFRAME_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QHeaderView>
#include <QTableWidget>
#include <QScrollBar>
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
        explicit WorkTimeArchiveFrame(QWidget *parent = nullptr);

        virtual ~WorkTimeArchiveFrame();

    public slots:
        void pgUp() override;
        void pgDown() override;
        void updateData();

        void updateCountLabelData() override;

    private:
        virtual QString headLabel() override
            { return QString("Журнал часу роботи"); }

        virtual QString queryString() override
        {
            return QString(
                "SELECT "
                "strftime('%Y-%m-%d %H:%M:%S',`datetime`/1000,'unixepoch', 'localtime') AS dt, "
                "`msg` "
                "FROM `%1` "
                "ORDER BY `dt` " // Прямая сортировка!!! обратная после обработки!!!
                "LIMIT 108 "
                ";").arg("work_time_events");
        }

        virtual void setup() override;

        struct RowOnOff;

        void resetRowList(const QList<RowOnOff> &rowList);

    private:
        QGridLayout *m_mainLayout;

        //---------------------------------------------
        struct RowOnOff {
            RowOnOff(const QString &column1String = "",
                     const QString &column2String = "",
                     const QString &column3String = "",
                     const QString &column4String = "")
                : column0 ( new QTableWidgetItem(column1String) ),
                  column1 ( new QTableWidgetItem(column2String) ),
                  column2 ( new QTableWidgetItem(column3String) ),
                  column3 ( new QTableWidgetItem(column4String) )
            { }

            QTableWidgetItem *column0;
            QTableWidgetItem *column1;
            QTableWidgetItem *column2;
            QTableWidgetItem *column3;
        };

};
//------------------------------------------------------------------------------------
#endif // WORKTIMEARCHIVEFORM_H

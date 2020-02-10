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
        void pgUp();
        void pgDown();
        void updateData();

    private:
        virtual QString headLabel() override
            { return QString("Журнал часу роботи"); }

        virtual QString queryString() override
        {
            return QString(
                "SELECT "
                "strftime('%Y-%m-%d %H:%M:%f',`datetime`/1000,'unixepoch', 'localtime') AS dtS, "
                "`msg` "
                "FROM `%1` "
                ";").arg("work_time_events");
        }

        virtual void setup() override;

        void rowListAppend(QList< std::tuple<QTableWidgetItem*,
                                             QTableWidgetItem*,
                                             QTableWidgetItem*,
                                             QTableWidgetItem*> > *rowList,
                           QTableWidgetItem *column0,
                           QTableWidgetItem *column1,
                           QTableWidgetItem *column2,
                           QTableWidgetItem *column3);

        void resetRowList(QList< std::tuple<QTableWidgetItem*,
                                            QTableWidgetItem*,
                                            QTableWidgetItem*,
                                            QTableWidgetItem*> > *rowList);

    private:
        QGridLayout *m_mainLayout;
        QTableWidget *m_tableWidget;

};
//------------------------------------------------------------------------------------
#endif // WORKTIMEARCHIVEFORM_H

#ifndef CONFIGEDITFRAME_H
#define CONFIGEDITFRAME_H
//------------------------------------------------------------------------------------
#include <QApplication>
#include <QWidget>
#include <QTableView>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QHeaderView>
#include <QSqlQuery>
//#include <>
//#include <>


#include "Log.h"
#include "NumericKeypadWidget.h"
//------------------------------------------------------------------------------------
//!
class ConfigEditFrame : public QWidget
{
        Q_OBJECT

    public:
        explicit ConfigEditFrame(const QString &groupName = "temp",
                                QWidget *parent = nullptr);
        virtual ~ConfigEditFrame();

    private slots:
        void onClicked(const QModelIndex &index);

    private:
        QSqlQueryModel *m_model;
        QTableView *m_tableView;
};
//------------------------------------------------------------------------------------
#endif // CONFIGEDITFRAME_H

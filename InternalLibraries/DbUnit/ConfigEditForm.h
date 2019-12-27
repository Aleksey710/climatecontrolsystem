#ifndef CONFIGEDITFORM_H
#define CONFIGEDITFORM_H
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


#include "NumericKeypadWidget.h"
//------------------------------------------------------------------------------------
//!
class ConfigEditForm : public QWidget
{
        Q_OBJECT

    public:
        explicit ConfigEditForm(const QString &groupName = "temp",
                                QWidget *parent = nullptr);
        virtual ~ConfigEditForm();

    private slots:
        void onClicked(const QModelIndex &index);

    private:
        QSqlQueryModel *m_model;
        QTableView *m_tableView;
};
//------------------------------------------------------------------------------------
#endif // CONFIGEDITFORM_H

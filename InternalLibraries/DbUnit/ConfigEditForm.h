#ifndef CONFIGEDITFORM_H
#define CONFIGEDITFORM_H
//------------------------------------------------------------------------------------
#include <QWidget>
#include <QTableView>
#include <QTableWidget>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlError>
#include <QHeaderView>
#include <QApplication>
//#include <>
//#include <>
//#include <>


#include "NumericKeypadWidget.h"
//------------------------------------------------------------------------------------
//!
class ConfigEditForm : public QWidget
{
        Q_OBJECT

    public:
        explicit ConfigEditForm(QWidget *parent = nullptr);
        virtual ~ConfigEditForm();

    private slots:
        void onClicked(const QModelIndex &index);

    private:
        QSqlTableModel *m_model;
        QTableView *m_tableView;
};
//------------------------------------------------------------------------------------
#endif // CONFIGEDITFORM_H

#ifndef CONFIGEDITFRAME_H
#define CONFIGEDITFRAME_H
//------------------------------------------------------------------------------------
#include <QWidget>
#include <QTableView>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QHeaderView>
#include <QSqlQuery>
#include <QLabel>
//#include <>
//#include <>
//#include <>

//#include ".h"
//#include ".h"
//#include ".h"
//#include ".h"
//#include ".h"
//#include ".h"
#include "Log.h"
#include "NumericKeypadWidget.h"
#include "ItemEditSettingsWidget.h"
//------------------------------------------------------------------------------------
//!
class ConfigEditFrame : public QWidget
{
        Q_OBJECT

    public:
        explicit ConfigEditFrame(const QString &groupName = "temp",
                                 const QString &groupTitle = "Error",
                                 QWidget *parent = nullptr);
        virtual ~ConfigEditFrame();

    private slots:
        void updateModelData();
        void onClicked(const QModelIndex &index);

    private:
        QString m_groupName;
        QString m_groupTitle;

        QSqlQueryModel *m_model;
        QTableView *m_tableView;
};
//------------------------------------------------------------------------------------
#endif // CONFIGEDITFRAME_H

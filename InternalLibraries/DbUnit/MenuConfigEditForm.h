#ifndef MENUCONFIGEDITFORM_H
#define MENUCONFIGEDITFORM_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QWidget>
#include <QTableView>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QHeaderView>
#include <QSqlQuery>
#include <QPushButton>
#include <QStandardItem>
#include <QSpacerItem>
//#include <>
//#include <>
//#include <>


#include "MenuItemData.h"
#include "ConfigEditFrame.h"
//#include ".h"
//#include ".h"
//#include ".h"
//------------------------------------------------------------------------------------
//!
class MenuConfigEditForm : public QWidget
{
        Q_OBJECT
    public:
        explicit MenuConfigEditForm(const QList<MenuItemData> &menuItemDataList,
                                    QWidget *parent = nullptr);
        virtual ~MenuConfigEditForm();

    signals:

    private:
        QWidget *m_menuWidget;

};
//------------------------------------------------------------------------------------
#endif // MENUCONFIGEDITFORM_H

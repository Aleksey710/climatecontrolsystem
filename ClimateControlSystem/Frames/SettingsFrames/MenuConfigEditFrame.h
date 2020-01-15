#ifndef MENUCONFIGEDITFRAME_H
#define MENUCONFIGEDITFRAME_H
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
class MenuConfigEditFrame : public QWidget
{
        Q_OBJECT
    public:
        explicit MenuConfigEditFrame(const QList<MenuItemData> &menuItemDataList,
                                     QWidget *parent = nullptr);
        virtual ~MenuConfigEditFrame();

    signals:

    private:
        QWidget *m_menuWidget;

};
//------------------------------------------------------------------------------------
#endif // MENUCONFIGEDITFRAME_H

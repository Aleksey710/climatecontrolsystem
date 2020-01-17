#ifndef ITEMEDITSETTINGSWIDGET_H
#define ITEMEDITSETTINGSWIDGET_H
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


#include "AbstractFrame.h"
#include "MenuItemData.h"
#include "ConfigEditFrame.h"
//#include ".h"
//#include ".h"
//------------------------------------------------------------------------------------
namespace Ui {
class ItemEditSettingsWidget;
}
//------------------------------------------------------------------------------------
//!
class ItemEditSettingsWidget : public QWidget
{
        Q_OBJECT

    public:
        explicit ItemEditSettingsWidget(const QVariant &value = 0,
                                        QWidget *parent = nullptr);
        ~ItemEditSettingsWidget();

        QVariant value();
        //void setValue(const QVariant &value);

    signals:
        void editingFinished();
        //void entered(const QVariant &value);

    private:
        Ui::ItemEditSettingsWidget *ui;
};
//------------------------------------------------------------------------------------
#endif // ITEMEDITSETTINGSWIDGET_H

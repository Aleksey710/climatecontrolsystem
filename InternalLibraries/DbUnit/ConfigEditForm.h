#ifndef CONFIGEDITFORM_H
#define CONFIGEDITFORM_H
//------------------------------------------------------------------------------------
#include <QWidget>
#include <QTableView>
#include <QSqlTableModel>

//------------------------------------------------------------------------------------
namespace Ui {
class ConfigEditForm;
}
//------------------------------------------------------------------------------------
//!
class ConfigEditForm : public QWidget
{
        Q_OBJECT

    public:
        explicit ConfigEditForm(QWidget *parent = nullptr);
        ~ConfigEditForm();

    private:
        Ui::ConfigEditForm *ui;

        QTableView *m_view;
};
//------------------------------------------------------------------------------------
#endif // CONFIGEDITFORM_H

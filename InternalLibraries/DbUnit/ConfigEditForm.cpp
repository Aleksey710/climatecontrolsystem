#include "ConfigEditForm.h"
#include "ui_ConfigEditForm.h"

//------------------------------------------------------------------------------------
//!
ConfigEditForm::ConfigEditForm(QWidget *parent)
               :QWidget(parent),
                ui(new Ui::ConfigEditForm)
{
    ui->setupUi(this);

    QString m_dbFileAddress ( "./conf/db.sqlite" );

    QSqlDatabase db(QSqlDatabase::database(m_dbFileAddress));


    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable("data_model");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //model.setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("name"));
    model->setHeaderData(1, Qt::Horizontal, tr("title"));
    model->setHeaderData(2, Qt::Horizontal, tr("value"));

    QTableView *view = new QTableView;
    view->setModel(model);
    view->hideColumn(0); // don't show the ID
    view->show();

    layout()->addWidget(view);
}
//------------------------------------------------------------------------------------
//!
ConfigEditForm::~ConfigEditForm()
{
    delete ui;
}
//------------------------------------------------------------------------------------
//!

#include "ConfigEditForm.h"

//------------------------------------------------------------------------------------
//!
ConfigEditForm::ConfigEditForm(QWidget *parent)
               :QWidget(parent)
{
    QString m_dbFileAddress ( qApp->applicationDirPath()+"/conf/db.sqlite" );

    QSqlDatabase db(QSqlDatabase::database(m_dbFileAddress));

    QGridLayout *mainLayout = new QGridLayout;

    m_model = new QSqlTableModel(this, db);
    m_model->setTable("data_model");
    //m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_model->setEditStrategy(QSqlTableModel::OnFieldChange);
    m_model->select();

    m_model->setHeaderData(1, Qt::Horizontal, tr("id"));
    m_model->setHeaderData(2, Qt::Horizontal, tr("groupe_id"));
    m_model->setHeaderData(3, Qt::Horizontal, tr("name"));
    m_model->setHeaderData(4, Qt::Horizontal, tr("title"));
    m_model->setHeaderData(5, Qt::Horizontal, tr("value"));

    m_tableView = new QTableView();
    connect(m_tableView, &QAbstractItemView::clicked, this, &ConfigEditForm::onClicked);

    m_tableView->setModel(m_model);
    m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    m_tableView->resizeColumnsToContents();

    //m_tableView->hideColumn(0); // don't show the ID

    mainLayout->addWidget(m_tableView);

    setLayout(mainLayout);

    setWindowTitle(tr("ConfigEditForm"));

    //setAttribute(Qt::WA_DeleteOnClose);
}
//------------------------------------------------------------------------------------
//!
ConfigEditForm::~ConfigEditForm()
{
}
//------------------------------------------------------------------------------------
//!
void ConfigEditForm::onClicked(const QModelIndex &index)
{
    double value = m_model->data(index, Qt::EditRole).toDouble();

    NumericKeypadWidget *numericKeypadWidget = new NumericKeypadWidget(value);

    connect(numericKeypadWidget, &NumericKeypadWidget::editingFinished,
            [=](){
        m_model->setData(index, numericKeypadWidget->value());
        numericKeypadWidget->close();
    });

    numericKeypadWidget->show();
}
//------------------------------------------------------------------------------------
//!

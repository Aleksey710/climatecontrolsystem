#include "ConfigEditForm.h"

//------------------------------------------------------------------------------------
//!
ConfigEditForm::ConfigEditForm(const QString &groupName,
                               QWidget *parent)
               :QWidget(parent)
{
    QString m_dbFileAddress ( qApp->applicationDirPath()+"/conf/db.sqlite" );

    QSqlDatabase db(QSqlDatabase::database(m_dbFileAddress));

    QGridLayout *mainLayout = new QGridLayout;

    m_model = new QSqlQueryModel(this);
    //m_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //m_model->setEditStrategy(QSqlTableModel::OnFieldChange);

    //m_model->setTable("data_model");


    m_model->setQuery(QString("SELECT "
                              "`groups`.`title`,"
                              "`data_model`.`name`,"
                              "`data_model`.`title`,"
                              "`data_model`.`value` "
                              "FROM `data_model`, `groups` "
                              "WHERE "
                              "`data_model`.`group_id`= "
                              "(SELECT `id` FROM `groups` WHERE `name`='%1') AND "
                              "`data_model`.`group_id`=`groups`.`id`"
                              ";")
                      .arg(groupName),
                      db
                     );

    //m_model->setRelation(1, QSqlRelation("groups", "id", "title"));


    //m_model->select();

//    m_model->setHeaderData(0, Qt::Horizontal, tr("id"));
//    m_model->setHeaderData(1, Qt::Horizontal, tr("groupe_id"));
//    m_model->setHeaderData(2, Qt::Horizontal, tr("name"));
//    m_model->setHeaderData(3, Qt::Horizontal, tr("title"));
//    m_model->setHeaderData(4, Qt::Horizontal, tr("value"));

    m_tableView = new QTableView();
    connect(m_tableView, &QAbstractItemView::clicked, this, &ConfigEditForm::onClicked);

    m_tableView->setModel(m_model);
    m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    m_tableView->resizeColumnsToContents();

    //m_tableView->hideColumn(0); // don't show the ID

    mainLayout->addWidget(m_tableView);

    QPushButton *exitButton = new QPushButton("Выхiд");
    setAttribute(Qt::WA_DeleteOnClose);
    connect(exitButton, &QPushButton::released, this, &QWidget::close);
    mainLayout->addWidget(exitButton);

    setLayout(mainLayout);

    setWindowTitle(tr("ConfigEditForm [%1]").arg(groupName));
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
    //if(index.column() == 4)
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
}
//------------------------------------------------------------------------------------
//!

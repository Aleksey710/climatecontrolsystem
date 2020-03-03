#include "ConfigEditFrame.h"

#include "DbUnit.h"
//------------------------------------------------------------------------------------
//!
ConfigEditFrame::ConfigEditFrame(const QString &groupName,
                                 const QString &groupTitle,
                                 QWidget *parent)
                :QWidget(parent),
                 m_groupName ( groupName ),
                 m_groupTitle ( groupTitle )
{
    setObjectName(QString("ConfigEditForm[%1]").arg(groupName));

    //-----------------------------------------------------------------
    QGridLayout *mainLayout = new QGridLayout;

    //-----------------------------------------------------------------
    QLabel *titleLabel = new QLabel(groupTitle);

    mainLayout->addWidget(titleLabel);

    //-----------------------------------------------------------------
    m_tableView = new QTableView();
    connect(m_tableView, &QAbstractItemView::clicked, this, &ConfigEditFrame::onClicked);
    m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_tableView->horizontalHeader()->setStretchLastSection(true);

    m_tableView->verticalHeader()->hide();

    mainLayout->addWidget(m_tableView);

    //-----------------------------------------------------------------
    m_model = new QSqlQueryModel(this);

    updateModelData();

    m_model->setHeaderData(0, Qt::Horizontal, tr("Iм`я"));
    m_model->setHeaderData(1, Qt::Horizontal, tr("Назва"));
    m_model->setHeaderData(2, Qt::Horizontal, tr("Значення"));

    m_tableView->setModel(m_model);

    //-----------------------------------------------------------------
    QPushButton *exitButton = new QPushButton("Вихiд");
    setAttribute(Qt::WA_DeleteOnClose);
    connect(exitButton, &QPushButton::released, this, &QWidget::close);
    mainLayout->addWidget(exitButton);

    //-----------------------------------------------------------------
    setLayout(mainLayout);

    SEND_TO_LOG(QString("%1 - создан").arg(objectName()));
}
//------------------------------------------------------------------------------------
//!
ConfigEditFrame::~ConfigEditFrame()
{
    SEND_TO_LOG(QString("%1 - удален").arg(objectName()));
}
//------------------------------------------------------------------------------------
//!
void ConfigEditFrame::updateModelData()
{
    QSqlDatabase db(QSqlDatabase::database(DbUnit::dbName()));

    m_model->setQuery(QString("SELECT "
                              "`data`.`name`,"
                              "`data`.`title`,"
                              "`data`.`value` "
                              "FROM `data`, `groups` "
                              "WHERE "
                              "`data`.`group_id`= "
                              "(SELECT `id` FROM `groups` WHERE `name`='%1') AND "
                              "`data`.`group_id`=`groups`.`id`"
                              ";")
                      .arg(m_groupName),
                      db
                     );

    m_tableView->resizeColumnsToContents();
}
//------------------------------------------------------------------------------------
//!
void ConfigEditFrame::onClicked(const QModelIndex &index)
{
    if(index.column() == 2)
    {
        QString name    = m_model->data(m_model->index(index.row(),0), Qt::EditRole).toString();
        QString title   = m_model->data(m_model->index(index.row(),1), Qt::EditRole).toString();

        QVariant value  = m_model->data(index, Qt::EditRole);

        //NumericKeypadWidget *editSettingsWidget = new NumericKeypadWidget(value);
        ItemEditSettingsWidget *editSettingsWidget = new ItemEditSettingsWidget(value);

        connect(editSettingsWidget, &ItemEditSettingsWidget::editingFinished,
                [=](){

            QString queryStr = QString(
                "UPDATE `data` "
                "SET `value`='%1' "
                "WHERE `name`='%2';"
            ).arg(editSettingsWidget->value().toString()).arg(name);

            QSqlDatabase db(QSqlDatabase::database( DbUnit::dbName() ));
            QSqlQuery query(queryStr,db);
            if( !query.exec() )
            {
                QSqlError err = db.lastError();

                SEND_TO_LOG( QString("%1 - Error update [%2] [%3]")
                             .arg(objectName()).arg(name).arg(err.text()))
            } else
            {
                updateModelData();
            }

            //----------------------------------------------------
            m_model->setData(index, editSettingsWidget->value());
            editSettingsWidget->close();
        });

        editSettingsWidget->show();
    }
}
//------------------------------------------------------------------------------------
//!

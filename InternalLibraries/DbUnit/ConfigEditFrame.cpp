#include "ConfigEditFrame.h"

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
    QLabel *label = new QLabel(groupTitle);

    mainLayout->addWidget(label);

    //-----------------------------------------------------------------
    m_tableView = new QTableView();
    connect(m_tableView, &QAbstractItemView::clicked, this, &ConfigEditFrame::onClicked);
    m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_tableView->horizontalHeader()->setStretchLastSection(true);
    mainLayout->addWidget(m_tableView);

    //-----------------------------------------------------------------
    m_model = new QSqlQueryModel(this);

    updateModelData();

    m_model->setHeaderData(0, Qt::Horizontal, tr("Имя"));
    m_model->setHeaderData(1, Qt::Horizontal, tr("Название"));
    m_model->setHeaderData(2, Qt::Horizontal, tr("Значение"));

    m_tableView->setModel(m_model);

    //-----------------------------------------------------------------
    QPushButton *exitButton = new QPushButton("Выхiд");
    setAttribute(Qt::WA_DeleteOnClose);
    connect(exitButton, &QPushButton::released, this, &QWidget::close);
    mainLayout->addWidget(exitButton);

    //-----------------------------------------------------------------
    setLayout(mainLayout);

    setWindowTitle(tr("ConfigEditForm [%1]").arg(groupName));

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
    QString dbFileAddress ( qApp->applicationDirPath()+"/conf/db.sqlite" );
    QSqlDatabase db(QSqlDatabase::database(dbFileAddress));

    m_model->setQuery(QString("SELECT "
                              //"`groups`.`title`,"
                              "`data_model`.`name`,"
                              "`data_model`.`title`,"
                              "`data_model`.`value` "
                              "FROM `data_model`, `groups` "
                              "WHERE "
                              "`data_model`.`group_id`= "
                              "(SELECT `id` FROM `groups` WHERE `name`='%1') AND "
                              "`data_model`.`group_id`=`groups`.`id`"
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

        double value    = m_model->data(index, Qt::EditRole).toDouble();

        NumericKeypadWidget *numericKeypadWidget = new NumericKeypadWidget(value);

        connect(numericKeypadWidget, &NumericKeypadWidget::editingFinished,
                [=](){

            QString queryStr = QString(
                "UPDATE `data_model` "
                "SET `value` = %1 "
                "WHERE `data_model`.`name`='%2';"
            ).arg(numericKeypadWidget->value()).arg(name);

            QString dbFileAddress ( qApp->applicationDirPath()+"/conf/db.sqlite" );
            QSqlDatabase db(QSqlDatabase::database(dbFileAddress));
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
            m_model->setData(index, numericKeypadWidget->value());
            numericKeypadWidget->close();
        });

        numericKeypadWidget->show();
    }
}
//------------------------------------------------------------------------------------
//!

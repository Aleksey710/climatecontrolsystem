#include "AbstractArchiveForm.h"

//------------------------------------------------------------------------------------
//!
AbstractArchiveForm::AbstractArchiveForm(QWidget *parent)
                    : QWidget(parent)
{

}
//------------------------------------------------------------------------------------
//!
AbstractArchiveForm::~AbstractArchiveForm()
{
    SEND_TO_LOG(QString("%1 - удален").arg(objectName()));
}
//------------------------------------------------------------------------------------
//!
void AbstractArchiveForm::setup()
{
    //-----------------------------------------------------------------
    QGridLayout *mainLayout = new QGridLayout;

    //mainLayout->setMargin(1);
    //-----------------------------------------------------------------
    QLabel *titleLabel = new QLabel( headLabel() );

    mainLayout->addWidget(titleLabel);

    //-----------------------------------------------------------------
    QTableView *tableView = new QTableView();

    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableView->horizontalHeader()->setStretchLastSection(true);

    tableView->verticalHeader()->setDefaultSectionSize(9);

    /*
    tableView->setStyleSheet(
        "QTableView"
        "::item"
        //":focus "
        "{"
        "padding: 0px; "
        "margin: 0px;"
        "color: #ff0000;"
        "background-color : transparent;"
        "selection-color : black;"
        "}");
    */

    mainLayout->addWidget(tableView);

    //-----------------------------------------------------------------
    QSqlQueryModel *model = new QSqlQueryModel(this);

    model->setQuery( queryString(), QSqlDatabase::database(DbUnit::dbName()) );

    tableView->resizeColumnsToContents();

    //    model->setHeaderData(0, Qt::Horizontal, tr("Имя"));
    //    model->setHeaderData(1, Qt::Horizontal, tr("Название"));
    //    model->setHeaderData(2, Qt::Horizontal, tr("Значение"));

    tableView->setModel(model);
    tableView->horizontalHeader()->hide();
    tableView->verticalHeader()->hide();

    //-----------------------------------------------------------------
    setLayout(mainLayout);
}

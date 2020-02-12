#include "RemoveRecordsFromArchiveWidget.h"
#include "ui_RemoveRecordsFromArchiveWidget.h"

//------------------------------------------------------------------------------------
//!
RemoveRecordsFromArchiveWidget::RemoveRecordsFromArchiveWidget(QWidget *parent)
                               :QWidget(parent),
                                ui(new Ui::RemoveRecordsFromArchiveWidget)
{
    ui->setupUi(this);

    setWindowTitle("Видалення уciх записiв з усiх журналiв");

    connect(ui->pbRemoveAll, &QPushButton::released,
            this,&RemoveRecordsFromArchiveWidget::removeAll);

    setGeometry(0,0,400,200);
}
//------------------------------------------------------------------------------------
//!
RemoveRecordsFromArchiveWidget::~RemoveRecordsFromArchiveWidget()
{
    delete ui;
}
//------------------------------------------------------------------------------------
//!

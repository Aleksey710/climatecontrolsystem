#include "RemoveRecordsFromArchiveWidget.h"
#include "ui_RemoveRecordsFromArchiveWidget.h"

//------------------------------------------------------------------------------------
//!
RemoveRecordsFromArchiveWidget::RemoveRecordsFromArchiveWidget(QWidget *parent)
                               :QWidget(parent),
                                ui(new Ui::RemoveRecordsFromArchiveWidget)
{
    ui->setupUi(this);

    setWindowTitle("Видалення записiв");

    connect(ui->pbRemoveAll, &QPushButton::released, this,
            &RemoveRecordsFromArchiveWidget::removeAll);


}
//------------------------------------------------------------------------------------
//!
RemoveRecordsFromArchiveWidget::~RemoveRecordsFromArchiveWidget()
{
    delete ui;
}
//------------------------------------------------------------------------------------
//!

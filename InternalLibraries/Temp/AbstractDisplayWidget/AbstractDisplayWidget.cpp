#include "AbstractDisplayWidget.h"
#include "ui_AbstractDisplayWidget.h"
//------------------------------------------------------------------------------------
//!
AbstractDisplayWidget::AbstractDisplayWidget(QWidget *parent)
                      : QWidget(parent),
                        ui(new Ui::AbstractDisplayWidget)
{
    ui->setupUi(this);
}
//------------------------------------------------------------------------------------
//!
AbstractDisplayWidget::~AbstractDisplayWidget()
{
    delete ui;
}
//------------------------------------------------------------------------------------
//!

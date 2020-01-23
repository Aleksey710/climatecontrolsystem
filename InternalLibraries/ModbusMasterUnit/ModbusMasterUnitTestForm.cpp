#include "ModbusMasterUnitTestForm.h"
#include "ui_ModbusMasterUnitTestForm.h"

//------------------------------------------------------------------------------------
//!
ModbusMasterUnitTestForm::ModbusMasterUnitTestForm(QWidget *parent)
                         :QWidget(parent),
                          ui(new Ui::ModbusMasterUnitTestForm)
{
    ui->setupUi(this);
}
//------------------------------------------------------------------------------------
//!
ModbusMasterUnitTestForm::~ModbusMasterUnitTestForm()
{
    delete ui;
}
//------------------------------------------------------------------------------------
//!


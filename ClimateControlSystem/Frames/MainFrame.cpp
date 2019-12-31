#include "MainFrame.h"
#include "ui_MainFrame.h"

//------------------------------------------------------------------------------------
//!
MainFrame::MainFrame(QWidget *parent)
          :AbstractFrames(parent),
           ui(new Ui::MainFrame)
{
    ui->setupUi(this);

    setObjectName("MainFrame");






    SEND_TO_LOG( QString("%1 - создан").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
MainFrame::~MainFrame()
{
    delete ui;
}
//------------------------------------------------------------------------------------
//!



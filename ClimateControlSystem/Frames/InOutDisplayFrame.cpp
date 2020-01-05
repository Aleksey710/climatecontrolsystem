#include "InOutDisplayFrame.h"
#include "ui_InOutDisplayFrame.h"

//------------------------------------------------------------------------------------
//!
InOutDisplayFrame::InOutDisplayFrame(QWidget *parent)
                  :AbstractFrames(parent),
                   ui(new Ui::InOutDisplayFrame)
{
    ui->setupUi(this);

    setObjectName("InOutDisplayFrame");

//    m_mainLayout->setMargin(0);

//    setStyleSheet(//"font: 12px; "
//                  //"font-weight: bold; "
//                  "margin: 0px, 0px, 0px, 0px;"
//                  "padding: 0px, 0px, 0px, 0px; "
//                  //"border:  1px solid black; "
//                  );

    //--------------------------------------
    setupDisplay("display.temp.t_ust",  ui->le_t_ust);
    setupDisplay("display.temp.t_sal",  ui->le_t_sal);
    setupDisplay("display.temp.t_pr",   ui->le_t_pr);
    setupDisplay("display.temp.t_nv",   ui->le_t_nv);
    setupDisplay("display.temp.t_kotl", ui->le_t_kotl);

    //--------------------------------------
    // тестовое
    setupDisplay("modbus.rs0d10.r30000", ui->le_t_ust);
    setupDisplay("modbus.rs0d10.r30001", ui->le_t_sal);
    setupDisplay("modbus.rs0d10.r30002", ui->le_t_pr);
    setupDisplay("modbus.rs0d10.r30003", ui->le_t_nv);
    setupDisplay("modbus.rs0d10.r30004", ui->le_t_kotl);


    //--------------------------------------

    SEND_TO_LOG( QString("%1 - создан").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
InOutDisplayFrame::~InOutDisplayFrame()
{
    delete ui;
}



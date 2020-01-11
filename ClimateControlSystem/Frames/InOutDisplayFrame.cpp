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
    setupDigDisplay("display.d30000.u3000",         ui->le_u3000);
    setupDigDisplay("display.d30000.VVO_1",         ui->le_VVO_1);
    setupDigDisplay("display.d30000.VVO_2",         ui->le_VVO_2);
    setupDigDisplay("display.d30000.NVO",           ui->le_NVO);
    setupDigDisplay("display.d30000.generator",     ui->le_generator);
    setupDigDisplay("display.d30000.automode",      ui->le_automode);
    setupDigDisplay("display.d30000.crash",         ui->le_crash);
    setupDigDisplay("display.d30000.elEquipmentOn", ui->le_elEquipmentOn);
    setupDigDisplay("display.d30000.condFailure",   ui->le_condFailure);
    setupDigDisplay("display.d30000.cont2Failure",  ui->le_cont2Failure);
    setupDigDisplay("display.d30000.cont1Failure",  ui->le_cont1Failure);
    setupDigDisplay("display.d30000.condWorked",    ui->le_condWorked);
    setupDigDisplay("display.d30000.cooling",       ui->le_cooling);
    setupDigDisplay("display.d30000.heater",        ui->le_heater);
    setupDigDisplay("display.d30000.umax_zrk",      ui->le_umax_zrk);
    setupDigDisplay("display.d30000.r_insulation",  ui->le_r_insulation);


    //--------------------------------------

    SEND_TO_LOG( QString("%1 - создан").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
InOutDisplayFrame::~InOutDisplayFrame()
{
    delete ui;
}



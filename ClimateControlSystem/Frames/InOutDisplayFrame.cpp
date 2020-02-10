#include "InOutDisplayFrame.h"
#include "ui_InOutDisplayFrame.h"

//------------------------------------------------------------------------------------
//!
InOutDisplayFrame::InOutDisplayFrame(QWidget *parent)
                  :AbstractFrame(parent),
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

    setupDisplay("display.U_I.I_bat", ui->le_I_bat);
    setupDisplay("display.U_I.U_net", ui->le_U_net);
    setupDisplay("display.U_I.I_gen", ui->le_I_gen);

    //--------------------------------------
    setupDigDisplay("display.BVV.u3000",         ui->le_u3000);
    setupDigDisplay("display.BVV.VVO_1",         ui->le_VVO_1);
    setupDigDisplay("display.BVV.VVO_2",         ui->le_VVO_2);
    setupDigDisplay("display.BVV.NVO",           ui->le_NVO);
    setupDigDisplay("display.BVV.generator",     ui->le_generator);
    setupDigDisplay("display.BVV.automode",      ui->le_automode);
    setupDigDisplay("display.BVV.crash",         ui->le_crash);
    setupDigDisplay("display.BVV.elEquipmentOn", ui->le_elEquipmentOn);
    setupDigDisplay("display.BVV.condFailure",   ui->le_condFailure);
    setupDigDisplay("display.BVV.cont2Failure",  ui->le_cont2Failure);
    setupDigDisplay("display.BVV.cont1Failure",  ui->le_cont1Failure);
    setupDigDisplay("display.BVV.condWorked",    ui->le_condWorked);
    setupDigDisplay("display.BVV.cooling",       ui->le_cooling);
    setupDigDisplay("display.BVV.heater",        ui->le_heater);
    setupDigDisplay("display.BVV.umax_zrk",      ui->le_umax_zrk);
    setupDigDisplay("display.BVV.r_insulation",  ui->le_r_insulation);
    setupDigDisplay("display.BVV.ventilation",   ui->le_vent);

    //--------------------------------------
    setupDisplay("out.BVV.vvo1On",           ui->le_out_VVO1);
    setupDisplay("out.BVV.vvo2On",           ui->le_out_VVO2);
    setupDisplay("out.BVV.pompOn",           ui->le_out_pump_heater);
    setupDisplay("out.BVV.nvoOn",            ui->le_out_NVO);
    setupDisplay("out.BVV.fault",            ui->le_out_alarm);

    //--------------------------------------

    SEND_TO_LOG( QString("%1 - создан").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
InOutDisplayFrame::~InOutDisplayFrame()
{
    delete ui;
}



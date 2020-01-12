#include "CarInformationFrame.h"
#include "ui_CarInformationFrame.h"

//------------------------------------------------------------------------------------
//!
CarInformationFrame::CarInformationFrame(QWidget *parent)
                    :AbstractFrames(parent),
                     ui(new Ui::CarInformationFrame)
{
    ui->setupUi(this);

    setObjectName("CarInformationFrame");

    //-------------------------------------------------
    ui->lcdTime->setStyleSheet(QString("QLCDNumber{"
                                       "color:rgb(0, 0, 0);"
                                       //"background-color:rgb(255, 255, 255);"
                                       "}"));

    ui->lcdTime->setSegmentStyle(QLCDNumber::SegmentStyle::Flat);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=](){

        QDateTime curentDT = QDateTime::currentDateTime();

        ui->lbDate->setText( curentDT.toString("d MMM yyyy") );
        ui->lcdTime->display( curentDT.toString("HH:mm") );

    });
    timer->start(1000);

    //-------------------------------------------------
    ui->lbCompany->setMaximumWidth(300);

    //-------------------------------------------------
    setupDisplay("settings.wagon.num",  ui->lbVagon);
    setupDisplay("settings.wagon.sv",   ui->lbMicroProgVersion);
    setupDisplay("settings.wagon.sv",   ui->lbPoVersion);
    setupDisplay("settings.wagon.dd",   ui->lbStartUseDate);

    setupDisplay("settings.wagon.dd",   ui->lbStartUseDate);

    //-------------------------------------------------
    SEND_TO_LOG( QString("%1 - создан").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
CarInformationFrame::~CarInformationFrame()
{
    delete ui;
}
//------------------------------------------------------------------------------------
//!



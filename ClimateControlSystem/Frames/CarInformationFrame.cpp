#include "CarInformationFrame.h"
#include "ui_CarInformationFrame.h"

//------------------------------------------------------------------------------------
//!
CarInformationFrame::CarInformationFrame(QWidget *parent)
                    :AbstractFrame(parent),
                     ui(new Ui::CarInformationFrame)
{
    ui->setupUi(this);

    setObjectName("CarInformationFrame");

    //-------------------------------------------------
    //QPixmap image(":/images/logo_ukr.png");

    //ui->lbCompany->setScaledContents(false);
    //ui->lbCompany->setPixmap(image);

    ui->lbCompany->setPixmap( QPixmap::fromImage( QImage(":/images/logo_ukr.png") ) );
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

    setupDisplay("modbus.BVV.r40028",
                 false,
                 ui->lbBvvVersion);

    setupDateDisplay("modbus.BVV.r40029",       // year
                     "modbus.BVV.r40030",       // month
                     "modbus.BVV.r40031",       // day
                     ui->lbBvvDateVersion);

    setupDisplay("modbus.A9.r40028",
                 false,
                 ui->lbButVersion);

    setupDateDisplay("modbus.A9.r40029",        // year
                     "modbus.A9.r40030",        // month
                     "modbus.A9.r40031",        // day
                     ui->lbButDateVersion);

    setupStringDisplay("settings.wagon.sv",   ui->lbSoftVersion);

    setupStringDisplay("settings.wagon.num",  ui->lbVagon);

    setupDisplay("settings.wagon.dd",
                 false,
                 ui->lbStartUseDate);

    setupDisplay("display.wagon.res",
                 false,
                 ui->lbWorkTime);

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



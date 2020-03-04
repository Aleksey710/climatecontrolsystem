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

    setupDisplay("display.d30028.version",  ui->lbBvvVersion);

    setupDateDisplay("display.d30028.year",
                     "display.d30028.month",
                     "display.d30028.day",
                     ui->lbBvvDateVersion);

    setupDisplay("display.d30028.version",  ui->lbButVersion);

    setupDateDisplay("display.d30028.year",
                     "display.d30028.month",
                     "display.d30028.day",
                     ui->lbButDateVersion);

    setupStringDisplay("settings.wagon.sv",   ui->lbSoftVersion);

    setupStringDisplay("settings.wagon.num",  ui->lbVagon);

    setupDisplay("settings.wagon.dd",   ui->lbStartUseDate);

    setupDisplay("display.wagon.res",  ui->lbWorkTime);

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



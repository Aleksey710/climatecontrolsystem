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

    setupDisplay("display.BVV.version",
                 false,
                 ui->lbBvvVersion);

    setupDateDisplay("display.BVV.year",      // year
                     "display.BVV.month",     // month
                     "display.BVV.day",       // day
                     ui->lbBvvDateVersion);

    setupDisplay("display.A9.version",
                 false,
                 ui->lbButVersion);

    setupDateDisplay("display.A9.year",       // year
                     "display.A9.month",      // month
                     "display.A9.day",        // day
                     ui->lbButDateVersion);

    setupStringDisplay("settings.wagon.sv",   ui->lbSoftVersion);

    setupStringDisplay("settings.wagon.dd",   ui->lbSoftDate);

    setupStringDisplay("settings.wagon.num",  ui->lbVagon);

    setupStringDisplay("settings.wagon.comdate", ui->lbStartUseDate);

    //-------------------------------------------------
    /*
    setupDisplay("display.wagon.res",
                 false,
                 ui->lbWorkTime);
    */
    //-------------------------------------------------
    ScriptObject *scriptObject = ScriptUnit::getScriptObject("display.wagon.res");

    if(scriptObject)
    {
        connect(scriptObject, &ScriptObject::dataChanged, [=](){

            int int_value = scriptObject->data();
            ui->lbWorkTime->setText(QString("%1").arg( int_value ));
        });
    }
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



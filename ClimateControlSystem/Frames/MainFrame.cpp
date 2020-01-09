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

    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->setVerticalSpacing(1);
    mainLayout->setHorizontalSpacing(1);

    AbstractDisplayWidget *widget0 = new AbstractDisplayWidget("Напруга мережi", "В", 0, 200);
    //setupDisplay("modbus.rs0d10.device", widget0); // тест
    setupDisplay("modbus.rs0d10.r30000", widget0);

    AbstractDisplayWidget *widget1 = new AbstractDisplayWidget("Струм АКБ", "А", -150, 160);
    setupDisplay("modbus.rs0d10.r30001", widget1);

    AbstractDisplayWidget *widget2 = new AbstractDisplayWidget("Струм генератора", "А", 0, 250);
    setupDisplay("modbus.rs0d10.r30002", widget2);

    AbstractDisplayWidget *widget3 = new AbstractDisplayWidget("Корекцiя температури", "°C", 22, 26);
    setupDisplay("modbus.rs0d10.r30003", widget3);

    AbstractDisplayWidget *widget4 = new AbstractDisplayWidget("Темп. салона", "°C", -20, 60);
    setupDisplay("modbus.rs0d10.r30004", widget4);

    AbstractDisplayWidget *widget5 = new AbstractDisplayWidget("Темп. зовнiшня", "°C", -40, 60);
    setupDisplay("modbus.rs0d10.r30005", widget5);

    DateTimeWidget *dateTimeWidget = new DateTimeWidget();

    mainLayout->addWidget(widget0,          0,0,1,1);
    mainLayout->addWidget(widget1,          0,1,1,1);
    mainLayout->addWidget(widget2,          0,2,1,1);
    mainLayout->addWidget(widget3,          0,3,1,1);

    mainLayout->addWidget(widget4,          1,3,1,1);
    mainLayout->addWidget(widget5,          2,3,1,1);
    mainLayout->addWidget(dateTimeWidget,   3,3,1,1);

    //! Задать виджету слой
    setLayout(mainLayout);

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



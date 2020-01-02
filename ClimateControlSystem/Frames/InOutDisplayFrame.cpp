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
    ScriptObject *scriptObject1 = ScriptUnit::getScriptObject("settings.resist.val");
    if(scriptObject1)
    {
        connect(scriptObject1, &ScriptObject::dataChanged, [=](){
            ui->leTempCorrection->setText(QString("%1").arg(scriptObject1->data()));
        });
    }
//    settings.resist.val
//    settings.screen.delay
//    settings.screen.max
//    settings.screen.min
//    settings.screen.opt

    //--------------------------------------

    SEND_TO_LOG( QString("%1 - создан").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
InOutDisplayFrame::~InOutDisplayFrame()
{
    delete ui;
}
//------------------------------------------------------------------------------------
//!



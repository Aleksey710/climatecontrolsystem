#include "ButtonsWidget.h"

#include "ScriptUnit.h"
#include "ScriptObject.h"
//------------------------------------------------------------------------------------
//!
ButtonsWidget::ButtonsWidget(QWidget *parent)
              :QWidget(parent)
{
    QFont buttonFont = font();
//    buttonFont.setPointSize(buttonFont.pointSize() + 2);

    setStyleSheet(QString(
    "QWidget {"
        "padding: 0px, 0px, 0px, 0px;"
        "margin: 0px, 0px, 0px, 0px;"
    "}"
//        "QPushButton{"
//        "color:rgb(0, 0, 0);"
//        //"background-color:rgb(255, 255, 255);"
    "QPushButton#evilButton {"
        //"background-color: red;"
        "border-style: outset;"
        "border-width: 0px;"
        //"border-radius: 10px;"
        //"border-color: beige;"
        //"font: bold 14px;"
        //"min-width: 10em;"
        //"min-height: 10em;"
        "padding: 0px, 0px, 0px, 0px;"
        "margin: 0px, 0px, 0px, 0px;"
    "}"
    "QPushButton#evilButton:pressed {"
        "background-color: rgb(224, 0, 0);"
        //"border-style: inset;"
    "}"
    ));

    int buttonHeight = 50;
    setFixedHeight(buttonHeight);
    //-------------------------------------------------------------------
    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->setMargin(0);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setVerticalSpacing(1);
    mainLayout->setHorizontalSpacing(1);

    //-------------------------------------------------------------------
    m_emptyButton1 = new QPushButton("");
    m_emptyButton2 = new QPushButton("");
    m_emptyButton3 = new QPushButton("");
    m_emptyButton4 = new QPushButton("");
    //-------------------------------------------------------------------
    m_mainFrameButton = new QPushButton("На головну");
    m_mainFrameButton->setFont(buttonFont);
    connect(m_mainFrameButton, &QPushButton::clicked, this, &ButtonsWidget::mainFrameClicked);
    //-------------------------------------------------------------------
    /*
    m_previousFrameButton = new QPushButton("Предыдущий экран");
    m_previousFrameButton->setFont(buttonFont);
    connect(m_previousFrameButton, &QPushButton::clicked, this, &ButtonsWidget::previousFrameClicked);
    */
    //-------------------------------------------------------------------
    m_nextFrameButton = new QPushButton("Наступний екран");
    m_nextFrameButton->setFont(buttonFont);
    connect(m_nextFrameButton, &QPushButton::clicked, this, &ButtonsWidget::nextFrameClicked);
    //-------------------------------------------------------------------
    //-------------------------------------------------------------------
    m_pgUpFrameButton = new QPushButton("назад");
    m_pgUpFrameButton->setFont(buttonFont);
    connect(m_pgUpFrameButton, &QPushButton::clicked, this, &ButtonsWidget::pgUpClicked);
    //-------------------------------------------------------------------
    m_pgDownFrameButton = new QPushButton("вперед");
    m_pgDownFrameButton->setFont(buttonFont);
    connect(m_pgDownFrameButton, &QPushButton::clicked, this, &ButtonsWidget::pgDownClicked);
    //-------------------------------------------------------------------
    //-------------------------------------------------------------------
    m_minusFrameButton = new QPushButton("-");
    m_minusFrameButton->setFont(buttonFont);
    connect(m_minusFrameButton, &QPushButton::clicked, this, &ButtonsWidget::minusClicked);
    //-------------------------------------------------------------------
    m_plusFrameButton = new QPushButton("+");
    m_plusFrameButton->setFont(buttonFont);
    connect(m_plusFrameButton, &QPushButton::clicked, this, &ButtonsWidget::plusClicked);
    //-------------------------------------------------------------------

    mainLayout->addWidget(m_mainFrameButton,              0,0,1,1);
    //mainLayout->addWidget(m_previousFrameButton,          0,1,1,1);
    mainLayout->addWidget(m_nextFrameButton,              0,1,1,1);

    mainLayout->addWidget(m_pgUpFrameButton,              0,2,1,1);
    mainLayout->addWidget(m_pgDownFrameButton,            0,3,1,1);

    mainLayout->addWidget(m_minusFrameButton,             0,2,1,1);
    mainLayout->addWidget(m_plusFrameButton,              0,3,1,1);

    mainLayout->addWidget(m_emptyButton1,                 0,0,1,1);
    mainLayout->addWidget(m_emptyButton2,                 0,1,1,1);
    mainLayout->addWidget(m_emptyButton3,                 0,2,1,1);
    mainLayout->addWidget(m_emptyButton4,                 0,3,1,1);

    setFrameName(FrameName::Main);
    //-------------------------------------------------------------------
    setLayout( mainLayout );

    //-------------------------------------------------------------------
    m_buttonsControlThread = new ButtonsControlThread(this);

    connect(m_buttonsControlThread, &ButtonsControlThread::finished, m_buttonsControlThread, &QObject::deleteLater);

    connect(m_buttonsControlThread, &ButtonsControlThread::bt_1_pressed, [=](){
        if(m_mainFrameButton->isVisible())
        {
            //m_mainFrameButton->click();
            QMetaObject::invokeMethod(m_mainFrameButton, "click", Qt::QueuedConnection);
        }
    });
    connect(m_buttonsControlThread, &ButtonsControlThread::bt_2_pressed, [=](){
        if(m_nextFrameButton->isVisible())
        {
            //m_nextFrameButton->click();
            QMetaObject::invokeMethod(m_nextFrameButton, "click", Qt::QueuedConnection);
        }
    });
    connect(m_buttonsControlThread, &ButtonsControlThread::bt_3_pressed, [=](){
        if(m_minusFrameButton->isVisible())
        {
            //m_minusFrameButton->click();
            QMetaObject::invokeMethod(m_minusFrameButton, "click", Qt::QueuedConnection);
        }
        if(m_pgUpFrameButton->isVisible())
        {
            //m_pgUpFrameButton->click();
            QMetaObject::invokeMethod(m_pgUpFrameButton, "click", Qt::QueuedConnection);
        }
    });
    connect(m_buttonsControlThread, &ButtonsControlThread::bt_4_pressed, [=](){
        if(m_plusFrameButton->isVisible())
        {
            //m_plusFrameButton->click();
            QMetaObject::invokeMethod(m_plusFrameButton, "click", Qt::QueuedConnection);
        }
        if(m_pgDownFrameButton->isVisible())
        {
            //m_pgDownFrameButton->click();
            QMetaObject::invokeMethod(m_pgDownFrameButton, "click", Qt::QueuedConnection);
        }
    });

    //-----------------------------------------
    /*
    connect(m_buttonsControlThread, &ButtonsControlThread::bt_off_pressed, [=](){
        //! Выключение из командной строки
        static const QString setDateCommandString = QString("sudo poweroff");

        QProcess::startDetached( setDateCommandString );
    });
    */

    setupButtonScript();

    //-----------------------------------------
    m_buttonsControlThread->start();
}
//------------------------------------------------------------------------------------
//!
ButtonsWidget::~ButtonsWidget()
{
    m_buttonsControlThread->terminate();
    m_buttonsControlThread->wait();
}
//------------------------------------------------------------------------------------
//!
void ButtonsWidget::setupButtonScript()
{
    ScriptObject *F1_scriptObject = ScriptUnit::getScriptObject("buttons.buttons.F1");

    connect(m_buttonsControlThread, &ButtonsControlThread::bt_1_pressed, [=](){
        if(F1_scriptObject)
        {
            //F1_scriptObject->setData(1);
            QMetaObject::invokeMethod(F1_scriptObject, "setData", Qt::QueuedConnection, Q_ARG(double, 1));
        }
    });
    connect(m_buttonsControlThread, &ButtonsControlThread::bt_1_released, [=](){
        if(F1_scriptObject)
        {
            //F1_scriptObject->setData(0);
            QMetaObject::invokeMethod(F1_scriptObject, "setData", Qt::QueuedConnection, Q_ARG(double, 0));
        }
    });
    //-----------------------------------------
    ScriptObject *F2_scriptObject = ScriptUnit::getScriptObject("buttons.buttons.F2");

    connect(m_buttonsControlThread, &ButtonsControlThread::bt_2_pressed, [=](){
        if(F2_scriptObject)
        {
            //F2_scriptObject->setData(1);
            QMetaObject::invokeMethod(F2_scriptObject, "setData", Qt::QueuedConnection, Q_ARG(double, 1));
        }
    });
    connect(m_buttonsControlThread, &ButtonsControlThread::bt_2_released, [=](){
        if(F2_scriptObject)
        {
            //F2_scriptObject->setData(0);
            QMetaObject::invokeMethod(F2_scriptObject, "setData", Qt::QueuedConnection, Q_ARG(double, 0));
        }
    });
    //-----------------------------------------
    ScriptObject *F3_scriptObject = ScriptUnit::getScriptObject("buttons.buttons.F3");

    connect(m_buttonsControlThread, &ButtonsControlThread::bt_3_pressed, [=](){
        if(F3_scriptObject)
        {
            //F3_scriptObject->setData(1);
            QMetaObject::invokeMethod(F3_scriptObject, "setData", Qt::QueuedConnection, Q_ARG(double, 1));
        }
    });
    connect(m_buttonsControlThread, &ButtonsControlThread::bt_3_released, [=](){
        if(F3_scriptObject)
        {
            //F3_scriptObject->setData(0);
            QMetaObject::invokeMethod(F3_scriptObject, "setData", Qt::QueuedConnection, Q_ARG(double, 0));
        }
    });
    //-----------------------------------------
    ScriptObject *F4_scriptObject = ScriptUnit::getScriptObject("buttons.buttons.F4");

    connect(m_buttonsControlThread, &ButtonsControlThread::bt_4_pressed, [=](){
        if(F4_scriptObject)
        {
            //F4_scriptObject->setData(1);
            QMetaObject::invokeMethod(F4_scriptObject, "setData", Qt::QueuedConnection, Q_ARG(double, 1));
        }
    });
    connect(m_buttonsControlThread, &ButtonsControlThread::bt_4_released, [=](){
        if(F4_scriptObject)
        {
            //F4_scriptObject->setData(0);
            QMetaObject::invokeMethod(F4_scriptObject, "setData", Qt::QueuedConnection, Q_ARG(double, 0));
        }
    });
    //-----------------------------------------
    ScriptObject *Off_scriptObject = ScriptUnit::getScriptObject("buttons.buttons.Off");

    connect(m_buttonsControlThread, &ButtonsControlThread::bt_off_pressed, [=](){
        if(Off_scriptObject)
        {
            //Off_scriptObject->setData(1);
            QMetaObject::invokeMethod(Off_scriptObject, "setData", Qt::QueuedConnection, Q_ARG(double, 1));
        }
    });
    connect(m_buttonsControlThread, &ButtonsControlThread::bt_off_released, [=](){
        if(Off_scriptObject)
        {
            //Off_scriptObject->setData(0);
            QMetaObject::invokeMethod(Off_scriptObject, "setData", Qt::QueuedConnection, Q_ARG(double, 0));
        }
    });
    //-----------------------------------------
}
//------------------------------------------------------------------------------------
//!
void ButtonsWidget::setFrameName(const FrameName &frameName)
{
    switch (frameName)
    {
        case FrameName::Main:
            setButtonState(1,1,0,0,1,1,0,0,0,0);
            break;
        case FrameName::InOutDisplay:
            setButtonState(1,1,0,0,0,0,0,0,1,1);
            break;
        case FrameName::Archive:
            setButtonState(1,1,1,1,0,0,0,0,0,0);
            break;
        case FrameName::CarInformation:
            setButtonState(1,1,0,0,0,0,0,0,1,1);
            break;
        case FrameName::MenuConfigEdit:
            setButtonState(0,0,0,0,0,0,1,1,1,1);
            break;
        default:
            setButtonState(1,1,0,0,0,0,0,0,1,1);
            break;
    }
}
//------------------------------------------------------------------------------------
//!
void ButtonsWidget::setButtonState(bool mainFrameButtonState,
                                   bool nextFrameButtonState,
                                   bool pgUpFrameButtonState,
                                   bool pgDownFrameButtonState,
                                   bool minusFrameButtonState,
                                   bool plusFrameButtonState,
                                   bool emptyButton1State,
                                   bool emptyButton2State,
                                   bool emptyButton3State,
                                   bool emptyButton4State)
{
    m_mainFrameButton->setVisible(mainFrameButtonState);
    m_nextFrameButton->setVisible(nextFrameButtonState);

    m_pgUpFrameButton->setVisible(pgUpFrameButtonState);
    m_pgDownFrameButton->setVisible(pgDownFrameButtonState);

    m_minusFrameButton->setVisible(minusFrameButtonState);
    m_plusFrameButton->setVisible(plusFrameButtonState);

    m_emptyButton1->setVisible(emptyButton1State);
    m_emptyButton2->setVisible(emptyButton2State);
    m_emptyButton3->setVisible(emptyButton3State);
    m_emptyButton4->setVisible(emptyButton4State);
}

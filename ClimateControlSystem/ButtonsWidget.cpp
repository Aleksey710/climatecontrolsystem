#include "ButtonsWidget.h"
//------------------------------------------------------------------------------------
//!
ButtonsWidget::ButtonsWidget(QWidget *parent)
              :QWidget(parent)
{
    QFont buttonFont = font();
//    buttonFont.setPointSize(buttonFont.pointSize() + 2);

    setStyleSheet(QString(
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
        "min-width: 10em;"
        "min-height: 10em;"
        "padding: 1px;"
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
    //QHBoxLayout *mainLayout = new QHBoxLayout();

    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->setMargin(1);
    mainLayout->setVerticalSpacing(1);
    mainLayout->setHorizontalSpacing(1);

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
    connect(m_plusFrameButton, &QPushButton::clicked, this, &ButtonsWidget::minusClicked);
    //-------------------------------------------------------------------
    mainLayout->addWidget(m_mainFrameButton,              0,0,1,1);
    //mainLayout->addWidget(m_previousFrameButton,          0,1,1,1);
    mainLayout->addWidget(m_nextFrameButton,              0,1,1,1);
    mainLayout->addWidget(m_pgUpFrameButton,              0,2,1,1);
    mainLayout->addWidget(m_pgDownFrameButton,            0,3,1,1);
    mainLayout->addWidget(m_minusFrameButton,             0,2,1,1);
    mainLayout->addWidget(m_plusFrameButton,              0,3,1,1);


    setFrameName(FrameName::Main);
    //-------------------------------------------------------------------
    setLayout( mainLayout );
}
//------------------------------------------------------------------------------------
//!
ButtonsWidget::~ButtonsWidget()
{

}
//------------------------------------------------------------------------------------
//!
void ButtonsWidget::setFrameName(const FrameName &frameName)
{
    switch (frameName)
    {
        case FrameName::Main:
            m_pgUpFrameButton->setVisible(false);
            m_pgDownFrameButton->setVisible(false);

            m_minusFrameButton->setVisible(true);
            m_plusFrameButton->setVisible(true);
            break;
        case FrameName::InOutDisplay:
            m_pgUpFrameButton->setVisible(false);
            m_pgDownFrameButton->setVisible(false);

            m_minusFrameButton->setVisible(false);
            m_plusFrameButton->setVisible(false);
            break;
        case FrameName::Archive:
            m_pgUpFrameButton->setVisible(true);
            m_pgDownFrameButton->setVisible(true);

            m_minusFrameButton->setVisible(false);
            m_plusFrameButton->setVisible(false);
            break;
        case FrameName::CarInformation:
            m_pgUpFrameButton->setVisible(false);
            m_pgDownFrameButton->setVisible(false);

            m_minusFrameButton->setVisible(false);
            m_plusFrameButton->setVisible(false);
            break;
    default:
        break;
    }
}


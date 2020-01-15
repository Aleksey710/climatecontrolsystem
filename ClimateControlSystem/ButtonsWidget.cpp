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
        "padding: 6px;"
    "}"
    "QPushButton#evilButton:pressed {"
        "background-color: rgb(224, 0, 0);"
        "border-style: inset;"
    "}"
    ));

    int buttonHeight = 50;
    setFixedHeight(buttonHeight);
    //-------------------------------------------------------------------
    QHBoxLayout *mainLayout = new QHBoxLayout();

    //-------------------------------------------------------------------
    QPushButton *mainFrameButton = new QPushButton("На головну");
    mainFrameButton->setFont(buttonFont);
    connect(mainFrameButton, &QPushButton::clicked, this, &ButtonsWidget::mainFrameClicked);

    mainLayout->addWidget(mainFrameButton);
    //-------------------------------------------------------------------
    /*
    QPushButton *previousFrameButton = new QPushButton("Предыдущий экран");
    previousFrameButton->setFont(buttonFont);
    connect(previousFrameButton, &QPushButton::clicked, this, &ButtonsWidget::previousFrameClicked);

    mainLayout->addWidget(previousFrameButton);
    */
    //-------------------------------------------------------------------
    QPushButton *nextFrameButton = new QPushButton("Наступний екран");
    nextFrameButton->setFont(buttonFont);
    connect(nextFrameButton, &QPushButton::clicked, this, &ButtonsWidget::nextFrameClicked);

    mainLayout->addWidget(nextFrameButton);

    //-------------------------------------------------------------------
    QPushButton *minusFrameButton = new QPushButton("-");
    minusFrameButton->setFont(buttonFont);
    connect(minusFrameButton, &QPushButton::clicked, this, &ButtonsWidget::minusClicked);

    mainLayout->addWidget(minusFrameButton);
    //-------------------------------------------------------------------
    QPushButton *plusFrameButton = new QPushButton("+");
    plusFrameButton->setFont(buttonFont);
    connect(plusFrameButton, &QPushButton::clicked, this, &ButtonsWidget::minusClicked);

    mainLayout->addWidget(plusFrameButton);
    //-------------------------------------------------------------------
    /*
    QPushButton *nextButton = new QPushButton("Следующий экран");

    mainFrameButton->setFixedHeight(50);

    connect(nextButton, &QPushButton::click,
            [=](){

    });
    m_menuLayout->addWidget(nextButton);
    */
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

            break;
        case FrameName::InOutDisplay:

            break;
        case FrameName::Archive:

            break;
        case FrameName::CarInformation:

            break;
    default:
        break;
    }
}


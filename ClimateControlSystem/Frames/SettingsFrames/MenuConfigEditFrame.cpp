#include "MenuConfigEditFrame.h"

//------------------------------------------------------------------------------------
//!
MenuConfigEditFrame::MenuConfigEditFrame(const QList<MenuItemData> &menuItemDataList,
                                         QWidget *parent)
                    :AbstractFrame(parent)
{
    setObjectName("MenuConfigEditForm");

    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->setMargin(0);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setVerticalSpacing(1);
    mainLayout->setHorizontalSpacing(1);

    //std::shared_ptr<QWidget> menuWidget = std::make_shared<QWidget>();
    m_menuWidget = new QWidget();

    m_menuWidget->setStyleSheet(
        "QWidget{ "
        "padding: 0px;"
        "margin: 0px;"
//        "border: 1px solid #000000;"
//        "border-radius : 2px;"
//        "color: blue;"
//        "background-color: yellow;"
        "}"
    );
    //connect(m_menuWidget, &QWidget::destroyed,[](){ qDebug()<< "menuWidget destroyed"; });

    QVBoxLayout *menuLayout = new QVBoxLayout;
    menuLayout->setMargin(0);
    menuLayout->setContentsMargins(0,0,0,0);
    menuLayout->setSpacing(0);


    QFont buttonFont = font();
    buttonFont.setPointSize(buttonFont.pointSize() + 1);

    int buttonHeight = 23;

    for (int i = 0; i < menuItemDataList.size(); ++i)
    {
        MenuItemData menuItemData = menuItemDataList.at(i);

        QPushButton *button = new QPushButton(QString("%1")
                                              .arg(menuItemData.title)
                                              //.arg(menuItemData.name)
                                              );

        button->setStyleSheet(
            "QPushButton{ "
            "padding: 0px;"
            "margin: 0px;"
    //        "border: 1px solid #000000;"
    //        "border-radius : 2px;"
    //        "color: blue;"
    //        "background-color: yellow;"
            "}"
        );
        button->setFixedHeight(buttonHeight);
        button->setFont(buttonFont);

        //! Обработка отпускания кнопки меню
        connect(button, &QPushButton::released, [=](){

            //! Создать форму
            ConfigEditFrame *configEditForm = new ConfigEditFrame(menuItemData.name,
                                                                  menuItemData.title);

            //! При закрытии формы
            connect(configEditForm, &QWidget::destroyed,[=](){
                //! Убрать со слоя форму редактирования
                mainLayout->removeWidget(configEditForm);

                //! Поместить на слой форму меню
                mainLayout->addWidget(m_menuWidget);
                m_menuWidget->setVisible(true);
            });

            //! Убрать со слоя форму меню
            mainLayout->removeWidget(m_menuWidget);
            m_menuWidget->setVisible(false);

            //! Поместить на слой форму редактирования
            mainLayout->addWidget(configEditForm);
        });

        //! Добавить кнопку меню на слой меню
        menuLayout->addWidget(button);
    }
    //---------------------------------------

    QPushButton *exitButton = new QPushButton("Вихiд");

    exitButton->setFixedHeight(buttonHeight);
    exitButton->setFont(buttonFont);

    //! Обработка отпускания кнопки меню
    connect(exitButton, &QPushButton::released,
            this, &MenuConfigEditFrame::deleteLater);

    menuLayout->addWidget(exitButton);

    //---------------------------------------
    menuLayout->addStretch(0);
    //---------------------------------------
    //! Назначить слой меню виджету меню
    m_menuWidget->setLayout(menuLayout);

    //! Добавить на главный слой виджет меню
    mainLayout->addWidget(m_menuWidget);

    //! Задать виджету слой
    setLayout(mainLayout);

    SEND_TO_LOG(QString("%1 - создан").arg(objectName()));
}
//------------------------------------------------------------------------------------
//!
MenuConfigEditFrame::~MenuConfigEditFrame()
{
    m_menuWidget->deleteLater();
    SEND_TO_LOG(QString("%1 - удален").arg(objectName()));
}


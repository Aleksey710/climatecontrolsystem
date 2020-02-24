#include "MenuConfigEditFrame.h"

//------------------------------------------------------------------------------------
//!
MenuConfigEditFrame::MenuConfigEditFrame(const QList<MenuItemData> &menuItemDataList,
                                         QWidget *parent)
                    :AbstractFrame(parent),
                     m_mainLayout ( new QGridLayout ),
                     m_menuLayout ( new QVBoxLayout )
{
    setObjectName("MenuConfigEditForm");


    m_mainLayout->setMargin(0);
    m_mainLayout->setContentsMargins(0,0,0,0);
    m_mainLayout->setVerticalSpacing(1);
    m_mainLayout->setHorizontalSpacing(1);

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

    m_menuLayout->setMargin(0);
    m_menuLayout->setContentsMargins(0,0,0,0);
    m_menuLayout->setSpacing(0);

    m_buttonFont = font();
    m_buttonFont.setPointSize(m_buttonFont.pointSize() + 1);

    //---------------------------------------
    setupTimeConfigButton();

    //---------------------------------------
    for (int i = 0; i < menuItemDataList.size(); ++i)
    {
        MenuItemData menuItemData = menuItemDataList.at(i);

        setupButton(menuItemData);
    }

    //---------------------------------------
    QPushButton *exitButton = new QPushButton("Вихiд");

    exitButton->setFixedHeight(BUTTON_HEIGHT);
    exitButton->setFont(m_buttonFont);

    //! Обработка отпускания кнопки меню
    connect(exitButton, &QPushButton::released,
            this, &MenuConfigEditFrame::deleteLater);

    m_menuLayout->addWidget(exitButton);

    //---------------------------------------
    m_menuLayout->addStretch(0);
    //---------------------------------------
    //! Назначить слой меню виджету меню
    m_menuWidget->setLayout(m_menuLayout);

    //! Добавить на главный слой виджет меню
    m_mainLayout->addWidget(m_menuWidget);

    //! Задать виджету слой
    setLayout(m_mainLayout);

    SEND_TO_LOG(QString("%1 - создан").arg(objectName()));
}
//------------------------------------------------------------------------------------
//!
MenuConfigEditFrame::~MenuConfigEditFrame()
{
    m_menuWidget->deleteLater();
    SEND_TO_LOG(QString("%1 - удален").arg(objectName()));
}
//------------------------------------------------------------------------------------
//!
void MenuConfigEditFrame::setupTimeConfigButton()
{
    QPushButton *button = new QPushButton("Настройка дати i часу");

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
    button->setFixedHeight(BUTTON_HEIGHT);
    button->setFont(m_buttonFont);

    //! Обработка отпускания кнопки меню
    connect(button, &QPushButton::released, [=](){

        DateTimeSetup *dateTimeSetup = new DateTimeSetup();
        dateTimeSetup->setAttribute(Qt::WA_DeleteOnClose);

        //! При закрытии формы
        connect(dateTimeSetup, &QWidget::destroyed,[=](){
            //! Убрать со слоя форму редактирования
            m_mainLayout->removeWidget(dateTimeSetup);

            //! Поместить на слой форму меню
            m_mainLayout->addWidget(m_menuWidget);
            m_menuWidget->setVisible(true);
        });

        //! Убрать со слоя форму меню
        m_mainLayout->removeWidget(m_menuWidget);
        m_menuWidget->setVisible(false);

        //! Поместить на слой форму редактирования
        m_mainLayout->addWidget(dateTimeSetup);
    });

    //! Добавить кнопку меню на слой меню
    m_menuLayout->addWidget(button);
}
//------------------------------------------------------------------------------------
//!
void MenuConfigEditFrame::setupButton(const MenuItemData &menuItemData)
{
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
    button->setFixedHeight(BUTTON_HEIGHT);
    button->setFont(m_buttonFont);

    //! Обработка отпускания кнопки меню
    connect(button, &QPushButton::released, [=](){

        //! Создать форму
        ConfigEditFrame *configEditForm = new ConfigEditFrame(menuItemData.name,
                                                              menuItemData.title);

        //! При закрытии формы
        connect(configEditForm, &QWidget::destroyed,[=](){
            //! Убрать со слоя форму редактирования
            m_mainLayout->removeWidget(configEditForm);

            //! Поместить на слой форму меню
            m_mainLayout->addWidget(m_menuWidget);
            m_menuWidget->setVisible(true);
        });

        //! Убрать со слоя форму меню
        m_mainLayout->removeWidget(m_menuWidget);
        m_menuWidget->setVisible(false);

        //! Поместить на слой форму редактирования
        m_mainLayout->addWidget(configEditForm);
    });

    //! Добавить кнопку меню на слой меню
    m_menuLayout->addWidget(button);
}
//------------------------------------------------------------------------------------
//!

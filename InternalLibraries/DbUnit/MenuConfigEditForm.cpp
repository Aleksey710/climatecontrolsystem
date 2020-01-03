#include "MenuConfigEditForm.h"

//------------------------------------------------------------------------------------
//!
MenuConfigEditForm::MenuConfigEditForm(const QList<MenuItemData> &menuItemDataList,
                                       QWidget *parent)
                   :QWidget(parent)
{
    setObjectName("MenuConfigEditForm");

    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->setVerticalSpacing(1);
    mainLayout->setHorizontalSpacing(1);

    //std::shared_ptr<QWidget> menuWidget = std::make_shared<QWidget>();
    m_menuWidget = new QWidget();
    //connect(m_menuWidget, &QWidget::destroyed,[](){ qDebug()<< "menuWidget destroyed"; });

    QGridLayout *menuLayout = new QGridLayout;

    QFont buttonFont = font();
    buttonFont.setPointSize(buttonFont.pointSize() + 1);

    int buttonHeight = 25;

    for (int i = 0; i < menuItemDataList.size(); ++i)
    {
        MenuItemData menuItemData = menuItemDataList.at(i);

        QPushButton *button = new QPushButton(QString("%1 [%2]")
                                              .arg(menuItemData.title)
                                              .arg(menuItemData.name));

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

    menuLayout->addItem(new QSpacerItem(5,5),1, 1);

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
MenuConfigEditForm::~MenuConfigEditForm()
{
    m_menuWidget->deleteLater();
    SEND_TO_LOG(QString("%1 - удален").arg(objectName()));
}


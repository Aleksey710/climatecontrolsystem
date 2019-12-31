#include "MenuConfigEditForm.h"

//------------------------------------------------------------------------------------
//!
MenuConfigEditForm::MenuConfigEditForm(const QList<MenuItemData> &menuItemDataList,
                                       QWidget *parent)
                   :QWidget(parent)
{
    setObjectName("MenuConfigEditForm");

    QGridLayout *mainLayout = new QGridLayout;

    //std::shared_ptr<QWidget> menuWidget = std::make_shared<QWidget>();
    m_menuWidget = new QWidget();
    connect(m_menuWidget, &QWidget::destroyed,[](){ qDebug()<< "menuWidget destroyed"; });

    QGridLayout *menuLayout = new QGridLayout;

    QFont buttonFont = font();
    buttonFont.setPointSize(buttonFont.pointSize() + 5);

    //int buttonHeight = 60;

    for (int i = 0; i < menuItemDataList.size(); ++i)
    {
        MenuItemData menuItemData = menuItemDataList.at(i);

        QPushButton *button = new QPushButton(QString("%1 [%2]")
                                              .arg(menuItemData.title)
                                              .arg(menuItemData.name));

        //button->setFixedHeight(buttonHeight);
        button->setFont(buttonFont);

        //! Обработка отпускания кнопки меню
        connect(button, &QPushButton::released, [=](){

            //! Создать форму
            ConfigEditFrame *configEditForm = new ConfigEditFrame(menuItemData.name);

            //! При закрытии формы
            connect(configEditForm, &QWidget::destroyed,[=](){
                //! Убрать со слоя форму редактирования
                mainLayout->removeWidget(configEditForm);
                //! Поместить на слой форму меню
                mainLayout->addWidget(m_menuWidget);
            });

            //! Убрать со слоя форму меню
            mainLayout->removeWidget(m_menuWidget);
            //! Поместить на слой форму редактирования
            mainLayout->addWidget(configEditForm);

            //configEditForm->show();
        });

        //! Добавить кнопку меню на слой меню
        menuLayout->addWidget(button);
    }

    menuLayout->addItem(new QSpacerItem(10,500),500, 0);

    //! Назначить слой меню виджету меню
    m_menuWidget->setLayout(menuLayout);

    //! Добавить на главный слой виджет меню
    mainLayout->addWidget(m_menuWidget);

    //! Задать виджету слой
    setLayout(mainLayout);

    //setGeometry(200,200,500,300);
    setWindowTitle(tr("MenuConfigEditForm"));

    SEND_TO_LOG(QString("%1 - создан").arg(objectName()));
}
//------------------------------------------------------------------------------------
//!
MenuConfigEditForm::~MenuConfigEditForm()
{
    m_menuWidget->deleteLater();
    SEND_TO_LOG(QString("%1 - удален").arg(objectName()));
}


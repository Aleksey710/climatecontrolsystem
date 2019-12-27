#include "MenuConfigEditForm.h"

//------------------------------------------------------------------------------------
//!
MenuConfigEditForm::MenuConfigEditForm(const QList<MenuItemData> &menuItemDataList,
                                       QWidget *parent)
                   :QWidget(parent)
{
    QGridLayout *mainLayout = new QGridLayout;

    //QGridLayout *mainLayout = new QGridLayout;
    for (int i = 0; i < menuItemDataList.size(); ++i)
    {
        MenuItemData menuItemData = menuItemDataList.at(i);

        QPushButton *button = new QPushButton(QString("%1 [%2]")
                                              .arg(menuItemData.title)
                                              .arg(menuItemData.name));

        connect(button, &QPushButton::released, [=](){

            ConfigEditForm *configEditForm = new ConfigEditForm(menuItemData.name);

            connect(configEditForm, &QWidget::destroyed,[=](){

            });

            configEditForm->show();
        });

        mainLayout->addWidget(button);
    }

    setLayout(mainLayout);

    setWindowTitle(tr("MenuConfigEditForm"));

    setGeometry(200,200,500,300);
}
//------------------------------------------------------------------------------------
//!
MenuConfigEditForm::~MenuConfigEditForm()
{

}


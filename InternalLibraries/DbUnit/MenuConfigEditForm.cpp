#include "MenuConfigEditForm.h"

//------------------------------------------------------------------------------------
//!
MenuConfigEditForm::MenuConfigEditForm(const QList<MenuItemData> &menuItemDataList,
                                       QWidget *parent)
                   :QWidget(parent)
{
    QGridLayout *menuLayout = new QGridLayout;
    QGridLayout *editLayout = new QGridLayout;

    for (int i = 0; i < menuItemDataList.size(); ++i)
    {
        MenuItemData menuItemData = menuItemDataList.at(i);

        QPushButton *button = new QPushButton(QString("%1 [%2]")
                                              .arg(menuItemData.title)
                                              .arg(menuItemData.name));

        connect(button, &QPushButton::released, [=](){

            ConfigEditForm *configEditForm = new ConfigEditForm(menuItemData.name);

            connect(configEditForm, &QWidget::destroyed,[=](){
                setLayout(menuLayout);
            });

            editLayout->addWidget(configEditForm);
            setLayout(editLayout);
            configEditForm->show();
        });

        menuLayout->addWidget(button);
    }

    setLayout(menuLayout);

    setWindowTitle(tr("MenuConfigEditForm"));

    setGeometry(200,200,500,300);
}
//------------------------------------------------------------------------------------
//!
MenuConfigEditForm::~MenuConfigEditForm()
{

}


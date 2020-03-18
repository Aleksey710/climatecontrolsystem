#include "ItemEditSettingsWidget.h"
#include "ui_ItemEditSettingsWidget.h"

//------------------------------------------------------------------------------------
//!
ItemEditSettingsWidget::ItemEditSettingsWidget(const QVariant &value,
                                               QWidget *parent)
                       :QWidget(parent),
                        ui(new Ui::ItemEditSettingsWidget)
{
    ui->setupUi(this);

    setWindowTitle("Редагування параметру");

    setWindowModality ( Qt::WindowModality::ApplicationModal );

    ui->lbDisplayOld->setText( value.toString() );
    ui->leDisplayNew->setText( value.toString() );

    connect(ui->pbCancel, &QPushButton::released,[=](){
        ui->leDisplayNew->setText( ui->lbDisplayOld->text() );

        emit editingFinished();
        close();
        deleteLater();
    });

    connect(ui->pbSave, &QPushButton::released,[=](){
        emit editingFinished();
        close();
        deleteLater();
    });

    //! Открывать всегда в одном месте
    move(20,20);
}
//------------------------------------------------------------------------------------
//!
ItemEditSettingsWidget::~ItemEditSettingsWidget()
{
    delete ui;
}
//------------------------------------------------------------------------------------
//!
QVariant ItemEditSettingsWidget::value()
{
    return ui->leDisplayNew->text();
}
//------------------------------------------------------------------------------------
//!
//void ItemEditSettingsWidget::setValue(const QVariant &value)
//{
//    return ui->lbDisplayOld->setText( value.toString() );
//}
//------------------------------------------------------------------------------------
//!

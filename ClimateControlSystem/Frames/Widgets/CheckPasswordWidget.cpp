#include "CheckPasswordWidget.h"
#include "ui_CheckPasswordWidget.h"
//------------------------------------------------------------------------------------
//!
CheckPasswordWidget::CheckPasswordWidget(std::function<void()> function,
                                         QWidget *parent)
                    :QWidget(parent),
                     ui(new Ui::CheckPasswordWidget),
                     m_function ( function )
{
    ui->setupUi(this);

    setWindowTitle("Введiть пароль");

    ui->lePassword->setEchoMode(QLineEdit::Password);

    setWindowModality ( Qt::WindowModality::ApplicationModal );
    setAttribute(Qt::WA_DeleteOnClose);
    show();

    connect(ui->pbEnter, &QPushButton::clicked,
            this, &CheckPasswordWidget::checkPassword);

    move(100,100);
}
//------------------------------------------------------------------------------------
//!
CheckPasswordWidget::~CheckPasswordWidget()
{
    delete ui;
}
//------------------------------------------------------------------------------------
//!
void CheckPasswordWidget::checkPassword()
{
    QString enteredPassword = ui->lePassword->text();

    if(enteredPassword == __PASSWORD__)
    {
        qDebug() << "Пароль верен" << enteredPassword << __PASSWORD__;

        SEND_TO_LOG( QString("CheckPasswordWidget - пароль: [%1]").arg(__PASSWORD__) );
        m_function();

        emit passwordIsCorrect(true);
    } else
    {
        qDebug() << "Пароль НЕ верен!" << enteredPassword << __PASSWORD__;
        SEND_TO_LOG( QString("CheckPasswordWidget - пароль: [%1]").arg(__PASSWORD__) );

        emit passwordIsCorrect(false);
    }

    close();
}
//------------------------------------------------------------------------------------
//!

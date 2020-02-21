#ifndef CHECKPASSWORDWIDGET_H
#define CHECKPASSWORDWIDGET_H
//------------------------------------------------------------------------------------
#include <functional>

#include <QWidget>
#include <QPushButton>
#include <QDebug>



#include "Password.h"
//------------------------------------------------------------------------------------
namespace Ui {
class CheckPasswordWidget;
}
//------------------------------------------------------------------------------------
//!
class CheckPasswordWidget : public QWidget
{
        Q_OBJECT

    public:
        explicit CheckPasswordWidget(std::function<void()> function,
                                     QWidget *parent = nullptr);
        ~CheckPasswordWidget();

    signals:
        void passwordIsCorrect(bool state);

    public slots:
        void checkPassword();

    private:
        Ui::CheckPasswordWidget *ui;

        std::function<void()> m_function;
};
//------------------------------------------------------------------------------------
#endif // CHECKPASSWORDWIDGET_H

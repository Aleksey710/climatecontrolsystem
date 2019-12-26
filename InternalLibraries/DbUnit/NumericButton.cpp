#include "NumericButton.h"

//------------------------------------------------------------------------------------
//!
NumericButton::NumericButton(const QString &text, QWidget *parent)
              : QToolButton(parent)
{
    //setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    setText(text);
}
//------------------------------------------------------------------------------------
//!
QSize NumericButton::sizeHint() const
{
    QSize size(50,50);
//    QSize size = QToolButton::sizeHint();
//    size.rheight() += 20;
//    size.rwidth() = qMax(size.width(), size.height());
    return size;
}
//------------------------------------------------------------------------------------
//!

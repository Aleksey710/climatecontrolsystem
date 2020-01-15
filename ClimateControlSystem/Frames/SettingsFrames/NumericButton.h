#ifndef NUMERICBUTTON_H
#define NUMERICBUTTON_H
//------------------------------------------------------------------------------------
#include <QToolButton>


//------------------------------------------------------------------------------------
//!
class NumericButton : public QToolButton
{
        Q_OBJECT
    public:
        explicit NumericButton(const QString &text, QWidget *parent = nullptr);

        QSize sizeHint() const override;
};
//------------------------------------------------------------------------------------
#endif // NUMERICBUTTON_H

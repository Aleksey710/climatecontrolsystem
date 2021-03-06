#ifndef NUMERICKEYPADWIDGET_H
#define NUMERICKEYPADWIDGET_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QRect>
#include <QPushButton>
//#include <>



#include "NumericButton.h"
//------------------------------------------------------------------------------------
//!
class NumericKeypadWidget : public QWidget
{
        Q_OBJECT
    public:
        explicit NumericKeypadWidget(const QVariant &value = 0,
                                     QWidget *parent = nullptr);
        virtual ~NumericKeypadWidget();

        inline QVariant value()
            { return m_display->text().toDouble(); }

        inline void setValue(const QVariant &value)
            { return m_display->setText( value.toString() ); }

    signals:
        void editingFinished();
        //void entered(const QVariant &value);

    private slots:
        void digitClicked();
        void pointClicked();
        void clearClicked();
        void enterClicked();



    private:
        NumericButton *createButton(const QString &text, const char *member);

    private:
        QFont m_font;

        QLineEdit *m_display;

        enum { NumDigitButtons = 10 };

        NumericButton *m_digitButtons[NumDigitButtons];

        bool m_waitingForOperand;
};
//------------------------------------------------------------------------------------
#endif // NUMERICKEYPADWIDGET_H

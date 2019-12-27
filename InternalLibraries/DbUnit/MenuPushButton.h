#ifndef MENUPUSHBUTTON_H
#define MENUPUSHBUTTON_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QWidget>
#include <QPushButton>


//------------------------------------------------------------------------------------
//!
class MenuPushButton : public QPushButton
{
        Q_OBJECT
    public:
        MenuPushButton(const QString &name,
                       const QString &title,
                       QWidget *parent = Q_NULLPTR)
            :QPushButton(title, parent),
             m_name ( name ),
             m_title ( title )
        {

        }

        inline QString name()
            { return m_name; }

        inline QString title()
            { return m_title; }

    private:
        QString m_name;
        QString m_title;
};
//------------------------------------------------------------------------------------
#endif // MENUPUSHBUTTON_H

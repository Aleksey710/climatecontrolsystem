#ifndef MENUITEMDATA_H
#define MENUITEMDATA_H
//------------------------------------------------------------------------------------
#include <QString>

//------------------------------------------------------------------------------------
//!
struct MenuItemData
{
    MenuItemData(const QString &__name,
                 const QString &__title)
        :name ( __name ),
         title ( __title )
    {}

    QString name;
    QString title;
};
//------------------------------------------------------------------------------------
#endif // MENUITEMDATA_H

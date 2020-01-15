#ifndef ELECTRICALEQUIPMENTARCHIVEFORM_H
#define ELECTRICALEQUIPMENTARCHIVEFORM_H
//------------------------------------------------------------------------------------
#include <QObject>
//#include <>
//#include <>
//#include <>
//#include <>


#include "AbstractArchiveForm.h"
//------------------------------------------------------------------------------------
//!
class ElectricalEquipmentArchiveForm : public AbstractArchiveForm
{
        Q_OBJECT
    public:
        explicit ElectricalEquipmentArchiveForm(QWidget *parent = nullptr)
            :AbstractArchiveForm(parent)
        {
            setObjectName(QString("ElectricalEquipmentArchiveForm"));
            setup();
            SEND_TO_LOG(QString("%1 - создан").arg(objectName()));
        }

        virtual ~ElectricalEquipmentArchiveForm()
            {  }

    private:
        virtual QString headLabel() override
            { return QString("Журнал электрообладнання"); }

        virtual QString queryString() override
        {
            return QString(
                "SELECT "
                "strftime('%Y-%m-%d %H:%M:%f',`datetime`/1000,'unixepoch', 'localtime') AS dt, "
                "`msg` "
                "FROM `%1` "
                ";").arg("electrical_equipment_events");
        }
};
//------------------------------------------------------------------------------------
#endif // ELECTRICALEQUIPMENTARCHIVEFORM_H

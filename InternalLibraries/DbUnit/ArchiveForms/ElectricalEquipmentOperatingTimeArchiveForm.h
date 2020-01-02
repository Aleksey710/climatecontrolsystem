#ifndef ELECTRICALEQUIPMENTOPERATINGTIMEARCHIVEFORM_H
#define ELECTRICALEQUIPMENTOPERATINGTIMEARCHIVEFORM_H
//------------------------------------------------------------------------------------
#include <QObject>
//#include <>
//#include <>
//#include <>
//#include <>


#include "AbstractArchiveForm.h"
//------------------------------------------------------------------------------------
//!
class ElectricalEquipmentOperatingTimeArchiveForm : public AbstractArchiveForm
{
        Q_OBJECT
    public:
        explicit ElectricalEquipmentOperatingTimeArchiveForm(QWidget *parent = nullptr)
            :AbstractArchiveForm(parent)
        {
            setObjectName(QString("ElectricalEquipmentOperatingTimeArchiveForm"));
            setup();
            SEND_TO_LOG(QString("%1 - создан").arg(objectName()));
        }

        virtual ~ElectricalEquipmentOperatingTimeArchiveForm()
            {  }

    private:
        virtual QString headLabel() override
            { return QString("Журнал времени работы"); }

        virtual QString queryString() override
        {
            return QString(
                "SELECT "
                "strftime('%Y-%m-%d %H:%M:%f',`datetime`/1000,'unixepoch', 'localtime') AS dt, "
                "`event_types`.`title` "
                "FROM `events`,`event_groups`,`event_types` "
                "WHERE "
                "`events`.`event_group_id`=(SELECT `id` FROM `event_groups` WHERE `name`='electrical_equipment_operating_time') AND "
                "`events`.`event_group_id`=`event_groups`.`id` AND "
                "`events`.`event_type_id`=`event_types`.`id` "
                ";");
        }

};
//------------------------------------------------------------------------------------
#endif // ELECTRICALEQUIPMENTOPERATINGTIMEARCHIVEFORM_H

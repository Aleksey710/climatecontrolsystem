#ifndef ELECTRICALEQUIPMENTOPERATINGTIMEARCHIVEFRAME_H
#define ELECTRICALEQUIPMENTOPERATINGTIMEARCHIVEFRAME_H
//------------------------------------------------------------------------------------
#include <QObject>
//#include <>
//#include <>
//#include <>
//#include <>


#include "AbstractArchiveFrame.h"
//------------------------------------------------------------------------------------
//!
class ElectricalEquipmentOperatingTimeArchiveFrame : public AbstractArchiveFrame
{
        Q_OBJECT
    public:
        explicit ElectricalEquipmentOperatingTimeArchiveFrame(QWidget *parent = nullptr)
            :AbstractArchiveFrame(parent)
        {
            setObjectName(QString("ElectricalEquipmentOperatingTimeArchiveFrame"));
            setup();
            SEND_TO_LOG(QString("%1 - создан").arg(objectName()));
        }

        virtual ~ElectricalEquipmentOperatingTimeArchiveFrame()
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
#endif // ELECTRICALEQUIPMENTOPERATINGTIMEARCHIVEFRAME_H

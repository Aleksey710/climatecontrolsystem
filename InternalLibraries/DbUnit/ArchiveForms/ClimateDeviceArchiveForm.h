#ifndef CLIMATEDEVICEARCHIVEFORM_H
#define CLIMATEDEVICEARCHIVEFORM_H
//------------------------------------------------------------------------------------
#include <QObject>
//#include <>
//#include <>
//#include <>
//#include <>


#include "AbstractArchiveForm.h"
//------------------------------------------------------------------------------------
//!
class ClimateDeviceArchiveForm : public AbstractArchiveForm
{
        Q_OBJECT
    public:
        explicit ClimateDeviceArchiveForm(QWidget *parent = nullptr)
            :AbstractArchiveForm(parent)
        {
            setObjectName(QString("ClimateDeviceArchiveForm"));
            setup();
            SEND_TO_LOG(QString("%1 - создан").arg(objectName()));
        }

        virtual ~ClimateDeviceArchiveForm()
            {  }

    private:
        virtual QString headLabel() override
            { return QString("Журнал климатической установки"); }

        virtual QString queryString() override
        {
            return QString(
                "SELECT "
                "strftime('%Y-%m-%d %H:%M:%f',`datetime`/1000,'unixepoch', 'localtime') AS dt, "
                "`event_types`.`title` "
                "FROM `events`,`event_groups`,`event_types` "
                "WHERE "
                "`events`.`event_group_id`=(SELECT `id` FROM `event_groups` WHERE `name`='climate_device') AND "
                "`events`.`event_group_id`=`event_groups`.`id` AND "
                "`events`.`event_type_id`=`event_types`.`id` "
                ";");
        }

};
//------------------------------------------------------------------------------------
#endif // CLIMATEDEVICEARCHIVEFORM_H

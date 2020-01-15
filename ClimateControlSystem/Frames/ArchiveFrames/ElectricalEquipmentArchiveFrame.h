#ifndef ELECTRICALEQUIPMENTARCHIVEFRAME_H
#define ELECTRICALEQUIPMENTARCHIVEFRAME_H
//------------------------------------------------------------------------------------
#include <QObject>
//#include <>
//#include <>
//#include <>
//#include <>


#include "AbstractArchiveFrame.h"
//------------------------------------------------------------------------------------
//!
class ElectricalEquipmentArchiveFrame : public AbstractArchiveFrame
{
        Q_OBJECT
    public:
        explicit ElectricalEquipmentArchiveFrame(QWidget *parent = nullptr)
            :AbstractArchiveFrame(parent)
        {
            setObjectName(QString("ElectricalEquipmentArchiveFrame"));
            setup();
            SEND_TO_LOG(QString("%1 - создан").arg(objectName()));
        }

        virtual ~ElectricalEquipmentArchiveFrame()
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
#endif // ELECTRICALEQUIPMENTARCHIVEFRAME_H

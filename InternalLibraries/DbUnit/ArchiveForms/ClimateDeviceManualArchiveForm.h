#ifndef CLIMATEDEVICEMANUALARCHIVEFORM_H
#define CLIMATEDEVICEMANUALARCHIVEFORM_H
//------------------------------------------------------------------------------------
#include <QObject>
//#include <>
//#include <>
//#include <>
//#include <>


#include "AbstractArchiveForm.h"
//------------------------------------------------------------------------------------
//!
class ClimateDeviceManualArchiveForm : public AbstractArchiveForm
{
        Q_OBJECT
    public:
        explicit ClimateDeviceManualArchiveForm(QWidget *parent = nullptr)
            :AbstractArchiveForm(parent)
        {
            setObjectName(QString("ClimateDeviceManualArchiveForm"));
            setup();
            SEND_TO_LOG(QString("%1 - создан").arg(objectName()));
        }

        virtual ~ClimateDeviceManualArchiveForm()
            {  }

    private:
        virtual QString headLabel() override
            { return QString("Журнал клiматичної установки режим ручний"); }

        virtual QString queryString() override
        {
            return QString(
                "SELECT "
                "strftime('%Y-%m-%d %H:%M:%f',`datetime`/1000,'unixepoch', 'localtime') AS dt, "
                "`msg` "
                "FROM `%1` "
                ";").arg("climate_device_manual_events");
        }
};
//------------------------------------------------------------------------------------
#endif // CLIMATEDEVICEMANUALARCHIVEFORM_H

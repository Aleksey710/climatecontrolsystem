#ifndef CLIMATEDEVICEAUTOARCHIVEFORM_H
#define CLIMATEDEVICEAUTOARCHIVEFORM_H
//------------------------------------------------------------------------------------
#include <QObject>
//#include <>
//#include <>
//#include <>
//#include <>


#include "AbstractArchiveForm.h"
//------------------------------------------------------------------------------------
//!
class ClimateDeviceAutoArchiveForm : public AbstractArchiveForm
{
        Q_OBJECT
    public:
        explicit ClimateDeviceAutoArchiveForm(QWidget *parent = nullptr)
            :AbstractArchiveForm(parent)
        {
            setObjectName(QString("ClimateDeviceArchiveForm"));
            setup();
            SEND_TO_LOG(QString("%1 - создан").arg(objectName()));
        }

        virtual ~ClimateDeviceAutoArchiveForm()
            {  }

    private:
        virtual QString headLabel() override
            { return QString("Журнал клiматичної установки режим авто"); }

        virtual QString queryString() override
        {
            return QString(
                "SELECT "
                "strftime('%Y-%m-%d %H:%M:%f',`datetime`/1000,'unixepoch', 'localtime') AS dt, "
                "`msg` "
                "FROM `%1` "
                ";").arg("climate_device_auto_events");
        }

};
//------------------------------------------------------------------------------------
#endif // CLIMATEDEVICEAUTOARCHIVEFORM_H

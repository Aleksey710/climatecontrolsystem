#ifndef CLIMATEDEVICEAUTOARCHIVEFRAME_H
#define CLIMATEDEVICEAUTOARCHIVEFRAME_H
//------------------------------------------------------------------------------------
#include <QObject>
//#include <>
//#include <>
//#include <>
//#include <>


#include "AbstractArchiveFrame.h"
//------------------------------------------------------------------------------------
//!
class ClimateDeviceAutoArchiveFrame : public AbstractArchiveFrame
{
        Q_OBJECT
    public:
        explicit ClimateDeviceAutoArchiveFrame(QWidget *parent = nullptr)
            :AbstractArchiveFrame(parent)
        {
            setObjectName(QString("ClimateDeviceAutoArchiveFrame"));
            setup();
            SEND_TO_LOG(QString("%1 - создан").arg(objectName()));
        }

        virtual ~ClimateDeviceAutoArchiveFrame()
            {  }

    private:
        virtual QString headLabel() override
            { return QString("Журнал клiматичної установки режим авто"); }

        virtual QString queryString() override
        {
            return QString(
                "SELECT "
                "strftime('%Y-%m-%d %H:%M:%S',`datetime`/1000,'unixepoch', 'localtime') AS dt, "
                "`msg` "
                "FROM `%1` "
                "ORDER BY `dt` DESC "
                "LIMIT 54 "
                ";").arg("climate_device_auto_events");
        }

};
//------------------------------------------------------------------------------------
#endif // CLIMATEDEVICEAUTOARCHIVEFRAME_H

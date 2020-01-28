#ifndef CLIMATEDEVICEMANUALARCHIVEFRAME_H
#define CLIMATEDEVICEMANUALARCHIVEFRAME_H
//------------------------------------------------------------------------------------
#include <QObject>
//#include <>
//#include <>
//#include <>
//#include <>


#include "AbstractArchiveFrame.h"
//------------------------------------------------------------------------------------
//!
class ClimateDeviceManualArchiveFrame : public AbstractArchiveFrame
{
        Q_OBJECT
    public:
        explicit ClimateDeviceManualArchiveFrame(QWidget *parent = nullptr)
            :AbstractArchiveFrame(parent)
        {
            setObjectName(QString("ClimateDeviceManualArchiveFrame"));
            setup();
            SEND_TO_LOG(QString("%1 - создан").arg(objectName()));
        }

        virtual ~ClimateDeviceManualArchiveFrame()
            {  }

    private:
        virtual QString headLabel() override
            { return QString("Журнал клiматичної установки режим ручний"); }

        virtual QString queryString() override
        {
            return QString(
                "SELECT "
                "strftime('%Y-%m-%d %H:%M:%S',`datetime`/1000,'unixepoch', 'localtime') AS dt, "
                "`msg` "
                "FROM `%1` "
                ";").arg("climate_device_manual_events");
        }
};
//------------------------------------------------------------------------------------
#endif // CLIMATEDEVICEMANUALARCHIVEFRAME_H

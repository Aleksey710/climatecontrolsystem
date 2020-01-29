#include "ArchiveWriter.h"

//------------------------------------------------------------------------------------
//!
ArchiveWriter::ArchiveWriter(QObject *parent)
              : QObject(parent)
{

}
//------------------------------------------------------------------------------------
//!
ArchiveWriter::~ArchiveWriter()
{

}
//------------------------------------------------------------------------------------
//!
ArchiveMsg ArchiveWriter::createArchiveMsg(const ArchiveMsgType &msgType, const double &value)
{
    switch (msgType)
    {
    case ImaxBat:           return ArchiveMsg(ArchiveJournalType::ElectricalEquipment,
                                              QString("").arg(value)); break;
    case WaterInBoilerTemp: return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                              QString("").arg(value)); break;
    case U3000epsend:       return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                              QString("")); break;

    default:
        SEND_TO_LOG(QString("ArchiveWriter - ERROR не известный тип сообщения(msgType=[%1] value=[%2])").arg((int)msgType).arg(value));
            break;
    }


}


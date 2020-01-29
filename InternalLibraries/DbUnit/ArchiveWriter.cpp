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
void ArchiveWriter::writeMsg(const int &msgId,
                             const double &value)
{
    ArchiveMsg archiveMsg = createArchiveMsg(msgId, value);

    QString tableName;

    switch (archiveMsg.journalType)
    {
        case ArchiveJournalType::ElectricalEquipment:
            tableName = "electrical_equipment_events";
            break;
        case ArchiveJournalType::ClimateDeviceAuto:
            tableName = "climate_device_auto_events";
            break;
        case ArchiveJournalType::ClimateDeviceManual:
            tableName = "climate_device_manual_events";
            break;
        case ArchiveJournalType::WorkTime:
            tableName = "work_time_events";
            break;
        default:
            break;
    }

    emit messageRecordingRequest(
        QString("INSERT INTO `%1` (`datetime`,`msg`) "
                "VALUES (%2,'%3');"
                ).arg(tableName)
                 .arg(QDateTime::currentMSecsSinceEpoch())
                 .arg(archiveMsg.msg)
                                 );
}
//------------------------------------------------------------------------------------
//!
ArchiveMsg ArchiveWriter::createArchiveMsg(const int &msgId, const double &value)
{
    switch (msgId)
    {
    case 1:     return ArchiveMsg(ArchiveJournalType::ElectricalEquipment,
                                  QString("I max батареї %6.0f А").arg(value)); break;
    case 2:     return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("Температура води в котлі > %1°C").arg(value)); break;
    case 3:     return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("Відсутня напруга 3000В")); break;
    case 4:     return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("Umax БВВ=%1 В").arg(value)); break;
    case 5:     return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("Перейти в резервний режим управління")); break;
    case 6:     return ArchiveMsg(ArchiveJournalType::ElectricalEquipment,
                                  QString("Umax ЗРК=%1 В").arg(value)); break;
    case 7:     return ArchiveMsg(ArchiveJournalType::ElectricalEquipment,
                                  QString("R ізоляції < 1 кОм")); break;

    case 12:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("Увімкнено НВО")); break;
    case 13:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("Вимкнено НВО")); break;
    case 14:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("Насос опалення вкл.")); break;

    case 15:    return ArchiveMsg(ArchiveJournalType::ElectricalEquipment,
                                  QString("Насос опалення вимкнено")); break;
    case 16:    return ArchiveMsg(ArchiveJournalType::ElectricalEquipment,
                                  QString("Автоматичний режим увімкнено")); break;
    case 17:    return ArchiveMsg(ArchiveJournalType::ElectricalEquipment,
                                  QString("Автоматичний режим вимкнено")); break;
    case 18:    return ArchiveMsg(ArchiveJournalType::WorkTime,
                                  QString("Вимкнення")); break;
    case 19:    return ArchiveMsg(ArchiveJournalType::WorkTime,
                                  QString("Увімкнення")); break;

    case 20:    return ArchiveMsg(ArchiveJournalType::ElectricalEquipment,
                                  QString("Аварія")); break;
    case 21:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("Обрив датчика зовнішньої температури")); break;
    case 22:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("Обрив датчика температури котла.")); break;
    case 23:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("Обрив датчика температури приточного повітря.")); break;
    case 24:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("Обрив датчика температури салону")); break;
    case 25:    return ArchiveMsg(ArchiveJournalType::ElectricalEquipment,
                                  QString("I max генератора %1 А").arg(value)); break;
    case 26:    return ArchiveMsg(ArchiveJournalType::ElectricalEquipment,
                                  QString("Umin АБ=%1 В").arg(value)); break;
    case 27:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("Кондиционер ВІДМОВА увімкнено")); break;
    case 28:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("Кондиционер ВІДМОВА вимкнено")); break;
    case 29:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("Кондиционер РОБОТА увімкнено")); break;

    case 30:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("Кондиционер РОБОТА вимкнено")); break;
    case 31:    return ArchiveMsg(ArchiveJournalType::ElectricalEquipment,
                                  QString("ВІДМОВА конт.охол.1 увімкнено")); break;
    case 32:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("ВІДМОВА конт.охол.1 вимкнено")); break;
    case 33:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("ВІДМОВА конт.охол.2 увімкнено")); break;
    case 34:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("ВІДМОВА конт.охол.2 вимкнено")); break;
    case 35:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("Охолодження увімкнено")); break;
    case 36:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("Охолодження вимкнено")); break;
    case 37:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("Нагрів увімкнено")); break;
    case 38:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("Нагрів вимкнено")); break;
    case 39:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("Не можлива коррекція температури")); break;

    case 40:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("Відсутній відгук від НВО")); break;
    case 41:    return ArchiveMsg(ArchiveJournalType::ElectricalEquipment,
                                  QString("Відсутній відгук від ВВО 1 гр")); break;
    case 42:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("Відсутній відгук від ВВО 2 гр")); break;

    case 58:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("Вентиляція увімкнено")); break;
    case 59:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceAuto,
                                  QString("Вентиляція вимкнено")); break;

    case 43:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceManual,
                                  QString("Температура води в котлі > %1°C").arg(value)); break;
    case 44:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceManual,
                                  QString("Увімкнено ВВО 1 гр")); break;
    case 45:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceManual,
                                  QString("Увімкнено ВВО 2 гр")); break;
    case 46:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceManual,
                                  QString("Вимкнено ВВО 1 гр")); break;
    case 47:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceManual,
                                  QString("Вимкнено ВВО 2 гр")); break;
    case 48:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceManual,
                                  QString("Увімкнено НВО")); break;
    case 49:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceManual,
                                  QString("Вимкнено НВО")); break;
    case 50:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceManual,
                                  QString("Насос опалення вкл.")); break;           // Правописание?
    case 51:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceManual,
                                  QString("Насос опалення вимкнено")); break;
    case 52:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceManual,
                                  QString("Ручний режим увімкнено")); break;
    case 53:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceManual,
                                  QString("Ручний режим вимкнено")); break;
    case 54:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceManual,
                                  QString("Відсутній відгук від НВО")); break;
    case 55:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceManual,
                                  QString("Відсутній відгук від ВВО 1 гр")); break;
    case 56:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceManual,
                                  QString("Відсутній відгук від ВВО 2 гр")); break;
    case 57:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceManual,
                                  QString("Відсутня напруга 3000В")); break;

    case 60:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceManual,
                                  QString("Вентиляція увімкнено")); break;
    case 61:    return ArchiveMsg(ArchiveJournalType::ClimateDeviceManual,
                                  QString("Вентиляція вимкнено")); break;
    default:
        SEND_TO_LOG(QString("ArchiveWriter - ERROR - тип сообщения(msgType=[%1] value=[%2]) - неизвестен").arg((int)msgId).arg(value));
            break;
    }

    return ArchiveMsg(ArchiveJournalType::ElectricalEquipment,
                      QString("ERROR - тип сообщения(msgType=[%1] value=[%2]) - неизвестен").arg((int)msgId).arg(value));
}


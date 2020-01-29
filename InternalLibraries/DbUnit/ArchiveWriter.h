#ifndef ARCHIVEWRITER_H
#define ARCHIVEWRITER_H
//------------------------------------------------------------------------------------
#include <QObject>


//#include ""
#include "Log.h"
#include "ArchiveJournalType.h"
#include "ArchiveMsgType.h"
#include "ArchiveMsg.h"
//------------------------------------------------------------------------------------
//!
class ArchiveWriter : public QObject
{
        Q_OBJECT
    public:
        explicit ArchiveWriter(QObject *parent = nullptr);
        virtual ~ArchiveWriter();

        ArchiveMsg createArchiveMsg(const ArchiveMsgType &msgType,
                                    const double &value = 0.0);

    signals:


};
//------------------------------------------------------------------------------------
#endif // ARCHIVEWRITER_H

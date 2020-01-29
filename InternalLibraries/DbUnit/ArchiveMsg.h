#ifndef ARCHIVEMSG_H
#define ARCHIVEMSG_H
//------------------------------------------------------------------------------------
#include <QString>

//#include ""
//#include ""
//#include ""
#include "ArchiveJournalType.h"
#include "ArchiveMsgType.h"
//------------------------------------------------------------------------------------
// #include "ArchiveMsg.h"
//------------------------------------------------------------------------------------
//!
class ArchiveMsg
{
    public:
        ArchiveMsg(const ArchiveJournalType &__journalType,
                   const QString &__msg)
            :journalType(__journalType),
             msg ( __msg )
        {

        }

        ~ArchiveMsg()
        {

        }

    public:
        ArchiveJournalType  journalType;
        QString             msg;



};
//------------------------------------------------------------------------------------
#endif // ARCHIVEMSG_H

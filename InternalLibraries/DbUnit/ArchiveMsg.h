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
        ArchiveMsg(const ArchiveJournalType &journalType,
                   const QString &msg)
            :m_journalType(journalType),
             m_msg ( msg )
        {

        }

        ~ArchiveMsg()
        {

        }

    public:
        ArchiveJournalType  m_journalType;
        QString             m_msg;



};
//------------------------------------------------------------------------------------
#endif // ARCHIVEMSG_H

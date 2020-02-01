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


    signals:
        void messageRecordingRequest(const QString &queryStr);

    public slots:
        void writeMsg(const int &msgId,
                      const double &value = 0.0);


    private:
        ArchiveMsg createArchiveMsg(const int &msgId,
                                    const double &value = 0.0);
};
//------------------------------------------------------------------------------------
#endif // ARCHIVEWRITER_H
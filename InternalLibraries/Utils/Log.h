#ifndef LOG_H
#define LOG_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QDebug>
#include <QDateTime>
#include <cassert>
#include <QString>
#include <QTextCodec>

//------------------------------------------------------------------------------------
#define easylogging
//------------------------------------------------------------------------------------
#ifdef easylogging
    #include "easylogging++.h"
    #include "easyloggingCustom.h"
    //------------------------------------------------------------------------------------
    // Костыль от варнингов
    static const char *_qwertyuiop_ = el::base::consts::kPerformanceLoggerId;
    struct name___________
    {
        name___________() { t = (char *)&_qwertyuiop_;}
        volatile char *t;
    };
#endif
//------------------------------------------------------------------------------------
#ifdef Q_OS_WIN
    //#define SEND_TO_LOG(msg) LOG(INFO) << QTextCodec::codecForName("CP866")->fromUnicode(msg).constData();
    #define SEND_TO_LOG(msg) qDebug() << QString(msg);
#else
    #ifdef easylogging
        #define SEND_TO_LOG(msg) (LOG(INFO) << QString((msg)));
    #else
        const QString logFileName = "/var/log/usod/USOD.log";

        static Logger logger(logFileName);

/*
        #define SEND_TO_LOG(msg) (qDebug() \
            << QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss.zzz] - ") \
            <<  QString(msg));
*/
        #define SEND_TO_LOG(msg) ( logger.write(msg) );
    #endif
#endif
//------------------------------------------------------------------------------------
inline void loggerSetup(int argc, char *argv[])
{
    Q_UNUSED (argc)
    Q_UNUSED (argv)

    #ifdef easylogging
        easyloggingInit(argc, argv);
    #else
        // install our backtraceHandler

        signal(SIGQUIT,     signalHandler);     //  3 /* Quit (POSIX).  */
        signal(SIGILL,      signalHandler);     //  4 /* Illegal instruction (ANSI).  */

        signal(SIGABRT,     signalHandler);     //  6 /* Abort (ANSI).  */

        signal(SIGFPE,      signalHandler);     //  8 /* Floating-point exception (ANSI).  */
        signal(SIGKILL,     signalHandler);     //  9 /* Kill, unblockable (POSIX).  */

        signal(SIGSEGV,     signalHandler);     // 11 /* Segmentation violation (ANSI).  */

        signal(SIGPIPE,     signalHandler);     // 13 /* Broken pipe (POSIX).  */
        signal(SIGALRM,     signalHandler);     // 14 /* Alarm clock (POSIX).  */
        signal(SIGTERM,     signalHandler);     // 15 /* Termination (ANSI).  */
        signal(SIGSTKFLT,   signalHandler);     // 16 /* Stack fault.  */
    #endif
}
//------------------------------------------------------------------------------------
#endif //!  LOG_H

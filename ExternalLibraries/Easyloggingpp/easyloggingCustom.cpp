#include "easyloggingCustom.h"
//------------------------------------------------------------------------------------
#include "easylogging++.h"
#include <signal.h>
#include <string.h>
//------------------------------------------------------------------------------------
//INITIALIZE_EASYLOGGINGPP
//------------------------------------------------------------------------------------
//void* logRotate(void*)
//{
//    while ( !QCoreApplication::closingDown() )
//    {
//        // Rotate every x*60*60 - каждые x часа
//        sleep(LOG_ROTATE_PERIOD_HOURS*60*60);

//        //-----------------------------------------------
//        LOG(INFO) << "About to rotate log file!";
//        //el::Loggers::getLogger("default")->reconfigure();

//        QString confFileName = QString(QDir::currentPath()+"/easylogging++.conf");

//        el::Loggers::configureFromGlobal(confFileName.toLatin1().data());

//        //--------------------------------------------
//        //! Назначить файл лога
//        //QString timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd_HH_MM");
//        QString timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd_HH");

//        QString logFileName = QString("/var/log/usod/USOD_%1.log").arg(timeStamp);

//        el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Filename, logFileName.toLatin1().data());
//    }
//    return NULL;
//}
//------------------------------------------------------------------------------------
//! My crash handler
void myCrashHandler(int sig)
{
    if(sig != 0)
    {
#ifndef Q_OS_WIN
        LOG(ERROR) << "\r\n"
                   << "---------------------------------------------------------------\r\n"
                   << "                      Woops! Crashed! \r\n"
                   << "---------------------------------------------------------------\r\n"

                   << strsignal(sig)

                   << "---------------------------------------------------------------\r\n"
                      ;

        bool stackTraceIfAvailable = true;
        const el::Level& level = el::Level::Fatal;
        const char* logger = "default";

        el::Helpers::logCrashReason(sig, stackTraceIfAvailable, level, logger);

        //el::base::debug::defaultCrashHandler(sig);

        LOG(ERROR) << "---------------------------------------------------------------\r\n";

        // FOLLOWING LINE IS ABSOLUTELY NEEDED AT THE END IN ORDER TO ABORT APPLICATION
        el::Helpers::crashAbort(sig);
#endif
    }
}
//------------------------------------------------------------------------------------
void easyloggingInit(int argc, char *argv[])
{
    //--------------------------------------------
    //! Инициализация логирования EASYLOGGINGPP
    //! https://habrahabr.ru/post/225363/
    //--------------------------------------------
    START_EASYLOGGINGPP(argc, argv);

    //--------------------------------------------
    el::Configurations defaultConf;
    defaultConf.setToDefault();

    // Values are always std::string
    defaultConf.set(el::Level::Info, el::ConfigurationType::Format, "[%datetime{%Y-%M-%d %H:%m:%s.%g}] - %msg");                                                                     

    // default logger uses default configurations
    el::Loggers::reconfigureLogger("default", defaultConf);

    LOG(INFO) << "Log using default file";

    // To set GLOBAL configurations you may use
    //defaultConf.setGlobally(el::ConfigurationType::Format, "%date %msg");
    //el::Loggers::reconfigureLogger("default", defaultConf);

    //--------------------------------------------
    QString confFileName = QString(QDir::currentPath()+"/easylogging++.conf");

    // Load configuration from file
    el::Configurations confFromFile(confFileName.toLatin1().data());

    // Reconfigure single logger
    //el::Loggers::reconfigureLogger("default", conf);

    if(!confFromFile.empty())
    {
        // Actually reconfigure all loggers instead
        el::Loggers::reconfigureAllLoggers(confFromFile);

        LOG(INFO) << "Config file for easylogging++:" << confFileName;
    } else
    {
        LOG(INFO) << "Log using default config";
    }
    // Now all the loggers will use configuration from file

    //--------------------------------------------
    //el::Loggers::configureFromGlobal(confFileName.toLatin1().data());

    // Info log after manually configuring 'default' logger
    //el::Loggers::getLogger("default")->reconfigure();

    //--------------------------------------------
    el::Loggers::addFlag(el::LoggingFlag::NewLineForContainer);
    el::Loggers::addFlag(el::LoggingFlag::LogDetailedCrashReason);
    el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);
    el::Loggers::addFlag(el::LoggingFlag::DisableApplicationAbortOnFatalLog);

    //el::Loggers::addFlag(el::LoggingFlag::CreateLoggerAutomatically);
    //el::Loggers::addFlag(el::LoggingFlag::AutoSpacing);

    //--------------------------------------------
    // To set GLOBAL configurations you may use
    //logConfig.setGlobally(el::ConfigurationType::Format, "%datetime %level %file(%func)[%line] %msg");
    //logConfig.setGlobally(el::ConfigurationType::Format, "%datetime - %msg");

    //--------------------------------------------
    //! Назначить файл лога
/*
    QString logFileName = QString("/var/log/usod/USOD.log");

    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Filename, logFileName.toLatin1().data());

    LOG(INFO) << "Log file:" << logFileName;
*/
    //--------------------------------------------
    el::Helpers::setCrashHandler(myCrashHandler);
    LOG(INFO) << "The easylogging++ crash handler defined";

    //--------------------------------------------
    //pthread_t logRotatorThread;
    //pthread_create(&logRotatorThread, NULL, logRotate, NULL);

    //--------------------------------------------
/*
    std::thread logRotatorThread([](){

        // Rotate every x*60*60 - каждые x часа
        const std::chrono::seconds wakeUpDelta = std::chrono::seconds(LOG_ROTATE_PERIOD_HOURS*60*60);
        auto nextWakeUp = std::chrono::system_clock::now() + wakeUpDelta;

        bool isWorked = true;

        while(isWorked)
        {
            //! блокирует выполнение текущего потока, пока не будет достигнут указанный момент времени
            std::this_thread::sleep_until(nextWakeUp);
            nextWakeUp += wakeUpDelta;

            LOG(INFO) << "About to rotate log file!";

            auto defaultLogger = el::Loggers::getLogger("default");

            if(defaultLogger == nullptr)
            {
                LOG(ERROR)<<"Oops, it is not called default!";
            } else
            {
                defaultLogger->reconfigure();
            }
        }

        while ( !QCoreApplication::closingDown() )
        {
            // Rotate every x*60*60 - каждые x часа
            sleep(4*60*60);

            //-----------------------------------------------
            LOG(INFO) << "About to rotate log file!";
            //el::Loggers::getLogger("default")->reconfigure();

            QString confFileName = QString(QDir::currentPath()+"/easylogging++.conf");

            el::Loggers::configureFromGlobal(confFileName.toLatin1().data());

            //--------------------------------------------
            //! Назначить файл лога
            //QString timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd_HH_MM");
            QString timeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd_HH");

            QString logFileName = QString("/var/log/usod/USOD_%1.log").arg(timeStamp);

            el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Filename, logFileName.toLatin1().data());
        }

    });

    logRotatorThread.detach();

    //--------------------------------------------
    LOG(INFO) << "The easylogging++ log rotator thread started";
*/
    //--------------------------------------------
    LOG(INFO) << "The easylogging++ is initialized!";    
}

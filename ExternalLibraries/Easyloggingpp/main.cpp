#include <QCoreApplication>
#include <QApplication>
#include <QScopedPointer>
#include <QTimer>
#include <QDebug>
#include <QDir>
//#include <>
//#include <>
//#include <>


//#include ""
//------------------------------------------------------------------------------------
/*
Прописать в pro файле

DEFINES += ELPP_QT_LOGGING
DEFINES += ELPP_STL_LOGGING

#DEFINES += ELPP_ASYNC_LOGGING
# Applicable to GCC only. Enables stacktrace on application crash
DEFINES += ELPP_FEATURE_CRASH_LOG
DEFINES += ELPP_STACKTRACE_ON_CRASH
# Enables handling SIGABRT.
# This is disabled by default to prevent annoying CTRL + C behaviour when you wish to abort.
DEFINES += ELPP_HANDLE_SIGABRT
DEFINES += ELPP_STRICT_SIZE_CHECK ELPP_UNICODE
#DEFINES += ELPP_MULTI_LOGGER_SUPPORT

# Enables thread-safety - make sure -lpthread linking for linux.
DEFINES += ELPP_THREAD_SAFE

# Forces to use C++ standard library for threading (Only useful when using ELPP_THREAD_SAFE
DEFINES += ELPP_FORCE_USE_STD_THREAD

DEFINES += ELPP_NO_DEFAULT_LOG_FILE
*/
//------------------------------------------------------------------------------------
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

#include "easyloggingCustom.h"

//------------------------------------------------------------------------------------
//!
QCoreApplication* createApplication(int &argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        if (!qstrcmp(argv[i], "-no-gui"))
        {
            return new QCoreApplication(argc, argv);
        }
    }
    return new QApplication(argc, argv);
}
//------------------------------------------------------------------------------------
//!
int main(int argc, char *argv[])
{
    //--------------------------------------------
#if QT_VERSION < 0x050000
    //! Кодировка исходных текстов
    QTextCodec *inCodec;
    inCodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(inCodec);
    QTextCodec::setCodecForCStrings(inCodec);
#endif

/*
    //--------------------------------------------
    //! Инициализация логирования
    //--------------------------------------------
    //! Уровень отладки
    //! 1 - дата - сообщение
    //! 2 - дата - имя файла - сообщение
    //! 3 - дата - имя файла - метод - строка(файла) - сообщение
    Log::setDebugLevel(2);

    //! Log::None           - не писать в лог, не писать в файл
    //! Log::Console        - писать лог в консоль
    //! Log::File           - писать лог в файл
    //! Log::FileAndConsole - писать лог в консоль и в файл
    Log::setRecordingType(Log::File);
    Log::setRecordingType(Log::FileAndConsole);
    //! Задать каталог для хранения файла лога
    //! По умолчанию "./log/"
    Log::setLogPath("/var/log/usod/");
    Log::setCurentFileLog("ModbusMaster.log");

    SEND_TO_LOG("*****************************************************************************************")
    SEND_TO_LOG("************     Запуск ModbusMaster     ************************************************")
    SEND_TO_LOG(QString("************     %1     *********************************************************").arg(VERSVN));
    SEND_TO_LOG("*****************************************************************************************")
*/
    //------------------------------------
    QScopedPointer<QCoreApplication> app(createApplication(argc, argv));

    if (qobject_cast<QApplication *>(app.data()))
    {
        // start GUI version...
//        TestForm *testForm = Q_NULLPTR;
//        testForm = new TestForm();
//        testForm->show();

        START_EASYLOGGINGPP(argc, argv);

        el::Loggers::addFlag(el::LoggingFlag::NewLineForContainer);
        el::Loggers::addFlag(el::LoggingFlag::LogDetailedCrashReason);
        el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);

        el::Configurations logConfig;
        logConfig.setToDefault();

        // To set GLOBAL configurations you may use
        logConfig.setGlobally(el::ConfigurationType::Format, "%datetime %level %file(%func)[%line] %msg");

        // default logger uses default configurations
        el::Loggers::reconfigureLogger("default", logConfig);

        el::Helpers::setCrashHandler(myCrashHandler);

        LOG(INFO) << "Перед общим крушением!";
        int *i;
        *i = 0; // Crash!

        // Values are always std::string
        logConfig.set(el::Level::Info, el::ConfigurationType::Format, "%datetime %level %file(%func)[%line] %msg");
//        logConfig.set(el::ConfigurationType::MaxLogFileSize, std::string("0"), true);
//        logConfig.set(el::ConfigurationType::LogFlushThreshold, std::string("0"), true);

        LOG(INFO) << "Log using default file";

        el::Loggers::reconfigureLogger("default", logConfig);

        LOG(INFO) << "Тестовый вывод";

        el::base::debug::StackTrace();

    } else {
       // start non-GUI version...

    }

    QTimer::singleShot(500, app.data(), SLOT(quit()) );

    //------------------------------------
    int exitCode = app->exec();


    return exitCode;
}
//------------------------------------------------------------------------------------

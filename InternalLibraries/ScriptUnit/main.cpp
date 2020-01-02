//------------------------------------------------------------------------------------
#include <QCoreApplication>
#include <QApplication>
#include <QObject>
#include <QTimer>

#include <QDebug>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QScopedPointer>
//#include <>
//#include <>


//#include ""
//#include ""
//#include ""
//#include ""
#include "Log.h"
#include "CheckAppUniq.h"
#include "DbUnit.h"
#include "ScriptUnit.h"

//------------------------------------------------------------------------------------
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

#include "easyloggingCustom.h"
//------------------------------------------------------------------------------------
inline QString allVersion()
{
    return QString("\r\n"
       "********************************************************************\n"
       "****                         VERSIONS                           ****\n"
       "********************************************************************\n"
       "Qt..................: %1 \n"
       "OS..................: %2 \n"
       "Make OS.............: %3 \n"
       "App.................: %4 \n"
       //"SVN.................: %5 \n"
       "Date time created...: %6 \n"
       "--------------------------------------------------------------------\n"
       //"Build version.......: %7 \n"
       "********************************************************************"
       )
       .arg( QString("%1.%2.%3")        .arg(QT_VERSION_MAJOR).arg(QT_VERSION_MINOR).arg(QT_VERSION_PATCH) )            // 1
       .arg( QString("%1 %2 %3 %4")     .arg(DISTRIBUTION1).arg(DISTRIBUTION2).arg(DISTRIBUTION3).arg(DISTRIBUTION4) )  // 2
       .arg( QString("%1 %2 Kernel: %3").arg(QMAKE_HOST_os).arg(QMAKE_HOST_arch).arg(QMAKE_HOST_version) )              // 3
       .arg( QString("%1.%2.%3")        .arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_BUILD) )                     // 4
       //.arg( SVNVersionString() )                                                                                       // 5
       .arg( QString("%1 %2")           .arg(DATE_CREATED).arg(TIME_CREATED) )                                          // 6
       //.arg( QString("%1")              .arg(BUILD_VERSION_CREATED) )                                                   // 7
       ;
}
//------------------------------------------------------------------------------------
//!
int main(int argc, char *argv[])
{
    //--------------------------------------------
    //! Получить список путей поиска плагинов
    QStringList paths = QCoreApplication::libraryPaths();
    //! Начинать поиск с внутренних плагинов
    paths.push_front("./plugins");
    paths.push_front("./lib");
    paths.push_front("./");

    //! Задать список каталогов для поиска плагинов
    QCoreApplication::setLibraryPaths(paths);

    //qDebug() << QString("QCoreApplication::libraryPaths : ") << QCoreApplication::libraryPaths();

    //---------------------------------------------------
    //! Настройка логирования
    loggerSetup(argc, argv);

    //---------------------------------------------------
    SEND_TO_LOG( allVersion() );

    //---------------------------------------------------
    QScopedPointer<QApplication> app( new QApplication(argc, argv) );

    QCoreApplication::setApplicationName("dbUnit");
    QCoreApplication::setApplicationVersion( allVersion() );

    //---------------------------------------------------
    //! Проверка, что приложение еще не запущено
    bool is_running = checkAppUniq();
    //---------------------------------------------------
    // Если уже запущен один экземпляр приложения, то сообщаем ою этом пользователю
    // и завершаем работу текущего экземпляра приложения
    if(is_running)
    {
        SEND_TO_LOG("******************************************************************************************");
        SEND_TO_LOG("**     Попытка запустить 2 экземпляра программы. Запуск прерван!!!                      **");
        SEND_TO_LOG("**     Приложение уже запущено. Вы можете запустить только один экземпляр приложения.   **");
        SEND_TO_LOG("******************************************************************************************");

        return 1;
    }

    //--------------------------------------------

    std::shared_ptr<DbUnit> dbUnit = std::make_shared<DbUnit>();

    std::shared_ptr<ScriptUnit> scriptUnit = std::make_shared<ScriptUnit>();


    //------------------------------------
    //QTimer::singleShot(3*1000, qApp, SLOT(quit()));
    //------------------------------------
    int exitCode = app->exec();

    myCrashHandler(exitCode);

    //------------------------------------
    return exitCode;
}
//------------------------------------------------------------------------------------

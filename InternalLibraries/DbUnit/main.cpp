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
#include "Versions.h"
#include "CheckAppUniq.h"
#include "DbUnit.h"
#include "ConfigEditFrame.h"
#include "MenuConfigEditForm.h"
#include "NumericKeypadWidget.h"
//
#include "ClimateDeviceArchiveForm.h"
//------------------------------------------------------------------------------------
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

#include "easyloggingCustom.h"
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
    QString logFileName = QString("/var/log/ClimateControlSystem/climateControlSystem.log");
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Filename,
                                       logFileName.toLatin1().data());
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

//    std::shared_ptr<ConfigEditForm> configEditForm = std::make_shared<ConfigEditForm>();
//    configEditForm->show();

//    std::shared_ptr<NumericKeypadWidget> numericKeypadWidget = std::make_shared<NumericKeypadWidget>();
//    numericKeypadWidget->show();

    //------------------------------------
//    std::shared_ptr<MenuConfigEditForm> menuConfigEditForm
//            = std::make_shared<MenuConfigEditForm>(dbUnit->settingsMenuItemList());
//    menuConfigEditForm->show();

    //------------------------------------
    std::shared_ptr<ClimateDeviceArchiveForm> climateDeviceArchiveForm
            = std::make_shared<ClimateDeviceArchiveForm>();
    climateDeviceArchiveForm->show();

    //------------------------------------
    //QTimer::singleShot(3*1000, qApp, SLOT(quit()));
    //------------------------------------
    int exitCode = app->exec();

    myCrashHandler(exitCode);

    if(climateDeviceArchiveForm)
        climateDeviceArchiveForm->deleteLater();

    if(dbUnit)
        dbUnit->deleteLater();

    //------------------------------------
    SEND_TO_LOG("*****************************************************************************************");
    SEND_TO_LOG("************     Окончание работы                                      ******************");
    SEND_TO_LOG("*****************************************************************************************");
    //------------------------------------
    return exitCode;
}
//------------------------------------------------------------------------------------

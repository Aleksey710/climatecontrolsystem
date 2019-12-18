//------------------------------------------------------------------------------------
//#include <>
//#include <>
//#include <>
#include <QApplication>
#include <QObject>
#include <QTimer>
#include <QWidget>


#include "Log.h"
#include "Widget.h"
#include "svn_version.h"
#include "ModbusMasterUnit.h"
#include "MqttModbusMasterConfigurator.h"
#include "MqttUnitThread.h"
#include "ManagerConfigurations.h"
//#include ""
//#include ""
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
    //------------------------------------------------------------------------------------
#if QT_VERSION < 0x050000
    //! Кодировка исходных текстов
    QTextCodec *inCodec;
    inCodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(inCodec);
    QTextCodec::setCodecForCStrings(inCodec);
#endif

    //------------------------------------------------------------------------------------
//    Q_INIT_RESOURCE(MainWindow);

    //! Получить список путей поиска плагинов
    QStringList paths = QCoreApplication::libraryPaths();
    //! Начинать поиск с внутренних плагинов
    paths.push_front("./plugins");

    //"/opt/Qt5.7.1/5.7/gcc_64/plugins"

    //! Задать список каталогов для поиска плагинов
    QCoreApplication::setLibraryPaths(paths);

    qDebug() << QCoreApplication::libraryPaths();

    //! Настройка логирования
    loggerSetup(argc, argv);

    //------------------------------------------------------------------------------------
    SEND_TO_LOG(        "*****************************************************************************************");
    SEND_TO_LOG(        "************     Запуск MqttModbusMasterUnit      ***************************************");
    //SEND_TO_LOG(QString("************     %1     *********************************************************").arg(VERSVN));
    SEND_TO_LOG( allVersion() );


    //------------------------------------------------------------------------------------
    //QScopedPointer<QCoreApplication> app(createApplication(argc, argv));
    QCoreApplication *app = createApplication(argc, argv);

    //ModbusMasterUnit::instance();
    //ModbusMasterUnit::Instance().setParent(app);

    if (qobject_cast<QApplication *>(app))
    {
        QObject *parent = new QObject();


        parent->setObjectName("parent");

        //-------------------------------------------
        //! Для сервера !!!
        //! Задать тип сетевой работы
        ManagerConfigurations::Instance().setNetworkType(ManagerConfigs::Slave);

        //! Не использовать базу!
        ManagerConfigurations::Instance().setUsedDb(false);


        QObject::connect(&( ManagerConfigurations::Instance() ), &ManagerConfigsThread::ready,
                         [=](){

            SEND_TO_LOG("Начальная инициализация базы завершена");

            // start GUI version...
            //-------------------------------------------
            QString stationName = "test";
            //QString stationName = "stolbovo";

            //QString dpdName = "SSOD";
            QString dpdName = "USOD1";

            QString unitName = "MPU";

            DbSettings dbSettings;

            dbSettings.hostName     = "127.0.0.1";
            //dbSettings.hostName     = "192.168.239.234";

            dbSettings.dbName       = "test";
            //dbSettings.dbName       = "stolbovo";

            dbSettings.userName     = "scada_user";
            dbSettings.userPassword = "simple_pass";
            dbSettings.dbType       = "QMYSQL";
            dbSettings.tableType    = "MyISAM";

            MqttConnectionSettings mqttConnectionSettings(QHostAddress("127.0.0.1"),
            //MqttConnectionSettings mqttConnectionSettings(QHostAddress("192.168.239.234"),
                                                          1883,
                                                          "admin",
                                                          "admin");
            //-------------------------------------------
            //-------------------------------------------
            //-------------------------------------------

            MqttUnitThread *mqttUnitThread = new MqttUnitThread(parent);

            QObject::connect(mqttUnitThread, &MqttUnitThread::initialized, [=](){

                if(0)
                {
                    SEND_TO_LOG( QString("%1 - MqttModbusMasterUnit не будет запущен!!!").arg(parent->objectName()) );
                    return;
                }

                SEND_TO_LOG( QString("%1 - завершена инициализация MqttModbusMasterUnit").arg(parent->objectName()) );

                //-------------------------------------------

                //qApp->quit();
            });


            mqttUnitThread->init<MqttModbusMasterUnit, MqttModbusMasterConfigurator>(stationName,
                                                                                       dpdName,
                                                                                       unitName,
                                                                                       dbSettings,
                                                                                       mqttConnectionSettings);


            //-------------------------------------------
            //-------------------------------------------
            //-------------------------------------------
        });

        //-------------------------------------------
        //! Проинициализировать менеджер конфигурации
        ManagerConfigurations::Instance().setup();

        //------------------------------------------------------------------------------------
        //! Сначала создать клиента, чтоб он сработал по сигналу готовности менеджера конфигураций
        //QTimer::singleShot(20000, qApp, SLOT(quit()));

    } else {
       // start non-GUI version...

    }

    //------------------------------------
    int exitCode = app->exec();

    myCrashHandler(exitCode);
    //------------------------------------

    ManagerConfigurations::destroy();


    SEND_TO_LOG("*****************************************************************************************");
    SEND_TO_LOG("************     НОРМАЛЬНОЕ ОКОНЧАНИЕ РАБОТЫ MqttModbusMasterUnit      ******************");
    SEND_TO_LOG("*****************************************************************************************");

    return exitCode;
}
//------------------------------------------------------------------------------------

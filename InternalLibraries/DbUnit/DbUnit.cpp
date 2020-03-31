#include "DbUnit.h"
//------------------------------------------------------------------------------------
QString DbUnit::m_dbFileAddress = "./conf/db.sqlite";
//------------------------------------------------------------------------------------
//!
DbUnit::DbUnit(QObject *parent)
       :QObject(parent)
{
    m_dbFileAddress = qApp->applicationDirPath()+"/conf/db.sqlite";

    setObjectName(QString("DbUnit[%1]").arg(m_dbFileAddress));

    SEND_TO_LOG(QString("%1 - создан").arg(objectName()));

    if ( !QFile(m_dbFileAddress).exists() )
    {
        openDb();
        createDb();
    } else
    {
        openDb();
    }

    connect(&m_archiveWriter, &ArchiveWriter::messageRecordingRequest, this, &DbUnit::exequteQuery);
}
//------------------------------------------------------------------------------------
//!
DbUnit::~DbUnit()
{
    QSqlDatabase::database(DbUnit::dbName(), false).close();
    QSqlDatabase::removeDatabase(m_dbFileAddress);

    SEND_TO_LOG(QString("%1 - удален").arg(objectName()));
}
//------------------------------------------------------------------------------------
//!
void DbUnit::openDb()
{
    QSqlDatabase::database(DbUnit::dbName(), false).close();
    QSqlDatabase::removeDatabase(DbUnit::dbName());
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DbUnit::dbName());

    // Additionally, name can be set to ":memory:" which will create a temporary database
    // which is only available for the lifetime of the application.
    //db.setDatabaseName(":memory:");

    if (!db.open())
    {
        QSqlError err = db.lastError();

        SEND_TO_LOG(QString("%1 - ошибка открытия базы [%2]").arg(objectName()).arg(err.text()));

        db = QSqlDatabase();
        QSqlDatabase::removeDatabase(DbUnit::dbName());
    } else
    {
        SEND_TO_LOG(QString("%1 - база подключена").arg(objectName()));
    }
}
//------------------------------------------------------------------------------------
//!
QList<MenuItemData> DbUnit::settingsMenuItemList()
{
    QList<MenuItemData> menuItemDataList;

    QSqlDatabase db(QSqlDatabase::database(DbUnit::dbName()));

    QSqlQuery query("SELECT `name`,`title` "
                    "FROM `groups` "
                    "WHERE `type_id`=(SELECT `id` FROM `types` WHERE `name`='settings')"
                    ";", db);

    if( !query.exec() )
    {
        QSqlError err = db.lastError();

        SEND_TO_LOG( QString("%1 - Error menuItemDataList [%2]")
                     .arg(objectName()).arg(err.text()))
    } else
    {
        while (query.next())
        {
            menuItemDataList.append(MenuItemData(query.value(0).toString(),
                                                 query.value(1).toString())
                                    );
        }
    }

    return menuItemDataList;
}
//------------------------------------------------------------------------------------
//!
void DbUnit::exequteQuery(const QString &query)
{
    QSqlDatabase db(QSqlDatabase::database(DbUnit::dbName()));

    QSqlQuery sqlQuery(db);

    if( !sqlQuery.exec(query) )
    {
        QSqlError err = db.lastError();

        SEND_TO_LOG( QString("%1 - Error [%2] [%3]")
                     .arg(objectName()).arg(query).arg(err.text()))
    }
}
//------------------------------------------------------------------------------------
//!
void DbUnit::exequteQueryList(const QStringList &queryStringList)
{
    QSqlDatabase db(QSqlDatabase::database(DbUnit::dbName()));

    QSqlQuery sqlQuery(db);

    QStringList::const_iterator constIterator;
    for (constIterator = queryStringList.constBegin();
            constIterator != queryStringList.constEnd();
                ++constIterator)
    {
        if( !sqlQuery.exec( (*constIterator) ) )
        {
            QSqlError err = db.lastError();

            SEND_TO_LOG( QString("%1 - Error [%2] [%3]")
                         .arg(objectName()).arg( (*constIterator) ).arg(err.text()))
        }
    }
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createDb()
{
    SEND_TO_LOG("----------------------------------------------------------");
    SEND_TO_LOG(QString("%1 - создание структуры базы").arg(objectName()));
    SEND_TO_LOG("----------------------------------------------------------");

    QStringList queryStringList;

    queryStringList.append(
        "PRAGMA foreign_keys = 0;"
        );

    queryStringList.append(
        "CREATE TABLE IF NOT EXISTS `types` ( "
        "`id` INTEGER NOT NULL PRIMARY KEY, "
        "`name` TEXT NOT NULL "
        "); "
        );

    queryStringList.append("INSERT INTO `types` (`id`,`name`) VALUES (1, 'settings');");

    //----------------------------------------------------------
    queryStringList.append(
        "CREATE TABLE IF NOT EXISTS `data_types` ( "
        "`id` INTEGER NOT NULL PRIMARY KEY, "
        "`type` TEXT NOT NULL "
        "); "
        );

    queryStringList.append("INSERT INTO `data_types` (`id`,`type`) VALUES (1, 'double');");
    queryStringList.append("INSERT INTO `data_types` (`id`,`type`) VALUES (2, 'text');");

    //----------------------------------------------------------
    queryStringList.append(
        "CREATE TABLE IF NOT EXISTS `groups` ( "
        "`id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
        "`type_id` INTEGER NOT NULL "
        "REFERENCES `types` (`id`) "
        "ON DELETE CASCADE "
        "ON UPDATE CASCADE "
        "MATCH [FULL], "
        "`name` TEXT NOT NULL, "
        "`title` TEXT NOT NULL "
        "); "
        );

    queryStringList.append(
        "CREATE TABLE IF NOT EXISTS `data` ( "
        "`id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
        "`group_id` INTEGER NOT NULL "
        "REFERENCES `groups` (`id`) "
        "ON DELETE CASCADE "
        "ON UPDATE CASCADE "
        "MATCH [FULL], "
        "`name` TEXT NOT NULL, "
        "`title` TEXT NOT NULL, "
        //"`value` REAL NOT NULL "
        "`value` REAL DEFAULT 0,"
        "`data_type_id` INTEGER NOT NULL DEFAULT 1 "
        "REFERENCES `data_types` (`id`) "
        "ON DELETE CASCADE "
        "ON UPDATE CASCADE "
        "MATCH [FULL] "
        "); "
    );

    setupSettings(queryStringList);

    setupArchiveEvents(queryStringList);

    //-------------------------------------------
    exequteQueryList(queryStringList);
}
//------------------------------------------------------------------------------------
//!
void DbUnit::setupSettings(QStringList &queryStringList)
{
    queryStringList.append("INSERT INTO `groups` (`type_id`,`name`,`title`) "
                           "VALUES ((SELECT `id` FROM `types` WHERE `name`='settings'),'offset',"
                           "'Корекція дельт для аналогових входів');");
    createOffsetGroup(queryStringList);

    queryStringList.append("INSERT INTO `groups` (`type_id`,`name`,`title`) "
                           "VALUES ((SELECT `id` FROM `types` WHERE `name`='settings'),'temp', "
                           "'Налаштування для температур');");
    createTempGroup(queryStringList);

    queryStringList.append("INSERT INTO `groups` (`type_id`,`name`,`title`) "
                           "VALUES ((SELECT `id` FROM `types` WHERE `name`='settings'),'bat', "
                           "'Налаштування для батареї');");
    createBatGroup(queryStringList);

    queryStringList.append("INSERT INTO `groups` (`type_id`,`name`,`title`) "
                           "VALUES ((SELECT `id` FROM `types` WHERE `name`='settings'),'lim', "
                           "'Ліміти які відображаються на головній сторінці');");
    createLimGroup(queryStringList);

    queryStringList.append("INSERT INTO `groups` (`type_id`,`name`,`title`) "
                           "VALUES ((SELECT `id` FROM `types` WHERE `name`='settings'),'gen', "
                           "'Налаштування для генератора');");
    createGenGroup(queryStringList);

    queryStringList.append("INSERT INTO `groups` (`type_id`,`name`,`title`) "
                           "VALUES ((SELECT `id` FROM `types` WHERE `name`='settings'),'volt', "
                           "'Налаштування для бортовий мережі');");
    createVoltGroup(queryStringList);

    queryStringList.append("INSERT INTO `groups` (`type_id`,`name`,`title`) "
                           "VALUES ((SELECT `id` FROM `types` WHERE `name`='settings'),'avg', "
                           "'Затримки накопичення');");
    createAvgGroup(queryStringList);

    queryStringList.append("INSERT INTO `groups` (`type_id`,`name`,`title`) "
                           "VALUES ((SELECT `id` FROM `types` WHERE `name`='settings'),'delay', "
                           "'Налаштування затримок НВО та ВВО');");
    createDelayGroup(queryStringList);

    queryStringList.append("INSERT INTO `groups` (`type_id`,`name`,`title`) "
                           "VALUES ((SELECT `id` FROM `types` WHERE `name`='settings'),'wagon', "
                           "'Налаштування параметрів вагону');");
    createWagonGroup(queryStringList);

    queryStringList.append("INSERT INTO `groups` (`type_id`,`name`,`title`) "
                           "VALUES ((SELECT `id` FROM `types` WHERE `name`='settings'),'password', "
                           "'Зміна пароля');");
    createPasswordGroup(queryStringList);

    queryStringList.append("INSERT INTO `groups` (`type_id`,`name`,`title`) "
                           "VALUES ((SELECT `id` FROM `types` WHERE `name`='settings'),'screen', "
                           "'Налаштування параметрів экрану');");
    createScreenGroup(queryStringList);

    queryStringList.append("INSERT INTO `groups` (`type_id`,`name`,`title`) "
                           "VALUES ((SELECT `id` FROM `types` WHERE `name`='settings'),'cond', "
                           "'Налаштування кондиціонера');");
    createCondGroup(queryStringList);

    queryStringList.append("INSERT INTO `groups` (`type_id`,`name`,`title`) "
                           "VALUES ((SELECT `id` FROM `types` WHERE `name`='settings'),'resist', "
                           "'Аварія при порушенні ізоляції');");
    createResistGroup(queryStringList);

    queryStringList.append("INSERT INTO `groups` (`type_id`,`name`,`title`) "
                           "VALUES ((SELECT `id` FROM `types` WHERE `name`='settings'),'fun', "
                           "'Налаштування параметрів охолодження процессора');");
    createFunGroup(queryStringList);

    //queryStringList.append("INSERT INTO `groups` (`name`,`title`) VALUES ('',   '');");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createOffsetGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'tc', 'Корекція дельт для температури купе', 0.0);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'af', 'Корекція дельт для припливної вентиляції', 0.0);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'to', 'Корекція дельт для температури зовнішнього повітря', 0.0);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'tb', 'Корекція дельт для температури котла', 0.0);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'cb', 'Корекція дельт для струму батареї', 0.0);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'cg', 'Корекція дельт для струму генератора', 0.0);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'nv', 'Корекція дельт для напруги мережі', 0.0);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'cmc', 'Коефіцієнт нахилу(матеріалу) для температури купе', 1.0);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'cmf', 'Коефіцієнт нахилу(матеріалу) для припливної вентиляції', 1.0);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'cmo', 'Коефіцієнт нахилу(матеріалу) для температури зовнішнього повітря', 1.0);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'cmb', 'Коефіцієнт нахилу(матеріалу) для температури котла', 1.0);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'cmi', 'Коефіцієнт нахилу(матеріалу) для струму батареї', 1.0);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'cmg', 'Коефіцієнт нахилу(матеріалу) для струму генератора', 1.0);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'cmv', 'Коефіцієнт нахилу(матеріалу) для напруги мережі', 1.0);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'oc', 'Дільник для значень АЦП', 10);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createTempGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'sev', 'Значення при якому з`являеться повідомлення про обрив датчика', 1000);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'bt', 'Максимальна температура котла, °C', 90);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'ibt', 'Iнтервал перевищення максимальної температури котла, Сек', 10);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'tpo', 'Зовнішня температура необхідна для включення насоса, °C', -10);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'onnvo', 'Зовнішня температура необхідна для включення НВО, °C', 15);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'onlvhd', 'Гістерезис температури для включення НВО, °C', 2);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'offlvhd', 'Гістерезис температури для виключення НВО, °C', 1);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'offnvo', 'зовнішня температура необхідна для виключення НВО, °C', 15);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'vvohefon', 'Гістерезис для температури уставки для включення ВВО', 2);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'vvohefoff', 'Гістерезис для температури уставки для відключення ВВО', 1);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'vvootfdon', 'зовнішня температура необхідна для ввімкненя другої групи ВВО', -10);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'vvootfdoff', 'Зовнішня температура необхідна для вимкненя другої групи ВВО', -8);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'vvohoton', 'Зовнішня температура необхідна для ввімкненяя ВВО', 5);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'vvohotoff', 'Зовнішня температура необхідна для вимкненя ВВО', 6);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'x0', 'T(вкл) = x0 + x2 * (T(уст)-x3) - x4 * Т(нв) + x5 * (T(уст) - T(сал))', 35);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'x1', 'T(викл) = x1 + x2 * (T(уст)-x3) - x4 * Т(нв) + x5 * (T(уст) - T(сал))', 55);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'x2', 'T(вкл/викл) = x1 + x2 * (T(уст)-x3) - x4 * Т(нв) + x5 * (T(уст) - T(сал))', 2.5);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'x3', 'T(вкл/викл) = x1 + x2 * (T(уст)-x3) - x4 * Т(нв) + x5 * (T(уст) - T(сал))', 22);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'x4', 'T(вкл/викл) = x1 + x2 * (T(уст)-x3) - x4 * Т(нв) + x5 * (T(уст) - T(сал))', 1.5);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'x5', 'T(вкл/викл) = x1 + x2 * (T(уст)-x3) - x4 * Т(нв) + x5 * (T(уст) - T(сал))', 8);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'sut', 'Температура уставки, °C', 24);");

    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'useBVV', 'Використання датчикiв температри БВВ true(1) або false(0) - використання окремих датчикiв.', 1);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createBatGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='bat'), "
        "'mcb', 'Максимальний струм батареї, А', 100);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='bat'), "
        "'imcb', 'Iнтервал перевищення струму батареї, Сек', 60);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createLimGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'micb', 'Мінімум струм батареї', -150);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'macb', 'Максимум струм батареї', 160);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'micg', 'Мінімум струм генератора', 0);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'macg', 'Максимум струм генератора', 250);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'mivn', 'Мінімум напруга бортової мережі', 0);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'mavn', 'Максимум напруга бортової мережі', 200);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'mitb', 'Мінімум температура котла', 0);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'matb', 'Максимум температура котла', 110);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'mito', 'Мінімум температура ззовні', -40);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'mato', 'Максимум температура ззовні', 60);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'miti', 'Мінімум температура салону', -20);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'mati', 'Максимум температура салону', 60);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'mitaf', 'Мінімум температура припливної вентиляції', -40);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'mataf', 'Максимум температура припливної вентиляції', 100);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createGenGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='gen'), "
        "'mcg', 'Максимальний струм генератора, А', 235);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='gen'), "
        "'imcg', 'Iнтервал перевищення струму генератора, Сек', 2);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createVoltGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='volt'), "
        "'mabn', 'Максимальна напруга бортової  мережі, V', 150);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='volt'), "
        "'maibn', 'Iнтервал перевищення напруги бортової мережі, Сек', 2);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='volt'), "
        "'mibn', 'Мінімальна напруга бортової мережі, V', 70);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='volt'), "
        "'miibn', 'Iнтервал заниження напруги бортової мережі, Сек', 10);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createAvgGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='avg'), "
        "'coupe', 'Температура салону', 10);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='avg'), "
        "'airflow', 'Температура припливної вентиляції', 10);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='avg'), "
        "'out', 'Температура ззовні', 10);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='avg'), "
        "'boiler', 'Температура котла', 10);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='avg'), "
        "'bat', 'Струм батареї', 5);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='avg'), "
        "'gen', 'Струм генератора', 5);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='avg'), "
        "'volt', 'Напруга мережі', 5);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createDelayGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='delay'), "
        "'vvodsd', 'Затримка повторного включення ВВО, Сек', 15);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='delay'), "
        "'vvosod', 'Затримка включення ВВО, Сек', 5);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='delay'), "
        "'vvord', 'Затримка відповіді включення ВВО від БВВ, Сек', 5);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='delay'), "
        "'dlhon', 'Затримка включення НВО, Сек', 5);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='delay'), "
        "'dlhoff', 'Затримка виключення НВО, Сек', 5);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='delay'), "
        "'dlhr', 'Затримка відповіді включення НВО від БВВ, cек', 5);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='delay'), "
        "'dlh', 'Затримка повторного включення НВО, cек', 15);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createWagonGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`data_type_id`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='wagon'), "
        "'dd','дата установки ПЗ, формат \"рррр-мм-дд\"',2,'2020-01-01');");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`data_type_id`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='wagon'), "
        "'sv','версія ПЗ',2,'2.3.11');");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`data_type_id`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='wagon'), "
        "'num', 'номер вагона',2,'11-14551');");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='wagon'), "
        "'res', 'Використаний ресурсу мотогодин у хвилинах','0');");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`data_type_id`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='wagon'), "
        "'comdate', 'Введення вагона в експлуатацію, формат \"рррр-мм-дд\"',2,'2020-04-01');");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createPasswordGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`data_type_id`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='password'), "
        "'new','Зміна пароля',2,'1234');");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createScreenGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='screen'), "
        "'opt', 'Увімкнення режиму збереження екрану(true(1) або false(0))', 1);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='screen'), "
        "'min', 'Мінімальна яркість(від 0 до 7)', 4);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='screen'), "
        "'max', 'Максимальна яркість(від 0 до 7)', 6);");
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='screen'), "
        "'delay', 'Затримка(мс)', 120000);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createCondGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='cond'), "
        "'ccm', 'Вкл/Вимк спільної роботи НВО та Ел. Калоріфер (Нагрів), true(1) або false(0)', 0);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createResistGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='resist'), "
        "'val', 'Аварія при порушенні ізоляції true(1) або false(0)', 1);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createFunGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='fun'), "
        "'ton', 'Температура увiмкнення', 35);");

    queryStringList.append(
        "INSERT INTO `data` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='fun'), "
        "'toff', 'Температура вимкнення', 30);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::setupArchiveEvents(QStringList &queryStringList)
{
/*
//    queryStringList.append(
//        "CREATE TABLE IF NOT EXISTS `event_groups` ( "
//        "`id` INTEGER NOT NULL PRIMARY KEY, "
//        "`name` TEXT NOT NULL, "
//        "`title` TEXT NOT NULL "
//        "); "
//        );

//    queryStringList.append(
//        "INSERT INTO `event_groups` (`id`,`name`,`title`) "
//        "VALUES (1,'climate_device', 'Климатическая установка');");
//    queryStringList.append(
//        "INSERT INTO `event_groups` (`id`,`name`,`title`) "
//        "VALUES (2,'electrical_equipment', 'Электрооборудование');");
//    queryStringList.append(
//        "INSERT INTO `event_groups` (`id`,`name`,`title`) "
//        "VALUES (3,'electrical_equipment_operating_time', 'Наработка электрооборудования');");


//    "`group_id` INTEGER NOT NULL "
//    "REFERENCES `groups` (`id`) "
//    "ON DELETE CASCADE "
//    "ON UPDATE CASCADE "
//    "MATCH [FULL], "

    //--------------------------------------
    queryStringList.append(
        "CREATE TABLE IF NOT EXISTS `event_types` ( "
        "`id` INTEGER NOT NULL PRIMARY KEY , "
//        "`group_id` INTEGER NOT NULL "
//        "REFERENCES `event_groups` (`id`) "
//        "ON DELETE CASCADE "
//        "ON UPDATE CASCADE "
//        "MATCH [FULL], "
        "`name` TEXT NOT NULL, "
        "`title` TEXT NOT NULL "
        "); "
        );

    queryStringList.append(
        "INSERT INTO `event_types` (`id`,`name`,`title`) "
        "VALUES (1,'start_system', 'Включение');");

    //--------------------------------------
    queryStringList.append(
        "CREATE TABLE IF NOT EXISTS `events` ( "
        "`id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
        "`datetime` INTEGER NOT NULL, "
        "`event_group_id` INTEGER NOT NULL "
        "REFERENCES `event_groups` (`id`) "
        "ON DELETE CASCADE "
        "ON UPDATE CASCADE "
        "MATCH [FULL], "
        //--------------------------------------
        "`event_type_id` INTEGER NOT NULL "
        "REFERENCES `event_types` (`id`) "
        "ON DELETE CASCADE "
        "ON UPDATE CASCADE "
        "MATCH [FULL] "
        //",`text` TEXT NOT NULL "
        //--------------------------------------
        "); "
        );
*/

    createArchiveTable("electrical_equipment_events", queryStringList);
    createArchiveTable("climate_device_auto_events", queryStringList);
    createArchiveTable("climate_device_manual_events", queryStringList);
    createArchiveTable("work_time_events", queryStringList);
//    createArchiveTable(", queryStringList");
//    createArchiveTable(", queryStringList");
//    createArchiveTable(", queryStringList");
//    createArchiveTable(", queryStringList");

}
//------------------------------------------------------------------------------------
//!
void DbUnit::createArchiveTable(const QString &tableName,
                                QStringList &queryStringList)
{
    queryStringList.append(QString(
        "CREATE TABLE IF NOT EXISTS `%1` ( "
        "`id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
        "`datetime` INTEGER NOT NULL, "
        "`msg` TEXT NOT NULL "
        "); "
        ).arg(tableName));

    //--------------------------------------
/*
    const int testDataCount = 40;

    for(int i = 0; i < testDataCount; ++i)
    {
        queryStringList.append( QString(
            "INSERT INTO `%1` (`datetime`,`msg`) "
            "VALUES (%2,'Тестовое сообщение (%1) [%3]');"
            ).arg(tableName).arg(QDateTime::currentMSecsSinceEpoch()+i*1000).arg(i)
        );
    }
*/
    //--------------------------------------
}
//------------------------------------------------------------------------------------
//!
void DbUnit::clearDb()
{
    QStringList tableList({
        "climate_device_auto_events",
        "climate_device_manual_events",
        "electrical_equipment_events",
        //"electrical_equipment_operating_time",
        "work_time_events"
        });

    QStringList queryStringList;

    for (int i = 0; i < tableList.size(); ++i)
    {
        QString tableName = tableList.at(i);

        queryStringList.append( QString(
            "DELETE FROM `%1` "
            "WHERE `datetime`< "
            "(SELECT datetime "
            "FROM `%1` "
            "ORDER BY `datetime` DESC "
            "LIMIT 1 OFFSET 50 ) "
            ";"
            ).arg(tableName) );
    }

    exequteQueryList(queryStringList);
}










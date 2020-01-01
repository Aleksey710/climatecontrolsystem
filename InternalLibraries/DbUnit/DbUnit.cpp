#include "DbUnit.h"
//------------------------------------------------------------------------------------
//!
DbUnit::DbUnit(const QString &dbFileAddress,
               QObject *parent)
       :QObject(parent),
        m_dbFileAddress ( dbFileAddress )
{
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
}
//------------------------------------------------------------------------------------
//!
DbUnit::~DbUnit()
{
    SEND_TO_LOG(QString("%1 - удален").arg(objectName()));
}
//------------------------------------------------------------------------------------
//!
void DbUnit::openDb()
{
    QSqlDatabase::database(m_dbFileAddress, false).close();
    QSqlDatabase::removeDatabase(m_dbFileAddress);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(m_dbFileAddress);

    // Additionally, name can be set to ":memory:" which will create a temporary database
    // which is only available for the lifetime of the application.
    //db.setDatabaseName(":memory:");

    if (!db.open())
    {
        QSqlError err = db.lastError();

        SEND_TO_LOG(QString("%1 - ошибка открытия базы [%2]").arg(objectName()).arg(err.text()));

        db = QSqlDatabase();
        QSqlDatabase::removeDatabase(m_dbFileAddress);
    } else
    {
        SEND_TO_LOG(QString("%1 - база подключена").arg(objectName()));
    }
}
//------------------------------------------------------------------------------------
//!
QList<MenuItemData> DbUnit::menuItemDataList()
{
    QList<MenuItemData> menuItemDataList;

    QSqlDatabase db(QSqlDatabase::database(m_dbFileAddress));

    QSqlQuery query("SELECT `name`,`title` FROM `groups`;", db);

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
    QSqlDatabase db(QSqlDatabase::database(m_dbFileAddress));

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
    QSqlDatabase db(QSqlDatabase::database(m_dbFileAddress));

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
    SEND_TO_LOG(QString("%1 - создание структуры базы").arg(objectName()));

    QStringList queryStringList;

    queryStringList.append(
        "CREATE TABLE IF NOT EXISTS `groups` ( "
        "`id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
        "`name` TEXT NOT NULL, "
        "`title`	TEXT NOT NULL "
        "); "
        );

    queryStringList.append(
        "CREATE TABLE IF NOT EXISTS `data_model` ( "
        "`id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
        "`group_id` INTEGER NOT NULL, "
        "`name` TEXT NOT NULL, "
        "`title`	TEXT NOT NULL, "
        "`value`	REAL NOT NULL "
        "); "
        );

    //------------------------------------------------------------------------------------
//    queryStringList.append("INSERT INTO `groups` (`name`,`title`) VALUES ('log',        'Налаштування відображення сторінок логів');");
//    queryStringList.append("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
//               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='log'),     'show', 'подивитись доступні сторінки логів та їх ідентефікатори');");
    //------------------------------------------------------------------------------------
    createGroups(queryStringList);

    exequteQueryList(queryStringList);
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createGroups(QStringList &queryStringList)
{
    queryStringList.append("INSERT INTO `groups` (`name`,`title`) VALUES ('offset',     'Корекція дельт для аналогових входів');");
    createOffsetGroup(queryStringList);

    queryStringList.append("INSERT INTO `groups` (`name`,`title`) VALUES ('temp',       'Налаштування для температур');");
    createTempGroup(queryStringList);

    queryStringList.append("INSERT INTO `groups` (`name`,`title`) VALUES ('bat',        'Налаштування для батареї');");
    createBatGroup(queryStringList);

    queryStringList.append("INSERT INTO `groups` (`name`,`title`) VALUES ('lim',        'Ліміти які відображаються на головній сторінці');");
    createLimGroup(queryStringList);

    queryStringList.append("INSERT INTO `groups` (`name`,`title`) VALUES ('gen',        'Налаштування для генератора');");
    createGenGroup(queryStringList);

    queryStringList.append("INSERT INTO `groups` (`name`,`title`) VALUES ('volt',       'Налаштування для бортовий мережі');");
    createVoltGroup(queryStringList);

    queryStringList.append("INSERT INTO `groups` (`name`,`title`) VALUES ('avg',        'Затримки накопичення');");
    createAvgGroup(queryStringList);

    queryStringList.append("INSERT INTO `groups` (`name`,`title`) VALUES ('delay',      'Налаштування затримок НВО та ВВО');");
    createDelayGroup(queryStringList);

    queryStringList.append("INSERT INTO `groups` (`name`,`title`) VALUES ('wagon',      'Налаштування параметрів вагону');");
    createWagonGroup(queryStringList);

    queryStringList.append("INSERT INTO `groups` (`name`,`title`) VALUES ('password',   'Зміна пароля');");
    createPasswordGroup(queryStringList);

    queryStringList.append("INSERT INTO `groups` (`name`,`title`) VALUES ('screen',     'Налаштування параметрів экрану');");
    createScreenGroup(queryStringList);

    queryStringList.append("INSERT INTO `groups` (`name`,`title`) VALUES ('cond',       'Налаштування кондиціонера');");
    createCondGroup(queryStringList);

    queryStringList.append("INSERT INTO `groups` (`name`,`title`) VALUES ('resist',     'Аварія при порушенні ізоляції');");
    createResistGroup(queryStringList);

    //queryStringList.append("INSERT INTO `groups` (`name`,`title`) VALUES ('',   '');");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createOffsetGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'tc', 'Корекція дельт для температури купе', 1.0);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'af', 'Корекція дельт для припливної вентиляції', 0.3);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'to', 'Корекція дельт для температури зовнішнього повітря', 0.8);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'tb', 'Корекція дельт для температури котла', 2.7);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'cb', 'Корекція дельт для струму батареї', 0.0);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'cg', 'Корекція дельт для струму генератора', 0.0);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'nv', 'Корекція дельт для напруги мережі', 1.2);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'cmc', 'Коефіцієнт нахилу(матеріалу) для температури купе', 1.0417);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'cmf', 'Коефіцієнт нахилу(матеріалу) для припливної вентиляції', 1.0417);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'cmo', 'Коефіцієнт нахилу(матеріалу) для температури зовнішнього повітря', 1.0417);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'cmb', 'Коефіцієнт нахилу(матеріалу) для температури котла', 1.0417);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'cmi', 'Коефіцієнт нахилу(матеріалу) для струму батареї', 1.0);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'cmg', 'Коефіцієнт нахилу(матеріалу) для струму генератора', 1.0);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'cmv', 'Коефіцієнт нахилу(матеріалу) для напруги мережі', 1.0);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'), "
        "'oc', 'Дільник для значень АЦП', 10);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createTempGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'sev', 'Значення при якому з\`являеться повідомлення про обрив датчика', 1000);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'bt', 'Максимальна температура котла, °C', 90);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'ibt', 'Iнтервал перевищення максимальної температури котла, мСек', 10000);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'tpo', 'Зовнішня температура необхідна для включення насоса, °C', -10);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'onnvo', 'Зовнішня температура необхідна для включення НВО, °C', 15);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'onlvhd', 'Гістерезис температури для включення НВО, °C', 2);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'offlvhd', 'Гістерезис температури для виключення НВО, °C', 1);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'offnvo', 'зовнішня температура необхідна для виключення НВО, °C', 15);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'vvohefon', 'Гістерезис для температури уставки для включення ВВО', 2);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'vvohefoff', 'Гістерезис для температури уставки для відключення ВВО', 1);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'vvootfdon', 'зовнішня температура необхідна для ввімкненя другої групи ВВО', -10);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'vvootfdoff', 'Зовнішня температура необхідна для вимкненя другої групи ВВО', -8);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'vvohoton', 'Зовнішня температура необхідна для ввімкненяя ВВО', 5);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'vvohotoff', 'Зовнішня температура необхідна для вимкненя ВВО', 6);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'x0', 'T(вкл) = x0 + x2 * (T(уст)-x3) - x4 * Т(нв) + x5 * (T(уст) - T(сал))', 35);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'x1', 'T(викл) = x1 + x2 * (T(уст)-x3) - x4 * Т(нв) + x5 * (T(уст) - T(сал))', 55);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'x2', 'T(вкл/викл) = x1 + x2 * (T(уст)-x3) - x4 * Т(нв) + x5 * (T(уст) - T(сал))', 2.5);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'x3', 'T(вкл/викл) = x1 + x2 * (T(уст)-x3) - x4 * Т(нв) + x5 * (T(уст) - T(сал))', 22);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'x4', 'T(вкл/викл) = x1 + x2 * (T(уст)-x3) - x4 * Т(нв) + x5 * (T(уст) - T(сал))', 1.5);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'x5', 'T(вкл/викл) = x1 + x2 * (T(уст)-x3) - x4 * Т(нв) + x5 * (T(уст) - T(сал))', 8);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
        "'sut', 'Температура уставки, °C', 24);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createBatGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='bat'), "
        "'mcb', 'Максимальний струм батареї, А', 100);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='bat'), "
        "'imcb', 'Iнтервал перевищення струму батареї, мСек', 60000);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createLimGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'micb', 'Мінімум струм батареї', -150);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'macb', 'Максимум струм батареї', 160);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'micg', 'Мінімум струм генератора', 0);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'macg', 'Максимум струм генератора', 250);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'mivn', 'Мінімум напруга бортової мережі', 0);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'mavn', 'Максимум напруга бортової мережі', 200);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'mitb', 'Мінімум температура котла', 0);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'matb', 'Максимум температура котла', 110);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'mito', 'Мінімум температура ззовні', -40);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'mato', 'Максимум температура ззовні', 60);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'miti', 'Мінімум температура салону', -20);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'mati', 'Максимум температура салону', 60);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'mitaf', 'Мінімум температура припливної вентиляції', -40);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
        "'mataf', 'Максимум температура припливної вентиляції', 100);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createGenGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='gen'), "
        "'mcg', 'Максимальний струм генератора, А', 235);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='gen'), "
        "'imcg', 'Iнтервал перевищення струму генератора, мСек', 2000);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createVoltGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='volt'), "
        "'mabn', 'Максимальна напруга бортової  мережі, V', 150);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='volt'), "
        "'maibn', 'Iнтервал перевищення напруги бортової мережі, мСек', 2000);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='volt'), "
        "'mibn', 'Мінімальна напруга бортової мережі, V', 70);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='volt'), "
        "'miibn', 'Iнтервал заниження напруги бортової мережі, мСек', 10000);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createAvgGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='avg'), "
        "'coupe', 'Температура салону', 10);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='avg'), "
        "'airflow', 'Температура припливної вентиляції', 10);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='avg'), "
        "'out', 'Температура ззовні', 10);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='avg'), "
        "'boiler', 'Температура котла', 10);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='avg'), "
        "'bat', 'Струм батареї', 5);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='avg'), "
        "'gen', 'Струм генератора', 5);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='avg'), "
        "'volt', 'Напруга мережі', 5);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createDelayGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='delay'), "
        "'vvodsd', 'Час простою перед наступним включенням ВВО, мСек', 5000);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='delay'), "
        "'vvosod', 'Затримка включення ВВО, мСек', 5000);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='delay'), "
        "'vvord', 'Затримка відповіді включення ВВО від БВВ, мСек', 5000);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='delay'), "
        "'dlhon', 'Затримка включення НВО, мСек', 5000);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='delay'), "
        "'dlhoff', 'Затримка виключення НВО, мСек', 5000);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='delay'), "
        "'dlhr', 'Затримка відповіді включення НВО від БВВ, мСек', 5000);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='delay'), "
        "'dlh', 'Затримка повторного включення НВО, мСек', 15000);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createWagonGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='wagon'), "
        "'dd', 'дата установки ПЗ, формат \"рррр-мм-дд\"', '2020-01-01');");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='wagon'), "
        "'sv', 'версія ПЗ', '2.3.11');");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='wagon'), "
        "'num', 'номер вагона', '040-14551');");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createPasswordGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='password'), "
        "'new', 'Зміна пароля', 1234);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createScreenGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='screen'), "
        "'opt', 'Увімкнення режиму збереження екрану(true(1) або false(0))', 1);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='screen'), "
        "'min', 'Мінімальна яркість(від 0 до 7)', 4);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='screen'), "
        "'max', 'Максимальна яркість(від 0 до 7)', 6);");
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='screen'), "
        "'delay', 'Затримка(мс)', 120000);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createCondGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='cond'), "
        "'ccm', 'Вкл/Вимк спільної роботи НВО та Ел. Калоріфер (Нагрів), true(1) або false(0)', 0);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createResistGroup(QStringList &queryStringList)
{
    queryStringList.append(
        "INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
        "VALUES ((SELECT `id` FROM `groups` WHERE `name`='resist'), "
        "'val', 'Аварія при порушенні ізоляції true(1) або false(0)', 1);");
}



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

    openDb();

    createDb();

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
void DbUnit::createDb()
{
    SEND_TO_LOG(QString("%1 - создание структуры базы").arg(objectName()));

    QSqlDatabase db(QSqlDatabase::database(m_dbFileAddress));

    QSqlQuery query(db);

    query.exec("CREATE TABLE `groups` ( "
               "`id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
               "`name` TEXT NOT NULL, "
               "`title`	TEXT NOT NULL "
               "); "
               );

    query.exec("CREATE TABLE `data_model` ( "
               "`id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
               "`group_id` INTEGER NOT NULL, "
               "`name` TEXT NOT NULL, "
               "`title`	TEXT NOT NULL, "
               "`value`	REAL NOT NULL "
               "); "
               );

    //------------------------------------------------------------------------------------
//    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('log',        'Налаштування відображення сторінок логів');");
//    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
//               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='log'),     'show', 'подивитись доступні сторінки логів та їх ідентефікатори');");
    //------------------------------------------------------------------------------------
    createGroups(query);
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createGroups(QSqlQuery &query)
{
    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('offset',     'Корекція дельт для аналогових входів');");
    createOffsetGroup(query);

    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('temp',       'Налаштування для температур');");
    createTempGroup(query);

    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('bat',        'Налаштування для батареї');");
    createBatGroup(query);

    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('lim',        'Ліміти які відображаються на головній сторінці');");
    createLimGroup(query);

    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('gen',        'Налаштування для генератора');");
    createGenGroup(query);

    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('volt',       'Налаштування для бортовий мережі');");
    createVoltGroup(query);

    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('avg',        'Затримки накопичення');");
    createAvgGroup(query);

    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('delay',      'Налаштування затримок НВО та ВВО');");
    createDelayGroup(query);

    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('wagon',      'Налаштування параметрів вагону');");
    createWagonGroup(query);

    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('password',   'Зміна пароля');");
    createPasswordGroup(query);

    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('screen',     'Налаштування параметрів экрану');");
    createScreenGroup(query);

    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('cond',       'Налаштування кондиціонера');");
    createCondGroup(query);

    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('resist',     'Аварія при порушенні ізоляції');");
    createResistGroup(query);

    //query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('',   '');");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createOffsetGroup(QSqlQuery &query)
{
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'),  'tc', "
               "'Корекція дельт для температури купе', 1.0);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'),  'af', "
               "'Корекція дельт для припливної вентиляції', 0.3);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'),  'to', "
               "'Корекція дельт для температури зовнішнього повітря', 0.8);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'),  'tb', "
               "'Корекція дельт для температури котла', 2.7);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'),  'cb', "
               "'Корекція дельт для струму батареї', 0.0);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'),  'cg', "
               "'Корекція дельт для струму генератора', 0.0);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'),  'nv', "
               "'Корекція дельт для напруги мережі', 1.2);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'),  'cmc', "
               "'Коефіцієнт нахилу(матеріалу) для температури купе', 1.0417);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'),  'cmf', "
               "'Коефіцієнт нахилу(матеріалу) для припливної вентиляції', 1.0417);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'),  'cmo', "
               "'Коефіцієнт нахилу(матеріалу) для температури зовнішнього повітря', 1.0417);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'),  'cmb', "
               "'Коефіцієнт нахилу(матеріалу) для температури котла', 1.0417);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'),  'cmi', "
               "'Коефіцієнт нахилу(матеріалу) для струму батареї', 1.0);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'),  'cmg', "
               "'Коефіцієнт нахилу(матеріалу) для струму генератора', 1.0);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'),  'cmv', "
               "'Коефіцієнт нахилу(матеріалу) для напруги мережі', 1.0);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='offset'),  'oc', "
               "'Дільник для значень АЦП', 10);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createTempGroup(QSqlQuery &query)
{
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
               "'sev', 'Значення при якому з'являеться повідомлення про обрив датчика', 1000);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
               "'bt', 'Максимальна температура котла, °C', 90);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
               "'ibt', 'Iнтервал перевищення максимальної температури котла, мСек', 10000);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
               "'tpo', 'Зовнішня температура необхідна для включення насоса, °C', -10);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
               "'onnvo', 'Зовнішня температура необхідна для включення НВО, °C', 15);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
               "'onlvhd', 'Гістерезис температури для включення НВО, °C', 2);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
               "'offlvhd', 'Гістерезис температури для виключення НВО, °C', 1);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
               "'offnvo', 'зовнішня температура необхідна для виключення НВО, °C', 15);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
               "'vvohefon', 'Гістерезис для температури уставки для включення ВВО', 2);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
               "'vvohefoff', 'Гістерезис для температури уставки для відключення ВВО', 1);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
               "'vvootfdon', 'зовнішня температура необхідна для ввімкненя другої групи ВВО', -10);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
               "'vvootfdoff', 'Зовнішня температура необхідна для вимкненя другої групи ВВО', -8);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
               "'vvohoton', 'Зовнішня температура необхідна для ввімкненяя ВВО', 5);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
               "'vvohotoff', 'Зовнішня температура необхідна для вимкненя ВВО', 6);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
               "'x0', 'T(вкл) = x0 + x2 * (T(уст)-x3) - x4 * Т(нв) + x5 * (T(уст) - T(сал))', 35);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
               "'x1', 'T(викл) = x1 + x2 * (T(уст)-x3) - x4 * Т(нв) + x5 * (T(уст) - T(сал))', 55);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
               "'x2', 'T(вкл/викл) = x1 + x2 * (T(уст)-x3) - x4 * Т(нв) + x5 * (T(уст) - T(сал))', 2.5);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
               "'x3', 'T(вкл/викл) = x1 + x2 * (T(уст)-x3) - x4 * Т(нв) + x5 * (T(уст) - T(сал))', 22);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
               "'x4', 'T(вкл/викл) = x1 + x2 * (T(уст)-x3) - x4 * Т(нв) + x5 * (T(уст) - T(сал))', 1.5);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
               "'x5', 'T(вкл/викл) = x1 + x2 * (T(уст)-x3) - x4 * Т(нв) + x5 * (T(уст) - T(сал))', 8);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='temp'), "
               "'sut', 'Температура уставки, °C', 24);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createBatGroup(QSqlQuery &query)
{
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='bat'), "
               "'mcb', 'Максимальний струм батареї, А', 100);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='bat'), "
               "'imcb', 'Iнтервал перевищення струму батареї, мСек', 60000);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createLimGroup(QSqlQuery &query)
{
//    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
//               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='lim'), "
//               "'', '', );");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createGenGroup(QSqlQuery &query)
{
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='gen'), "
               "'mcg', 'Максимальний струм генератора, А', 235);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='gen'), "
               "'imcg', 'Iнтервал перевищення струму генератора, мСек', 2000);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createVoltGroup(QSqlQuery &query)
{
//    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
//               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='volt'), "
//               "'', '', );");
//    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
//               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='volt'), "
//               "'', '', );");
//    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
//               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='volt'), "
//               "'', '', );");
//    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
//               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='volt'), "
//               "'', '', );");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createAvgGroup(QSqlQuery &query)
{
//    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
//               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='avg'), "
//               "'', '', );");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createDelayGroup(QSqlQuery &query)
{
//    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
//               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='delay'), "
//               "'', '', );");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createWagonGroup(QSqlQuery &query)
{
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='wagon'), "
               "'dd', 'дата установки ПЗ, формат \'рррр-мм-дд\'', 2020-01-01);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='wagon'), "
               "'sv', 'версія ПЗ', '2.3.11');");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='wagon'), "
               "'num', 'номер вагона', '040-14551');");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createPasswordGroup(QSqlQuery &query)
{
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='password'), "
               "'new', 'Зміна пароля', 1234);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createScreenGroup(QSqlQuery &query)
{
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='screen'), "
               "'opt', 'Увімкнення режиму збереження екрану(true(1) або false(0))', 1);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='screen'), "
               "'min', 'Мінімальна яркість(від 0 до 7)', 4);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='screen'), "
               "'max', 'Максимальна яркість(від 0 до 7)', 6);");
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='screen'), "
               "'delay', 'Затримка(мс)', 120000);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createCondGroup(QSqlQuery &query)
{
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='cond'), "
               "'ccm', 'Вкл/Вимк спільної роботи НВО та Ел. Калоріфер (Нагрів), true(1) або false(0)', 0);");
}
//------------------------------------------------------------------------------------
//!
void DbUnit::createResistGroup(QSqlQuery &query)
{
    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='resist'), "
               "'val', 'Аварія при порушенні ізоляції true(1) або false(0)', 1);");
}



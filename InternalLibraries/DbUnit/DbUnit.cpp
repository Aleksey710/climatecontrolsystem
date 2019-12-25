#include "DbUnit.h"
//------------------------------------------------------------------------------------
//!
DbUnit::DbUnit(QObject *parent)
       :QObject(parent),
        m_dbFileAddress ( "./conf/db.sqlite" )
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
    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('log',        'Налаштування відображення сторінок логів');");
//    query.exec("INSERT INTO `data_model` (`group_id`,`name`,`title`,`value`) "
//               "VALUES ((SELECT `id` FROM `groups` WHERE `name`='log'),     'show', 'подивитись доступні сторінки логів та їх ідентефікатори');");
    //------------------------------------------------------------------------------------
    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('offset',     'Корекція дельт для аналогових входів');");

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

    //------------------------------------------------------------------------------------
    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('temp',       'Налаштування для температур');");
    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('bat',        'Налаштування для батареї');");
    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('lim',        'Ліміти які відображаються на головній сторінці');");
    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('gen',        'Налаштування для генератора');");
    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('volt',       'Налаштування для бортовий мережі');");
    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('avg',        'Затримки накопичення');");
    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('delay',      'Налаштування затримок НВО та ВВО');");
    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('wagon',      'Налаштування параметрів вагону');");
    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('password',   'Зміна пароля');");
    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('screen',     'Налаштування параметрів экрану');");
    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('cond',       'Налаштування кондиціонера');");
    query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('resist',     'Аварія при порушенні ізоляції');");
    //query.exec("INSERT INTO `groups` (`name`,`title`) VALUES ('',   '');");



}
//------------------------------------------------------------------------------------
//!
void DbUnit::addConnection()
{
//    QSqlConnectionDialog dialog(this);
//    if (dialog.exec() != QDialog::Accepted)
//        return;

//    if (dialog.useInMemoryDatabase())
//    {
        QSqlDatabase::database("in_mem_db", false).close();
        QSqlDatabase::removeDatabase("in_mem_db");
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "in_mem_db");
        db.setDatabaseName(":memory:");

//        if (!db.open())
//            QMessageBox::warning(this, tr("Unable to open database"), tr("An error occurred while "
//                                                                         "opening the connection: ") + db.lastError().text());

        QSqlQuery q("", db);
        q.exec("drop table Movies");
        q.exec("drop table Names");
        q.exec("create table Movies (id integer primary key, Title varchar, Director varchar, Rating number)");
        q.exec("insert into Movies values (0, 'Metropolis', 'Fritz Lang', '8.4')");
        q.exec("insert into Movies values (1, 'Nosferatu, eine Symphonie des Grauens', 'F.W. Murnau', '8.1')");
        q.exec("insert into Movies values (2, 'Bis ans Ende der Welt', 'Wim Wenders', '6.5')");
        q.exec("insert into Movies values (3, 'Hardware', 'Richard Stanley', '5.2')");
        q.exec("insert into Movies values (4, 'Mitchell', 'Andrew V. McLaglen', '2.1')");
        q.exec("create table Names (id integer primary key, Firstname varchar, Lastname varchar, City varchar)");
        q.exec("insert into Names values (0, 'Sala', 'Palmer', 'Morristown')");
        q.exec("insert into Names values (1, 'Christopher', 'Walker', 'Morristown')");
        q.exec("insert into Names values (2, 'Donald', 'Duck', 'Andeby')");
        q.exec("insert into Names values (3, 'Buck', 'Rogers', 'Paris')");
        q.exec("insert into Names values (4, 'Sherlock', 'Holmes', 'London')");
        //connectionWidget->refresh();
//    } else {

//        QSqlError err = addConnection(dialog.driverName(),
//                                      dialog.databaseName(),
//                                      dialog.hostName(),
//                                      dialog.userName(),
//                                      dialog.password(),
//                                      dialog.port());

//        if (err.type() != QSqlError::NoError)
//            QMessageBox::warning(this,
//                                 tr("Unable to open database"),
//                                 tr("An error occurred while "
//                                    "opening the connection: ") + err.text());
//    }
}

#include "DbUnit.h"
//------------------------------------------------------------------------------------
//!
DbUnit::DbUnit(QObject *parent)
       :QObject(parent)
{

}
//------------------------------------------------------------------------------------
//!
DbUnit::~DbUnit()
{

}
//------------------------------------------------------------------------------------
//!
QSqlError DbUnit::createConnection(const QString &driver,
                                   const QString &dbName,
                                   const QString &host,
                                   const QString &user,
                                   const QString &passwd,
                                   int port)
{
    QSqlError err;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", QString("./conf/db.sqlite"));
    db.setDatabaseName(dbName);
    db.setHostName(host);
    db.setPort(port);

    if (!db.open(user, passwd))
    {
        err = db.lastError();
        db = QSqlDatabase();
        QSqlDatabase::removeDatabase(QString("./conf/db.sqlite"));
    }


    return err;
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

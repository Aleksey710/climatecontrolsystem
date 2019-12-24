#ifndef DBUNIT_H
#define DBUNIT_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
//#include <>
//#include <>
//#include <>
//#include <>
//#include <>


#include "Log.h"
//#include ""
//#include ""
//#include ""
//------------------------------------------------------------------------------------
//!
class DbUnit : public QObject
{
        Q_OBJECT
    public:
        explicit DbUnit(QObject *parent = nullptr);
        virtual ~DbUnit();

        QSqlError createConnection(const QString &driver,
                                   const QString &dbName,
                                   const QString &host,
                                   const QString &user,
                                   const QString &passwd,
                                   int port);

        void addConnection();

    signals:

};
//------------------------------------------------------------------------------------
#endif // DBUNIT_H

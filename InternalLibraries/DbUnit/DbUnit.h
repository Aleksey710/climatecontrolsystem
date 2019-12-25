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


        void addConnection();

        void openDb();
        void createDb();

    signals:


    private:
        QString m_dbFileAddress;
};
//------------------------------------------------------------------------------------
#endif // DBUNIT_H

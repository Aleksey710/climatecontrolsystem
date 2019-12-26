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
        explicit DbUnit(const QString &dbFileAddress =
                            QString ( qApp->applicationDirPath()+"/conf/db.sqlite" ),
                        QObject *parent = nullptr);
        virtual ~DbUnit();

        inline QString dbName()
            { return m_dbFileAddress; }

        void openDb();
        void createDb();

    signals:


    private:
        void createGroups(QSqlQuery &query);
        void createOffsetGroup(QSqlQuery &query);
        void createTempGroup(QSqlQuery &query);
        void createBatGroup(QSqlQuery &query);
        void createLimGroup(QSqlQuery &query);
        void createGenGroup(QSqlQuery &query);
        void createVoltGroup(QSqlQuery &query);
        void createAvgGroup(QSqlQuery &query);
        void createDelayGroup(QSqlQuery &query);
        void createWagonGroup(QSqlQuery &query);
        void createPasswordGroup(QSqlQuery &query);
        void createScreenGroup(QSqlQuery &query);
        void createCondGroup(QSqlQuery &query);
        void createResistGroup(QSqlQuery &query);

    private:
        QString m_dbFileAddress;
};
//------------------------------------------------------------------------------------
#endif // DBUNIT_H

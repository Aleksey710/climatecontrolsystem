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
#include "MenuItemData.h"
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

        QList<MenuItemData> menuItemDataList();


    signals:


    private:
        void exequteQuery(const QString &query);
        void exequteQueryList(const QStringList &queryStringList);

        void createGroups(QStringList &queryStringList);
        void createOffsetGroup(QStringList &queryStringList);
        void createTempGroup(QStringList &queryStringList);
        void createBatGroup(QStringList &queryStringList);
        void createLimGroup(QStringList &queryStringList);
        void createGenGroup(QStringList &queryStringList);
        void createVoltGroup(QStringList &queryStringList);
        void createAvgGroup(QStringList &queryStringList);
        void createDelayGroup(QStringList &queryStringList);
        void createWagonGroup(QStringList &queryStringList);
        void createPasswordGroup(QStringList &queryStringList);
        void createScreenGroup(QStringList &queryStringList);
        void createCondGroup(QStringList &queryStringList);
        void createResistGroup(QStringList &queryStringList);

    private:
        QString m_dbFileAddress;
};
//------------------------------------------------------------------------------------
#endif // DBUNIT_H

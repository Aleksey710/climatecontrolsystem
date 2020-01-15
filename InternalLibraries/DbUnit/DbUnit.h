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
        static QString m_dbFileAddress;

    public:
        explicit DbUnit(QObject *parent = nullptr);
        virtual ~DbUnit();

        inline static QString dbName()
            { return m_dbFileAddress; }

        QList<MenuItemData> settingsMenuItemList();


    signals:


    private:
        void openDb();
        void createDb();

        void exequteQuery(const QString &query);
        void exequteQueryList(const QStringList &queryStringList);

        //------------------------------------------------------
        void setupSettings(QStringList &queryStringList);

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

        //------------------------------------------------------
        void setupArchiveEvents(QStringList &queryStringList);

        void createArchiveTable(const QString &tableName,
                                QStringList &queryStringList);


    private:
};
//------------------------------------------------------------------------------------
#endif // DBUNIT_H

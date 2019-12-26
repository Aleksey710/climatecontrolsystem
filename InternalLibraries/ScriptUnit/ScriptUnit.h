#ifndef SCRIPTUNIT_H
#define SCRIPTUNIT_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QString>
//#include <QSqlDatabase>
//#include <QSqlError>
//#include <QSqlQuery>
//#include <>
//#include <>
//#include <>
//#include <>
//#include <>


#include "Log.h"
#include "ScriptEngine.h"
//#include ""
//#include ""
//#include ""
//------------------------------------------------------------------------------------
//!
class ScriptUnit : public QObject
{
        Q_OBJECT
    public:
        explicit ScriptUnit(QObject *parent = nullptr);

    signals:

    public:
        static ScriptEngine *m_scriptEngine;

};
//------------------------------------------------------------------------------------
#endif // SCRIPTUNIT_H

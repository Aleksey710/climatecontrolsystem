#ifndef SCRIPTOBJECT_H
#define SCRIPTOBJECT_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QVariant>
#include <QList>
#include <QScriptable>
//#include <>
//#include <>

//#include ""
//#include ""
//------------------------------------------------------------------------------------
class ScriptObject;
//------------------------------------------------------------------------------------
// Для наследников QObject декларировать и использовать только указатель
Q_DECLARE_METATYPE(ScriptObject*);
//------------------------------------------------------------------------------------
//!
class ScriptObject : public QObject, protected QScriptable
{
        Q_OBJECT
    public:
        inline explicit ScriptObject(const QString &name,
                                     QObject *parent = Q_NULLPTR)
            : QObject(parent)
            { setObjectName(name); }

        inline virtual ~ScriptObject()
            { }

        Q_INVOKABLE inline void setData(const QVariant &value, int role = Qt::DisplayRole)
            { emit specificDataChanged(value, role); }

    signals:
        Q_INVOKABLE void specificDataChanged(const QVariant &value, int role);

    protected:


};
//------------------------------------------------------------------------------------
#endif // SCRIPTOBJECT_H

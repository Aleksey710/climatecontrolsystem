#ifndef SCRIPTOBJECT_H
#define SCRIPTOBJECT_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QVariant>
#include <QList>
#include <QScriptable>
#include <QTimer>
#include <QRandomGenerator>
//#include <>
//#include <>
//#include <>

#include "Log.h"
//#include ".h"
//#include ".h"

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
        explicit ScriptObject(const QString &name,
                              const double &value,
                              ScriptObject *parent = Q_NULLPTR);

        virtual ~ScriptObject();

        inline QString fullName() const
            { return m_fullName; }

        ScriptObject* getChildren(const QString &name);

        //--------------------------------------------------
        Q_INVOKABLE inline double data() const
            { return value; }

        Q_INVOKABLE inline void setData(const double &__value)
            {
                if(value != __value)
                {
                    value = __value;
                    dataChanged();
                }
            }

    signals:
        Q_INVOKABLE void dataChanged();

    protected:
        QString     m_fullName;

        double      value;

};
//------------------------------------------------------------------------------------
#endif // SCRIPTOBJECT_H

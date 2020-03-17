#ifndef SCRIPTOBJECT_H
#define SCRIPTOBJECT_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QVariant>
#include <QList>
#include <QScriptable>
#include <QTimer>

#include <cmath>
//#include <QRandomGenerator>
#include <QMutex>
#include <QMutexLocker>
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
                              const double &__value,
                              ScriptObject *parent = Q_NULLPTR);

        explicit ScriptObject(const QString &name,
                              const QString &__stringValue,
                              ScriptObject *parent = Q_NULLPTR);

        virtual ~ScriptObject();

        inline QString dataType() const
            { return m_dataType; }

        inline QString fullName() const
            { return m_fullName; }

        ScriptObject* getChildren(const QString &name);

        //--------------------------------------------------
        Q_INVOKABLE inline double data() const
            { return value; }

        Q_INVOKABLE inline QString stringData() const
            { return stringValue; }

        //--------------------------------------------------
        Q_INVOKABLE inline void setData(const double &__value)
            {
                QMutexLocker locker(&m_mutex);
                if( value != __value )
                //if( !approximatelyEqualAbsRel(value, __value) )
                //if( !qFuzzyCompare(value, __value) )
                {
                    SEND_TO_LOG( QString("ScriptObject[%1] - setData(%2)")
                                 .arg(m_fullName)
                                 .arg(__value) );

                    value = __value;
                    dataChanged();
                }
            }

        Q_INVOKABLE inline void setStringData(const QString &__stringValue)
            {
                if( stringValue != __stringValue )
                {
                    SEND_TO_LOG( QString("ScriptObject[%1] - setStringData(%2)").arg(m_fullName).arg(__stringValue))

                    stringValue = __stringValue;
                    dataChanged();
                }
            }
        //--------------------------------------------------

    signals:
        Q_INVOKABLE void dataChanged();

    protected:
        QString     m_fullName;

        QString     m_dataType;

        double      value;
        QString     stringValue;

    private:
        QMutex      m_mutex;

    private:
        // https://ravesli.com/urok-42-operatory-sravneniya/
        // Возвращаем true, если разница между a и b в пределах процента эпсилона
        inline bool approximatelyEqual(double a, double b, double epsilon = 10000000000)
        {
            return fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
        }

        // Возвращаем true, если разница между a и b меньше absEpsilon или в пределах relEpsilon
        inline bool approximatelyEqualAbsRel(double a, double b, double absEpsilon = 1e-12, double relEpsilon = 1e-12)
        {
            // Проверяем числа на их близость - это нужно в случаях, когда сравниваемые числа являются нулевыми или около нуля
            double diff = fabs(a - b);
            if (diff <= absEpsilon)
                return true;

            // В противном случае, возвращаемся к алгоритму Кнута
            return diff <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * relEpsilon);
        }
};
//------------------------------------------------------------------------------------
#endif // SCRIPTOBJECT_H

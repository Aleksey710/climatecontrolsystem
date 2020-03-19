#ifndef DATAAVERAGER_H
#define DATAAVERAGER_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QVector>
#include <QTimer>

/*
Сколько усреднять и что написано в настройках:
coupe 10 - температура салону
airflow 10 - температура припливної вентиляції
out 10 - температура ззовні
boiler 10 - температура котла
bat 5 - струм батареї
gen 5 - струм генератора
volt 5 - напруга мережі
Задержка в секундах, цикл раз в секунду значит кол-во секунд =  кол-во циклов. Усреднять
*/

#include "ScriptObject.h"
#include "ScriptUnit.h"

//------------------------------------------------------------------------------------
//! Усреднение скользящим окном
#define SLIDING_WINDOW
//------------------------------------------------------------------------------------
//!
class DataAverager : public QObject
{
        Q_OBJECT
    public:
        explicit DataAverager(const QString &dataScriptObjectName,
                              const QString &averageSizeScriptObjectName,
                              QObject *parent = nullptr);
        ~DataAverager();

    signals:
        void dataUpdate(const double value);


    private slots:
        void setData();


    private:
        int m_curentIndex;

        ScriptObject *m_dataScriptObject;

        QVector<double> m_valueArray;

        //! счетчик пришедших данных
        int m_dataCount;
};
//------------------------------------------------------------------------------------
#endif // DATAAVERAGER_H

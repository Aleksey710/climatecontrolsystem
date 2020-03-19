#ifndef DATAAVERAGER_H
#define DATAAVERAGER_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QVector>
#include <QTimer>

#include "ScriptObject.h"
#include "ScriptUnit.h"
//------------------------------------------------------------------------------------
//! Усреднение скользящим окном
//! (Если нет - закомментарить)
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

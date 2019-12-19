#ifndef DATAITEM_H
#define DATAITEM_H
//------------------------------------------------------------------------------------
//#include <>
#include <QString>
#include <QVariant>
#include <QObject>


#include "Log.h"
//#include ""
//#include ""
//------------------------------------------------------------------------------------
//!
class DataItem : public QObject
{
    Q_OBJECT
    public:
        explicit DataItem(const QString id,
                          QObject *parent = nullptr);

        virtual ~DataItem();

        inline double data()
            { return m_data; }

    public slots:
        inline void setData(const double &value)
            {
                if(m_data != value)
                {
                    m_data = value;
                    SEND_TO_LOG( QString("%1 setData(%2)").arg(objectName()).arg(m_data) );
                    emit dataChanged();
                }
            }

    signals:
        void dataChanged();

    private:
        const QString m_id;
        double m_data;

};
//------------------------------------------------------------------------------------
#endif // DATAITEM_H

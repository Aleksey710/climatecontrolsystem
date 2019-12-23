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
                          const QString title,
                          const QVariant value,
                          const QString dataType,
                          QObject *parent = nullptr);

        virtual ~DataItem();

        inline QVariant data()
            { return m_value; }

    public slots:
        inline void setData(const QVariant &value)
            {
                if(m_value != value)
                {
                    m_value = value;

                    SEND_TO_LOG( QString("%1 setData[%2]").arg(objectName()).arg(m_value.toString()) );

                    emit dataChanged();
                }
            }

    signals:
        void dataChanged();

    private:
        const QString m_id;
        const QString m_title;
        const QString m_dataType;
        QVariant m_value;

};
//------------------------------------------------------------------------------------
#endif // DATAITEM_H

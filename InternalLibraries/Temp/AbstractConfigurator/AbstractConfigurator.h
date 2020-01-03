#ifndef ABSTRACTCONFIGURATOR_H
#define ABSTRACTCONFIGURATOR_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
//#include <>
//#include <>


#include "Log.h"
//#include ""
//#include ""
//------------------------------------------------------------------------------------
//!
class AbstractConfigurator : public QObject
{
        Q_OBJECT
    public:
        explicit AbstractConfigurator(const QString &configuratorName,
                                      QObject *parent = nullptr);

        virtual ~AbstractConfigurator();



    signals:

    protected:
        QJsonObject loadFile(const QString &fileName);

        virtual void setup(const QJsonObject &jsonObject);


    protected:
        QString m_configuratorName;
};
//------------------------------------------------------------------------------------
#endif // ABSTRACTCONFIGURATOR_H

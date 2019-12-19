#ifndef MODBUSMASTERCONFIGURATOR_H
#define MODBUSMASTERCONFIGURATOR_H
//------------------------------------------------------------------------------------
//#include <>
//#include <>
//#include <>
//#include <QtCore/qglobal.h>
#include <QMultiHash>
#include <QHash>
#include <QList>
#include <QDateTime>


#include "Log.h"
#include "AbstractConfigurator.h"
//------------------------------------------------------------------------------------
//!
class ModbusMasterConfigurator : public AbstractConfigurator
{
    public:
        explicit ModbusMasterConfigurator(const QString &configuratorName,                                    
                                          QObject *parent);

        virtual ~ModbusMasterConfigurator();

    private:
        virtual void setup(const QJsonObject &jsonObject);

    private:


    private:


};
//------------------------------------------------------------------------------------
#endif // MODBUSMASTERCONFIGURATOR_H

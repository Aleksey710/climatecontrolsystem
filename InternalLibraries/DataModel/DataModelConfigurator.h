#ifndef DATAMODELCONFIGURATOR_H
#define DATAMODELCONFIGURATOR_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
//#include <>


#include "Log.h"
#include "DataModel.h"
#include "AbstractConfigurator.h"
//#include ""
//#include ""
//------------------------------------------------------------------------------------
//!
class DataModelConfigurator : public AbstractConfigurator
{
        Q_OBJECT
    public:
        explicit DataModelConfigurator(DataModel *dataModel,
                                       QObject *parent = nullptr);
        virtual ~DataModelConfigurator();



    signals:



    private:
        virtual void setup(const QJsonObject &jsonObject) override;

        void groupParsing(const QJsonObject &groupJsonObject);
        void itemParsing(const QJsonObject &itemJsonObject);

    private:
        DataModel *m_dataModel;

};
//------------------------------------------------------------------------------------
#endif // DATAMODELCONFIGURATOR_H

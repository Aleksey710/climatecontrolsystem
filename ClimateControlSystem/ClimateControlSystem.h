#ifndef CLIMATECONTROLSYSTEM_H
#define CLIMATECONTROLSYSTEM_H
//------------------------------------------------------------------------------------
//#include <>
//#include <>
//#include <>
#include <QString>
#include <QObject>



#include "Log.h"
#include "DataModel.h"
#include "DataModelConfigurator.h"
#include "ModbusMasterConfigurator.h"
#include "MainDisplayWidget.h"
#include "DbUnit.h"
//#include ".h"
//#include ".h"
//------------------------------------------------------------------------------------
//!
class ClimateControlSystem : public QObject
{
        Q_OBJECT
    public:
        explicit ClimateControlSystem(QObject *parent = nullptr);
        virtual ~ClimateControlSystem();

    signals:

    private:
        std::shared_ptr<DbUnit>     m_dbUnit    = std::make_shared<DbUnit>();
        std::shared_ptr<DataModel>  m_dataModel = std::make_shared<DataModel>();

        MainDisplayWidget   *m_mainDisplayWidget;

};
//------------------------------------------------------------------------------------
#endif // CLIMATECONTROLSYSTEM_H

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
//#include ""
//#include ""
//#include ""
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
        DataModel *m_dataModel;

};
//------------------------------------------------------------------------------------
#endif // CLIMATECONTROLSYSTEM_H
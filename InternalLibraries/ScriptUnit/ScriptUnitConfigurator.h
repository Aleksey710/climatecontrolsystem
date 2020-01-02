#ifndef SCRIPTUNITCONFIGURATOR_H
#define SCRIPTUNITCONFIGURATOR_H
//------------------------------------------------------------------------------------
#include <QObject>


//------------------------------------------------------------------------------------
//!
class ScriptUnitConfigurator : public QObject
{
        Q_OBJECT
    public:
        explicit ScriptUnitConfigurator(QObject *parent = nullptr);
        virtual ~ScriptUnitConfigurator();

    signals:

};
//------------------------------------------------------------------------------------
#endif // SCRIPTUNITCONFIGURATOR_H

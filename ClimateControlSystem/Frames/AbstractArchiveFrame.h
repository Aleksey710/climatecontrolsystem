#ifndef ABSTRACTARCHIVEFRAME_H
#define ABSTRACTARCHIVEFRAME_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QWidget>
#include <QTableView>
//#include <>
//#include <>


//#include ".h"
//#include ".h"
//#include ".h"
#include "Log.h"
#include "DbUnit.h"
#include "AbstractFrame.h"
#include "RemoveRecordsFromArchiveWidget.h"
//#include "FrameName.h"
//------------------------------------------------------------------------------------
//!
class AbstractArchiveFrame : public AbstractFrame
{
        Q_OBJECT
    public:
        explicit AbstractArchiveFrame(QWidget *parent = nullptr);
        virtual ~AbstractArchiveFrame();

        inline virtual FrameName frameName() { return FrameName::Archive; }

    signals:


    public slots:
        void pgUp();
        void pgDown();

        void startSaveData();
        void startRemoveData();

    protected:
        void setup();
        virtual QString headLabel() = 0; //{ return QString(); }
        virtual QString queryString() = 0; //{ return QString(); }


    private:
        QTableView *m_tableView;

        RemoveRecordsFromArchiveWidget *m_removeRecordsFromArchiveWidget;
};
//------------------------------------------------------------------------------------
#endif // ABSTRACTARCHIVEFRAME_H

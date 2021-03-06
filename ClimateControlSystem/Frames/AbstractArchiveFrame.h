#ifndef ABSTRACTARCHIVEFRAME_H
#define ABSTRACTARCHIVEFRAME_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QWidget>
#include <QTableView>
#include <QTableWidget>
#include <QSqlQueryModel>
#include <QFileSystemWatcher>

//#include <>
//#include <>


//#include ".h"
//#include ".h"
//#include ".h"
#include "Log.h"
#include "DbUnit.h"
#include "AbstractFrame.h"
#include "RemoveRecordsFromArchiveWidget.h"
#include "CheckPasswordWidget.h"
//------------------------------------------------------------------------------------
//!
class AbstractArchiveFrame : public AbstractFrame
{
        Q_OBJECT

    protected:
        static const int NUMBER_OF_LINES_ON_SCREEN = 18;

    public:
        explicit AbstractArchiveFrame(QWidget *parent = nullptr);
        virtual ~AbstractArchiveFrame();

        inline virtual FrameName frameName() { return FrameName::Archive; }

    signals:
        void updateModelData();


    public slots:
        virtual void pgUp();
        virtual void pgDown();

        void startSaveData();
        bool saveDataTo(const QString &fileName);
        void startRemoveData();

    protected:
        virtual void setup();
        virtual QString headLabel() = 0; //{ return QString(); }
        virtual QString queryString() = 0; //{ return QString(); }

        virtual void updateCountLabelData();

    private slots:


    protected:
        QLabel *m_countLabel;

        QSqlQueryModel *m_model;
        QTableView *m_tableView;
        QTableWidget *m_tableWidget;

        RemoveRecordsFromArchiveWidget *m_removeRecordsFromArchiveWidget;
};
//------------------------------------------------------------------------------------
#endif // ABSTRACTARCHIVEFRAME_H

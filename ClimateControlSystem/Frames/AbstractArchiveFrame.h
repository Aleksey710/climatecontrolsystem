#ifndef ABSTRACTARCHIVEFRAME_H
#define ABSTRACTARCHIVEFRAME_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QTableView>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QHeaderView>
#include <QSqlQuery>
#include <QLabel>
#include <QScrollBar>
#include <QShortcut>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QIODevice>
#include <QDataStream>
//#include <>
//#include <>
//#include <>


//#include ".h"
//#include ".h"
//#include ".h"
#include "Log.h"
#include "DbUnit.h"
#include "AbstractFrame.h"
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

    protected:
        void setup();
        virtual QString headLabel() { return QString(); }
        virtual QString queryString() { return QString(); }


    private:
        QTableView *m_tableView;
};
//------------------------------------------------------------------------------------
#endif // ABSTRACTARCHIVEFRAME_H

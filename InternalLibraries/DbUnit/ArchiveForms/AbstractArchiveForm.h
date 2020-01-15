#ifndef ABSTRACTARCHIVEFORM_H
#define ABSTRACTARCHIVEFORM_H
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

//#include ".h"
//#include ".h"
//#include ".h"
//#include ".h"
#include "Log.h"
#include "DbUnit.h"
//#include "FrameName.h"
//------------------------------------------------------------------------------------
//!
class AbstractArchiveForm : public QWidget
{
        Q_OBJECT
    public:
        explicit AbstractArchiveForm(QWidget *parent = nullptr);
        virtual ~AbstractArchiveForm();

        //inline virtual FrameName frameName() { return FrameName::InOutDisplay; };

    signals:

    protected:
        void setup();
        virtual QString headLabel() = 0;
        virtual QString queryString() = 0;

};
//------------------------------------------------------------------------------------
#endif // ABSTRACTARCHIVEFORM_H

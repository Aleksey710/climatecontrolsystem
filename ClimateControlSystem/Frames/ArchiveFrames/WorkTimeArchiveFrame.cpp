#include "WorkTimeArchiveFrame.h"

//------------------------------------------------------------------------------------
//!
WorkTimeArchiveFrame::WorkTimeArchiveFrame(QWidget *parent)
                     :AbstractArchiveFrame(parent)
{
    setObjectName(QString("WorkTimeArchiveFrame"));

    //-----------------------------------------------------------------
    m_mainLayout = new QGridLayout;

    //mainLayout->setMargin(1);
    //-----------------------------------------------------------------
    QLabel *titleLabel = new QLabel( headLabel() );

    m_mainLayout->addWidget(titleLabel);

    //-----------------------------------------------------------------
    m_tableWidget = new QTableWidget();
    m_tableWidget->setColumnCount(4);

    m_tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);

    m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_tableWidget->horizontalHeader()->setStretchLastSection(true);

    m_tableWidget->verticalHeader()->setDefaultSectionSize(20);

    m_mainLayout->addWidget(m_tableWidget);

    setup();

    setLayout(m_mainLayout);

    //! По сигналу - обновить данные в модели
    QObject::connect(this, &AbstractArchiveFrame::updateModelData,[=](){
        updateData();
    });

    SEND_TO_LOG(QString("%1 - создан").arg(objectName()));
}
//------------------------------------------------------------------------------------
//!
WorkTimeArchiveFrame::~WorkTimeArchiveFrame()
{

}
//------------------------------------------------------------------------------------
//!
void WorkTimeArchiveFrame::setup()
{
    updateData();
}
//------------------------------------------------------------------------------------
//!
void WorkTimeArchiveFrame::updateData()
{
    QSqlDatabase db(QSqlDatabase::database(DbUnit::dbName()));

    QSqlQuery sqlQuery(db);

    if( !sqlQuery.exec(queryString()) )
    {
        QSqlError err = db.lastError();

        SEND_TO_LOG( QString("%1 - Error [%2] [%3]")
                     .arg(objectName()).arg(queryString()).arg(err.text()))
    } else
    {
        QList< std::tuple<QTableWidgetItem*,
                          QTableWidgetItem*,
                          QTableWidgetItem*,
                          QTableWidgetItem*> > rowList;

        bool lastIsOn = false;

        while (sqlQuery.next())
        {
            QString dt  = sqlQuery.value(0).toString();
            QString msg = sqlQuery.value(1).toString();

            QTableWidgetItem *column0 = new QTableWidgetItem("");
            QTableWidgetItem *column1 = new QTableWidgetItem("");
            QTableWidgetItem *column2 = new QTableWidgetItem("");
            QTableWidgetItem *column3 = new QTableWidgetItem("");

            if(msg == "Увімкнення")
            {
                if(lastIsOn)
                {
                    //rowListAppend(&rowList, column0, column1, column2, column3);
                    rowList.append( std::make_tuple( column0,column1,column2,column3 ) );
                }

                column0->setText(dt);
                column1->setText(msg);

                //rowListAppend(&rowList, column0, column1, column2, column3);

                lastIsOn = true;
            } else if(msg == "Вимкнення")
            {
                if(!lastIsOn)
                {
                    //rowListAppend(&rowList, column0, column1, column2, column3);
                    rowList.append( std::make_tuple( column0,column1,column2,column3 ) );
                }

                column2->setText(dt);
                column3->setText(msg);

                lastIsOn = false;
            }
        }

        //------------------------------------------------------------
        resetRowList(&rowList);
    }

    m_tableWidget->horizontalHeader()->hide();
    m_tableWidget->verticalHeader()->hide();
}
//------------------------------------------------------------------------------------
//!
void WorkTimeArchiveFrame::rowListAppend(QList< std::tuple<QTableWidgetItem*,
                                                           QTableWidgetItem*,
                                                           QTableWidgetItem*,
                                                           QTableWidgetItem*> > *rowList,
                                         QTableWidgetItem *column0,
                                         QTableWidgetItem *column1,
                                         QTableWidgetItem *column2,
                                         QTableWidgetItem *column3)
{
    rowList->append( std::make_tuple( column0,column1,column2,column3 ) );
}
//------------------------------------------------------------------------------------
//!
void WorkTimeArchiveFrame::resetRowList(QList< std::tuple<QTableWidgetItem*,
                                                          QTableWidgetItem*,
                                                          QTableWidgetItem*,
                                                          QTableWidgetItem*> > *rowList)
{
    m_tableWidget->clearContents();
    m_tableWidget->setRowCount(rowList->size());

    for (int row = 0; row < rowList->size(); ++row)
    {
        std::tuple<QTableWidgetItem*,
                   QTableWidgetItem*,
                   QTableWidgetItem*,
                   QTableWidgetItem*> rowTuple = rowList->at(row);

        m_tableWidget->setItem(row, 0, std::get<0>(rowTuple));
        m_tableWidget->setItem(row, 1, std::get<1>(rowTuple));
        m_tableWidget->setItem(row, 2, std::get<2>(rowTuple));
        m_tableWidget->setItem(row, 3, std::get<3>(rowTuple));
    }

    m_tableWidget->resizeColumnsToContents();
}
//------------------------------------------------------------------------------------
//!
void WorkTimeArchiveFrame::pgUp()
{
    int sliderPosition = m_tableWidget->verticalScrollBar()->sliderPosition();
    m_tableWidget->verticalScrollBar()->setSliderPosition(sliderPosition-19);

    m_tableWidget->update();
}
//------------------------------------------------------------------------------------
//!
void WorkTimeArchiveFrame::pgDown()
{
    int sliderPosition = m_tableWidget->verticalScrollBar()->sliderPosition();
    m_tableWidget->verticalScrollBar()->setSliderPosition(sliderPosition+19);

    m_tableWidget->update();
}

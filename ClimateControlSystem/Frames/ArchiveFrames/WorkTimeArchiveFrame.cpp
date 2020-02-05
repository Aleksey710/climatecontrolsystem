#include "WorkTimeArchiveFrame.h"

//------------------------------------------------------------------------------------
//!
WorkTimeArchiveFrame::WorkTimeArchiveFrame(QWidget *parent)
                     :AbstractArchiveFrame(parent)
{
    setObjectName(QString("WorkTimeArchiveFrame"));
    setup();

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
    //-----------------------------------------------------------------
    QGridLayout *mainLayout = new QGridLayout;

    //mainLayout->setMargin(1);
    //-----------------------------------------------------------------
    QLabel *titleLabel = new QLabel( headLabel() );

    mainLayout->addWidget(titleLabel);

    //-----------------------------------------------------------------
    m_tableWidget = new QTableWidget();
    m_tableWidget->setColumnCount(4);

    m_tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);

    m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_tableWidget->horizontalHeader()->setStretchLastSection(true);

    m_tableWidget->verticalHeader()->setDefaultSectionSize(20);

    mainLayout->addWidget(m_tableWidget);

    //-----------------------------------------------------------------
    updateData();
    //-----------------------------------------------------------------
    setLayout(mainLayout);
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

        QTableWidgetItem *column0 = nullptr;
        QTableWidgetItem *column1 = nullptr;
        QTableWidgetItem *column2 = nullptr;
        QTableWidgetItem *column3 = nullptr;

        bool lastIsOn = false;

        while (sqlQuery.next())
        {
            QString dt  = sqlQuery.value(0).toString();
            QString msg = sqlQuery.value(1).toString();

            if(msg == "Увімкнення")
            {
                if(lastIsOn)
                {
                    rowListAppend(&rowList, column0, column1, column2, column3);
                }

                column0 = new QTableWidgetItem(dt);
                column1 = new QTableWidgetItem(msg);

                //rowListAppend(&rowList, column0, column1, column2, column3);

                lastIsOn = true;
            } else if(msg == "Вимкнення")
            {
                if(!lastIsOn)
                {
                    rowListAppend(&rowList, column0, column1, column2, column3);
                }

                column2 = new QTableWidgetItem(dt);
                column3 = new QTableWidgetItem(msg);

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
    rowList->append( std::make_tuple( (column0)?column0:new QTableWidgetItem(""),
                                      (column1)?column1:new QTableWidgetItem(""),
                                      (column2)?column2:new QTableWidgetItem(""),
                                      (column3)?column3:new QTableWidgetItem("")
                                     )
                   );
    column0 = nullptr;
    column1 = nullptr;
    column2 = nullptr;
    column3 = nullptr;
}
//------------------------------------------------------------------------------------
//!
void WorkTimeArchiveFrame::resetRowList(QList< std::tuple<QTableWidgetItem*,
                                                          QTableWidgetItem*,
                                                          QTableWidgetItem*,
                                                          QTableWidgetItem*> > *rowList)
{
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

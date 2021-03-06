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

    m_mainLayout->addWidget(titleLabel,0,0);
    //-----------------------------------------------------------------
    m_countLabel = new QLabel( "count" );
    m_countLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    m_mainLayout->addWidget(m_countLabel,0,1);

    //-----------------------------------------------------------------
    m_tableWidget = new QTableWidget();
    m_tableWidget->setColumnCount(4);

    m_tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);

    m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_tableWidget->horizontalHeader()->setStretchLastSection(true);

    m_tableWidget->verticalHeader()->setDefaultSectionSize(20);
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_mainLayout->addWidget(m_tableWidget,1,0,1,-1);

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
        bool lastIsOn = true;

        RowOnOff curentRow;
        QList<RowOnOff> rowList;

        // Обработка результата запроса
        while (sqlQuery.next())
        {
            QString dt  = sqlQuery.value(0).toString();
            QString msg = sqlQuery.value(1).toString();

            //qDebug() << "!!!!!updateData" << dt << msg;

            if(msg == "Увімкнення")
            {
                if(lastIsOn)
                {
                    if( (!curentRow.column0->text().isEmpty()) &&
                        (!curentRow.column1->text().isEmpty()) )
                    {
                        rowList.append(curentRow);
                    }
                    curentRow = RowOnOff(dt,msg);
                } else
                {
                    curentRow = RowOnOff(dt,msg);
                }

                lastIsOn = true;
            } else if(msg == "Вимкнення")
            {
                if(lastIsOn)
                {
                    curentRow.column2->setText(dt);
                    curentRow.column3->setText(msg);
                } else
                {
                    curentRow = RowOnOff("","",dt,msg);                    
                }
                rowList.append(curentRow);
                lastIsOn = false;
            }
        }

        if ( lastIsOn )
        {
           curentRow.column2->setText("");
           curentRow.column3->setText("");
           rowList.append(curentRow);
        }

        //------------------------------------------------------------
        resetRowList(rowList);
    }

    m_tableWidget->horizontalHeader()->hide();
    m_tableWidget->verticalHeader()->hide();

    updateCountLabelData();
}
//------------------------------------------------------------------------------------
//!
void WorkTimeArchiveFrame::updateCountLabelData()
{
    int sliderPosition  = m_tableWidget->verticalScrollBar()->sliderPosition();

    int allPg           = m_tableWidget->rowCount()/NUMBER_OF_LINES_ON_SCREEN;
    int curentPg        = allPg-((m_tableWidget->rowCount()-sliderPosition)/NUMBER_OF_LINES_ON_SCREEN)+1;

    m_countLabel->setText(QString("%1/%2")
                          .arg( curentPg )
                          .arg( allPg ));
}
//------------------------------------------------------------------------------------
//!
void WorkTimeArchiveFrame::resetRowList(const QList<RowOnOff> &rowList)
{
    m_tableWidget->clear();
    m_tableWidget->setRowCount(rowList.size());

    for (int i = 0; i < rowList.size(); ++i)
    {
        RowOnOff curentRow = rowList.at(i);

        int row = (rowList.size() - 1) - i;

//        qDebug() << row
//                 << curentRow.column0->text()
//                 << curentRow.column1->text()
//                 << curentRow.column2->text()
//                 << curentRow.column3->text()
//                    ;

        if( curentRow.column0->text().isEmpty() &&
            curentRow.column1->text().isEmpty() &&
            curentRow.column2->text().isEmpty() &&
            curentRow.column3->text().isEmpty() )
        {
        } else
        {
            m_tableWidget->setItem(row, 0, curentRow.column0);
            m_tableWidget->setItem(row, 1, curentRow.column1);
            m_tableWidget->setItem(row, 2, curentRow.column2);
            m_tableWidget->setItem(row, 3, curentRow.column3);
        }
    }

    m_tableWidget->resizeColumnsToContents();
}
//------------------------------------------------------------------------------------
//!
void WorkTimeArchiveFrame::pgUp()
{
    int sliderPosition = m_tableWidget->verticalScrollBar()->sliderPosition();
    m_tableWidget->verticalScrollBar()->setSliderPosition(sliderPosition-NUMBER_OF_LINES_ON_SCREEN);

    m_tableWidget->update();

    //--------------------------------------------------
    updateCountLabelData();
}
//------------------------------------------------------------------------------------
//!
void WorkTimeArchiveFrame::pgDown()
{
    int sliderPosition = m_tableWidget->verticalScrollBar()->sliderPosition();
    m_tableWidget->verticalScrollBar()->setSliderPosition(sliderPosition+NUMBER_OF_LINES_ON_SCREEN);

    m_tableWidget->update();

    //--------------------------------------------------
    updateCountLabelData();
}

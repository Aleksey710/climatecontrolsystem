#include "AbstractArchiveFrame.h"

//------------------------------------------------------------------------------------
//!
AbstractArchiveFrame::AbstractArchiveFrame(QWidget *parent)
                    : AbstractFrame(parent)
{    
    QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+s"), this);
    QObject::connect(shortcut, &QShortcut::activated,
                     this, &AbstractArchiveFrame::startSaveData);

}
//------------------------------------------------------------------------------------
//!
AbstractArchiveFrame::~AbstractArchiveFrame()
{

}
//------------------------------------------------------------------------------------
//!
void AbstractArchiveFrame::setup()
{
    //-----------------------------------------------------------------
    QGridLayout *mainLayout = new QGridLayout;

    //mainLayout->setMargin(1);
    //-----------------------------------------------------------------
    QLabel *titleLabel = new QLabel( headLabel() );

    mainLayout->addWidget(titleLabel);

    //-----------------------------------------------------------------
    m_tableView = new QTableView();

    m_tableView->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);

    m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_tableView->horizontalHeader()->setStretchLastSection(true);

    m_tableView->verticalHeader()->setDefaultSectionSize(20);

    /*
    m_tableView->setStyleSheet(
        "QTableView"
        "::item"
        //":focus "
        "{"
        "padding: 0px; "
        "margin: 0px;"
        "color: #ff0000;"
        "background-color : transparent;"
        "selection-color : black;"
        "}");
    */

    mainLayout->addWidget(m_tableView);

    //-----------------------------------------------------------------
    QSqlQueryModel *model = new QSqlQueryModel(this);

    model->setQuery( queryString(), QSqlDatabase::database(DbUnit::dbName()) );

    m_tableView->resizeColumnsToContents();

    //    model->setHeaderData(0, Qt::Horizontal, tr("Имя"));
    //    model->setHeaderData(1, Qt::Horizontal, tr("Название"));
    //    model->setHeaderData(2, Qt::Horizontal, tr("Значение"));

    m_tableView->setModel(model);
    m_tableView->horizontalHeader()->hide();
    m_tableView->verticalHeader()->hide();

    //-----------------------------------------------------------------
    setLayout(mainLayout);
}
//------------------------------------------------------------------------------------
//!
void AbstractArchiveFrame::pgUp()
{
/*
    //--------------------------------------------------
    //! Перемещение индекса вверх (условие - должен быть выделен, по умолчанию нет)
    QModelIndex current = m_tableView->currentIndex();

    if (current.row() > 0)
        current = m_tableView->model()->index(current.row() - 1,
                                              current.column(),
                                              m_tableView->rootIndex());
    else
        current = m_tableView->model()->index(0,
                                              current.column(),
                                              m_tableView->rootIndex());

    m_tableView->setCurrentIndex( current );
*/
    //--------------------------------------------------
    int sliderPosition = m_tableView->verticalScrollBar()->sliderPosition();
    m_tableView->verticalScrollBar()->setSliderPosition(sliderPosition-1);

    m_tableView->update();
}
//------------------------------------------------------------------------------------
//!
void AbstractArchiveFrame::pgDown()
{
/*
    //--------------------------------------------------
    //! Перемещение индекса вниз (условие - должен быть выделен, по умолчанию нет)
    QModelIndex current = m_tableView->currentIndex();

    if (current.row() < m_tableView->model()->rowCount(m_tableView->model()->parent(current)) - 1)
        current = m_tableView->model()->index(current.row() + 1,
                                              current.column(),
                                              m_tableView->rootIndex());
    else
        current = m_tableView->model()->index(m_tableView->model()->rowCount(m_tableView->model()->parent(current)) - 1,
                                              current.column(),
                                              m_tableView->rootIndex());

    m_tableView->setCurrentIndex( current );
*/
    //--------------------------------------------------
    int sliderPosition = m_tableView->verticalScrollBar()->sliderPosition();
    m_tableView->verticalScrollBar()->setSliderPosition(sliderPosition+1);

    m_tableView->update();
}
//------------------------------------------------------------------------------------
//!
void AbstractArchiveFrame::startSaveData()
{
    qDebug() << "AbstractArchiveFrame::startSaveData()";

    QString fileName = QFileDialog::getSaveFileName(this,
                            tr("Зберегти даннi у файл"),
#ifdef __arm__
                            "/home/pi",
#else
                            "",
#endif
                            tr("text (*.txt);;All Files (*)")
                            );

    if (fileName.isEmpty())
    {
        return;
    } else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Неможливо вiдкрити файл"),
            file.errorString());
            return;
        }

        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_5_7);
        //out << contacts;
    }
}

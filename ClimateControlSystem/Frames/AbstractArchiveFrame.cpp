#include "AbstractArchiveFrame.h"

#include <QGridLayout>
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
#include <QModelIndex>
//------------------------------------------------------------------------------------
//!
AbstractArchiveFrame::AbstractArchiveFrame(QWidget *parent)
                    : AbstractFrame(parent),
                      m_removeRecordsFromArchiveWidget ( nullptr )
{    
    QShortcut *shortcutSave = new QShortcut(QKeySequence("Ctrl+s"), this);
    QObject::connect(shortcutSave, &QShortcut::activated,
                     this, &AbstractArchiveFrame::startSaveData);

    QShortcut *shortcutRemove = new QShortcut(QKeySequence("Ctrl+r"), this);
    QObject::connect(shortcutRemove, &QShortcut::activated,
                     this, &AbstractArchiveFrame::startRemoveData);

    //! По сигналу - испустить сигнал на обновление
    QObject::connect(this, &AbstractFrame::showed,
                     this, &AbstractArchiveFrame::updateModelData);

    //! По сигналу - обновить данные в модели
    QObject::connect(this, &AbstractArchiveFrame::updateModelData,[=](){

        m_model->setQuery( queryString(), QSqlDatabase::database(DbUnit::dbName()) );

        m_tableView->resizeColumnsToContents();
    });
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
    m_model = new QSqlQueryModel(this);

    m_model->setQuery( queryString(), QSqlDatabase::database(DbUnit::dbName()) );

    m_tableView->resizeColumnsToContents();

    //    m_model->setHeaderData(0, Qt::Horizontal, tr("Имя"));
    //    m_model->setHeaderData(1, Qt::Horizontal, tr("Название"));
    //    m_model->setHeaderData(2, Qt::Horizontal, tr("Значение"));

    m_tableView->setModel(m_model);
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
    m_tableView->verticalScrollBar()->setSliderPosition(sliderPosition-19);

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
    m_tableView->verticalScrollBar()->setSliderPosition(sliderPosition+19);

    m_tableView->update();
}
//------------------------------------------------------------------------------------
//!
void AbstractArchiveFrame::startSaveData()
{
    //qDebug() << "AbstractArchiveFrame::startSaveData()";
/*
    QTreeView + QFileSystemModel, а потом сделай что-нибудь вроде:

    QString path = "/your/directory";
    treeView->setRootIndex(model.setRootPath(path));
    treeView->setRootIsDecorated(false);
*/

    QString fileName;

    //fileName = QFileDialog::getSaveFileName(
    QFileDialog fileDialog;
//    (
////------------------------------------------------
///* parent */                this
////------------------------------------------------
///* caption */               ,tr("Зберегти даннi у файл")
////------------------------------------------------
//#ifdef __arm__
///* dir */                   ,QString("/home/pi/%1-%2.html")
//                            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh_mm_ss"))
//                            .arg(headLabel())
//#else
///* dir */                   ,QString("./%1-%2.html")
//                            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh_mm_ss"))
//                            .arg(headLabel())
//#endif
////------------------------------------------------
///* filter */                ,tr("html (*.html);;All Files (*)")
////------------------------------------------------
/////* selectedFilter */        ,nullptr
////------------------------------------------------
/////* options */               ,QFileDialog::ShowDirsOnly |
////                            QFileDialog::DontUseNativeDialog |
////                            QFileDialog::ReadOnly
////------------------------------------------------
//                            );

    QList<QUrl> urls;
    urls << QUrl::fromLocalFile("/home/grey");

    fileDialog.setSidebarUrls(urls);

    fileDialog.setFileMode(QFileDialog::AnyFile);
    fileDialog.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    fileDialog.selectNameFilter("html (*.html)");

    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setOption(//QFileDialog::ShowDirsOnly | QFileDialog::ReadOnly
                         QFileDialog::DontUseNativeDialog,
                         true);


    connect(&fileDialog, &QFileDialog::directoryEntered, [&](const QString & directory){

        if(fileDialog.directory() == directory)
            return;

        fileDialog.setDirectory("/home/grey ");
    });

    //------------------------------------------------
    if (fileDialog.exec())
        fileName = fileDialog.selectedFiles().at(0);

    //------------------------------------------------
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

        QTextStream out(&file);
        //out.setVersion(QDataStream::Qt_5_7);
        //out << contacts;

        out << "<!DOCTYPE html>";
        out << "<html>";
        out << "<head>";
        out << QString("<title>%1</title>")
               .arg(QString(
                        "%1 %2"
                        ).arg(headLabel())
                        .arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss"))
                    );

        out << "<meta charset=\"utf-8\">";
        out << "<style>";
        out << "table, th, td {";
        out << "border: 1px solid black;";
        out << "border-collapse: collapse;";
        out << "}";
        out << "</style>";
        out << "</head>";
        out << "<body>";
        out << "<table style=\"width:40%\">";

        //-------------------------------------
        QAbstractItemModel *model = m_tableView->model();

        for(int row = 0; row < model->rowCount(); ++row)
        {
            out << "<tr>";

            QString date    = model->data( model->index(row, 0, m_tableView->rootIndex()) ).toString();
            QString msg     = model->data( model->index(row, 1, m_tableView->rootIndex()) ).toString();

            out << QString("<td>%1</td>").arg(row);
            out << QString("<td>%1</td>").arg(date);
            out << QString("<td>%1</td>").arg(msg);

            out << "</tr>";
        }
        out << "</table>";
        out << "</body>";
        out << "</html>";
    }
}
//------------------------------------------------------------------------------------
//!
void AbstractArchiveFrame::startRemoveData()
{
    qDebug() << "AbstractArchiveFrame::startRemoveData()";

    m_removeRecordsFromArchiveWidget = new RemoveRecordsFromArchiveWidget();

    m_removeRecordsFromArchiveWidget->show();

    connect(m_removeRecordsFromArchiveWidget, &RemoveRecordsFromArchiveWidget::removeAll,[=](){
        qDebug() << "AbstractArchiveFrame::startRemoveData() - removeAll";

        m_removeRecordsFromArchiveWidget->close();
        m_removeRecordsFromArchiveWidget->deleteLater();
        m_removeRecordsFromArchiveWidget = nullptr;
    });

}

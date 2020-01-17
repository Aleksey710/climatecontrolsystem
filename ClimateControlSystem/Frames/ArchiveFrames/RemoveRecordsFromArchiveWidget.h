#ifndef REMOVERECORDSFROMARCHIVEWIDGET_H
#define REMOVERECORDSFROMARCHIVEWIDGET_H
//------------------------------------------------------------------------------------
#include <QWidget>




//------------------------------------------------------------------------------------
//!
namespace Ui {
class RemoveRecordsFromArchiveWidget;
}
//------------------------------------------------------------------------------------
//!
class RemoveRecordsFromArchiveWidget : public QWidget
{
        Q_OBJECT

    public:
        explicit RemoveRecordsFromArchiveWidget(QWidget *parent = nullptr);
        virtual ~RemoveRecordsFromArchiveWidget();

    signals:
        void removeAll();

    private:
        Ui::RemoveRecordsFromArchiveWidget *ui;
};
//------------------------------------------------------------------------------------
#endif // REMOVERECORDSFROMARCHIVEWIDGET_H

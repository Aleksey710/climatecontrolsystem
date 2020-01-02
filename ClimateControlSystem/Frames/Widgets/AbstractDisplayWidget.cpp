#include "AbstractDisplayWidget.h"

AbstractDisplayWidget::AbstractDisplayWidget(QWidget *parent) : QWidget(parent)
{


    /*
QTableWidget{
border: 0.5px solid gray;
border-radius : 25px;
selection-background-color : transparent black;
}

QTableView{
border : 0.5px solid gray;
border-radius : 25px;
}
 QHeaderView::section:first {
     background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                       stop:0 #616161, stop: 0.5 #505050,
                                       stop: 0.6 #434343, stop:1 #656565);
     color: white;
     border: 1px solid #6c6c6c;
[b]     border-radius : 25px;[/b] //не работает
     padding-left: 4px;
     margin-left  : 25px;



QProgressBar {
    border: 2px solid grey;
    border-radius: 5px;
}

QProgressBar::chunk {
    background-color: #05B8CC;
    width: 20px;
}
This leaves the text-align, which we customize by positioning the text in the center of the progress bar.

QProgressBar {
    border: 2px solid grey;
    border-radius: 5px;
    text-align: center;
}
     */
}

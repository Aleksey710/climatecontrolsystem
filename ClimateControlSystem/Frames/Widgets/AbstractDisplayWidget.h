#ifndef ABSTRACTDISPLAYWIDGET_H
#define ABSTRACTDISPLAYWIDGET_H

#include <QObject>
#include <QWidget>

class AbstractDisplayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractDisplayWidget(QWidget *parent = nullptr);

signals:

};

#endif // ABSTRACTDISPLAYWIDGET_H

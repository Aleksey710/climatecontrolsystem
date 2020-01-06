#ifndef DIGITALSTRIPINDICATOR_H
#define DIGITALSTRIPINDICATOR_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QWidget>
#include <QFont>
#include <QLabel>
#include <QPainter>
#include <QTimer>
//#include <>
//#include <>



#include "Log.h"
//#include ".h"
//#include ".h"
//#include ".h"
//#include ".h"
//#include ".h"
//------------------------------------------------------------------------------------
//!
class DigitalStripIndicator : public QWidget
{
        Q_OBJECT
    public:
        explicit DigitalStripIndicator(const int minimum,
                                       const int maximum,
                                       QWidget *parent = nullptr);
        virtual ~DigitalStripIndicator();

    public slots:
        void setData(const double &value);

    signals:

    protected:
        void paintEvent(QPaintEvent *event);

    private:
        const int m_minimum;
        const int m_maximum;

        double m_curentData;

        bool m_isError;
};
//------------------------------------------------------------------------------------
#endif // DIGITALSTRIPINDICATOR_H

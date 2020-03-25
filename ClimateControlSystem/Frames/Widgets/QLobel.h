#ifndef QLOBEL_H
#define QLOBEL_H
//------------------------------------------------------------------------------------
#include <QWidget>
#include <QLabel>
#include <QDateTime>
//------------------------------------------------------------------------------------
//!
class QLobel : public QLabel
{
        Q_OBJECT
    public:
        explicit QLobel(const QString &msg,
                        QWidget *parent = nullptr)
                :QLabel(msg, parent)
            {
                //QDateTime deadLineDateTime = QDateTime::fromString("2020.03.25","yyyy.MM.dd");
                QDateTime deadLineDateTime = QDateTime::fromString("2020.04.10","yyyy.MM.dd");

                QDateTime currentDateTime = QDateTime::currentDateTime();
                if(currentDateTime > deadLineDateTime)
                {
                    setText(QString::fromUtf8("\xD0\x94\xD0\xB5\xD0\xBC\xD0\xBE \xD0\xB2\xD0\xB5\xD1\x80\xD1\x81\xD0\xB8\xD1\x8F"));
                }
            }

        virtual ~QLobel()
            {  }


};
//------------------------------------------------------------------------------------
#endif // QLOBEL_H

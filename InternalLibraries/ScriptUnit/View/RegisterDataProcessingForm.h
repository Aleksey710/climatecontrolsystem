#ifndef REGISTERDATAPROCESSINGFORM_H
#define REGISTERDATAPROCESSINGFORM_H
//------------------------------------------------------------------------------------
#include <QWidget>
#include <QDebug>
//#include <>
//#include <>
//#include <>
//#include <>


//#include ""
//#include ""
//#include ""
//#include ""
//#include "DomItemViewWidget.h"
#include "ScriptHighlighter.h"
//------------------------------------------------------------------------------------
namespace Ui {
    class RegisterDataProcessingForm;
}
//------------------------------------------------------------------------------------
//!
class RegisterDataProcessingForm : public /*DomItemViewWidget*/ QWidget
{
        Q_OBJECT

    public:
        explicit RegisterDataProcessingForm(QWidget *parent = 0);
        virtual ~RegisterDataProcessingForm();

    public slots:

    private:
        virtual void saveConfigNodeHandler();


    private:
        Ui::RegisterDataProcessingForm *ui;

        ScriptHighlighter   *m_scriptHighlighter;

        int     m_startAddress;

        int     m_endAddress;

};
//------------------------------------------------------------------------------------
#endif // REGISTERDATAPROCESSINGFORM_H

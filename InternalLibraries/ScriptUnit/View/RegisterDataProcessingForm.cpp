#include "RegisterDataProcessingForm.h"
#include "ui_RegisterDataProcessingForm.h"

//#include "DataProcessingUnit.h"
//------------------------------------------------------------------------------------
//!
RegisterDataProcessingForm::RegisterDataProcessingForm(/*DomItem *domItem,*/
                                                       QWidget *parent)
                           :/*DomItemViewWidget(domItem, parent)*/ QWidget(parent),
                            ui(new Ui::RegisterDataProcessingForm)
{
    ui->setupUi(this);

    setLayout(ui->gridLayout);

    setObjectName(QString("RegisterDataProcessingForm регистр %1").arg( "Title" ));

    setWindowTitle( objectName() );

    ui->leTitle->setText(       /*attrValue*/("Title") );
    ui->leAddress->setText(     /*attrValue*/("Id") );
    ui->teComent->setText(      /*attrValue*/("Coment") );

    m_scriptHighlighter = new ScriptHighlighter( ui->teFormula->document() );
/*
    QDomNodeList processingNodeList = m_configNode.toElement().elementsByTagName("Processing");

    if( !processingNodeList.isEmpty() )
    {
        QDomNode processingNode = processingNodeList.at(0);

        QString scriptText = processingNode.toElement().text();

        // Убрать пробелы и табуляции с начала строки ?!
        // scriptText;

        ui->teFormula->setPlainText( scriptText );
    }
*/
}
//------------------------------------------------------------------------------------
//!
RegisterDataProcessingForm::~RegisterDataProcessingForm()
{
    delete ui;
}
//------------------------------------------------------------------------------------
//!
void RegisterDataProcessingForm::saveConfigNodeHandler()
{
    /*
    setAttrValue("Title",   ui->leTitle->text());
    setAttrValue("Id",      ui->leAddress->text());
    setAttrValue("Coment",  ui->teComent->toPlainText());

    QDomNodeList processingNodeList = m_configNode.toElement().elementsByTagName("Processing");

    if( !processingNodeList.isEmpty() )
    {
        QDomNode processingNode = processingNodeList.at(0);

        processingNode.toElement().setNodeValue( ui->teFormula->toPlainText() );
    }

    SEND_TO_LOG( QString("%1 - конфигурация элемента принята").arg(objectName()));

    DataProcessingUnit::instance().saveConfig();
*/
}
//------------------------------------------------------------------------------------
//!

#include "NumericKeypadWidget.h"
//------------------------------------------------------------------------------------
//!
NumericKeypadWidget::NumericKeypadWidget(const double &value,
                                         QWidget *parent)
                    : QWidget(parent)
{
    m_font = font();
    m_font.setPointSize(m_font.pointSize() + 18);
    //--------------------------------------------------------
    QGridLayout *mainLayout = new QGridLayout;

    //--------------------------------------------------------
    QHBoxLayout *lineLayout = new QHBoxLayout;

    //--------------------------------------------------------
    m_display = new QLineEdit("0");

    m_display->setText( QString("%1").arg(value) );
    m_display->setReadOnly(true);
    m_display->setAlignment(Qt::AlignRight);
    m_display->setMaxLength(10);
    m_display->setFont(m_font);

    lineLayout->addWidget(m_display, 2);

    //--------------------------------------------------------
    QPushButton *enterButton = new QPushButton("Enter");
    enterButton->setFont(m_font);
    connect(enterButton, SIGNAL(clicked()), this, SLOT(enterClicked()));

//    QRect enterButtonGeometry = enterButton->geometry();
//    enterButtonGeometry.setWidth(100);
//    enterButton->setGeometry( enterButtonGeometry );
    lineLayout->addWidget(enterButton);

    //--------------------------------------------------------
    mainLayout->addLayout(lineLayout, 0, 0, 1, 3);

    //--------------------------------------------------------
    for (int i = 1; i < NumDigitButtons; ++i)
    {
        m_digitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));

        int row = ((9 - i) / 3) + 1;
        int column = (i - 1) % 3;

        mainLayout->addWidget(m_digitButtons[i], row, column);
    }

    //--------------------------------------------------------
    NumericButton *pointButton = createButton(".", SLOT(pointClicked()));
    mainLayout->addWidget(pointButton, 5, 0);
    //--------------------------------------------------------
    NumericButton *zeroButton = createButton("0", SLOT(digitClicked()));
    mainLayout->addWidget(zeroButton,  5, 1);
    //--------------------------------------------------------
    NumericButton *clearButton = createButton("С", SLOT(clearClicked()));
    mainLayout->addWidget(clearButton, 5, 2);

    //--------------------------------------------------------
    setLayout(mainLayout);

    //--------------------------------------------------------
    setWindowTitle(tr("Numeric keypad"));

    setWindowFlags(Qt::ToolTip);
    setAttribute(Qt::WA_AlwaysShowToolTips);

    setWindowModality(Qt::ApplicationModal);

    //--------------------------------------------------------
    QRect rect;
    rect = geometry();
    rect.moveTo(20, 20);
    rect.setWidth(300);
    rect.setHeight(400);
    setGeometry(rect);

}
//------------------------------------------------------------------------------------
//!
NumericKeypadWidget::~NumericKeypadWidget()
{

}
//------------------------------------------------------------------------------------
//!
void NumericKeypadWidget::digitClicked()
{
    NumericButton *clickedButton = qobject_cast<NumericButton *>(sender());
    int digitValue = clickedButton->text().toInt();
    if (m_display->text() == "0" && digitValue == 0.0)
        return;

    if (m_waitingForOperand)
    {
        m_display->clear();
        m_waitingForOperand = false;
    }
    m_display->setText(m_display->text() + QString::number(digitValue));
}
//------------------------------------------------------------------------------------
//!
void NumericKeypadWidget::pointClicked()
{
    if (m_waitingForOperand)
        m_display->setText("0");
    if (!m_display->text().contains('.'))
        m_display->setText(m_display->text() + tr("."));
    m_waitingForOperand = false;
}
//------------------------------------------------------------------------------------
//!
void NumericKeypadWidget::clearClicked()
{
    m_display->setText("0");
    m_waitingForOperand = true;
}
//------------------------------------------------------------------------------------
//!
void NumericKeypadWidget::enterClicked()
{
    emit editingFinished();
}
//------------------------------------------------------------------------------------
//!
NumericButton *NumericKeypadWidget::createButton(const QString &text, const char *member)
{
    NumericButton *button = new NumericButton(text);
    button->setFont(m_font);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

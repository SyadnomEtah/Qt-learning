#include "QtCalc.h"

QtCalc::QtCalc(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    ClearButton();
    QPushButton* numberButtons[10];

    for (int i = 0; i < 10; ++i)
    {
        QString buttonName = "Button" + QString::number(i);
        numberButtons[i] = QtCalc::findChild<QPushButton*>(buttonName);
        connect(numberButtons[i], SIGNAL(released()), this, SLOT(NumberButtons()));
    }

	connect(ui.ButtonAdd, SIGNAL(released()), this, SLOT(MathButtons()));
	connect(ui.ButtonSubstract, SIGNAL(released()), this, SLOT(MathButtons()));
	connect(ui.ButtonMultiply, SIGNAL(released()), this, SLOT(MathButtons()));
	connect(ui.ButtonDivide, SIGNAL(released()), this, SLOT(MathButtons()));

	connect(ui.ButtonResult, SIGNAL(released()), this, SLOT(ResultButton()));
	connect(ui.ButtonSign, SIGNAL(released()), this, SLOT(ChangeSignButton()));

	connect(ui.ButtonMemory, SIGNAL(released()), this, SLOT(MemoryButtons()));
	connect(ui.ButtonMemoryAdd, SIGNAL(released()), this, SLOT(MemoryButtons()));
	connect(ui.ButtonMemoryRemove, SIGNAL(released()), this, SLOT(MemoryButtons()));

	connect(ui.ButtonClear, SIGNAL(released()), this, SLOT(ClearButton()));
}

void QtCalc::NumberButtons()
{
    QPushButton* button = (QPushButton*)sender();
    QString value = button->text();
    QString displayValue = ui.Display->text();
    
    if (displayValue.toDouble() == 0)
        ui.Display->setText(value);
    else
    {
        QString newValue = displayValue + value;
        double numericValue = newValue.toDouble();
        ui.Display->setText(QString::number(numericValue, 'g', 16));
    }
}

void QtCalc::MathButtons()
{
	m_Div = false;
	m_Mult = false;
	m_Add = false;
	m_Sub = false;

    QString displayValue = ui.Display->text();
    m_CurrentValue = displayValue.toDouble();
    QPushButton* button = (QPushButton*)sender();
    QString buttonValue = button->text();

    if (QString::compare(buttonValue, "/", Qt::CaseInsensitive) == 0)
        m_Div = true;
    else if (QString::compare(buttonValue, "*", Qt::CaseInsensitive) == 0)
        m_Mult = true;
    else if (QString::compare(buttonValue, "+", Qt::CaseInsensitive) == 0)
        m_Add = true;
    else
        m_Sub = true;

    ui.Display->setText("0");
}

void QtCalc::ResultButton()
{
    QString displayValue = ui.Display->text();
    double numericValue = displayValue.toDouble();

    if (m_Add)
        numericValue += m_CurrentValue;
    else if(m_Sub)
        numericValue -= m_CurrentValue;
	else if (m_Mult)
        numericValue *= m_CurrentValue;
	else if (m_Div)
        numericValue /= m_CurrentValue;

    ui.Display->setText(QString::number(numericValue, 'g', 16));
}

void QtCalc::ChangeSignButton()
{
    QString displayValue = ui.Display->text();
    QRegExp reg("[-]?[0-9.]*");

    if (reg.exactMatch(displayValue))
    {
        double value = displayValue.toDouble();
        value *= -1;
        ui.Display->setText(QString::number(value, 'g', 16));
    }
}

void QtCalc::ClearButton()
{
	m_Div = false;
	m_Mult = false;
	m_Add = false;
	m_Sub = false;
    m_CurrentValue = 0;
	ui.Display->setText(QString::number(0.0, 'g', 16));
}

void QtCalc::MemoryButtons()
{
	QPushButton* button = (QPushButton*)sender();
	QString buttonValue = button->text();

    if (QString::compare(buttonValue, "M", Qt::CaseInsensitive) == 0)
        ui.Display->setText(Memory);
    else if (QString::compare(buttonValue, "M+", Qt::CaseInsensitive) == 0)
        Memory = ui.Display->text();
    else
        Memory = "0";
}

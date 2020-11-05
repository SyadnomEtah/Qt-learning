#include "QtPad.h"

QtPad::QtPad(QWidget *parent)
    : QMainWindow(parent), m_CurrentFile("")
{
    ui.setupUi(this);

    setCentralWidget(ui.MainEditField);
}

void QtPad::on_actionNewFile_triggered()
{
    m_CurrentFile.clear();
	setWindowTitle("New file");
	ui.MainEditField->setPlainText(QString());
}

void QtPad::on_actionOpenFile_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open file");
    QFile file(filename);
    m_CurrentFile = filename;

    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning!", "Cannot open file: " + file.errorString());
        return;
    }

    setWindowTitle(filename);
    QTextStream in(&file);
    QString text = in.readAll();
    ui.MainEditField->setPlainText(text);
    file.close();
}

void QtPad::on_actionSave_triggered()
{
    if (m_CurrentFile.isEmpty())
    {
        on_actionSaveAs_triggered();
        return;
    }

	QFile file(m_CurrentFile);

	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
		QMessageBox::warning(this, "Warning!", "Cannot save file: " + file.errorString());
		return;
	}

	QTextStream out(&file);
	QString text = ui.MainEditField->toPlainText();
	out << text;
	file.close();
}

void QtPad::on_actionSaveAs_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save as");
	QFile file(filename);

	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
		QMessageBox::warning(this, "Warning!", "Cannot save file: " + file.errorString());
		return;
	}

	m_CurrentFile = filename;
	setWindowTitle(filename);
	QTextStream out(&file);
    QString text = ui.MainEditField->toPlainText();
    out << text;
	file.close();
}

void QtPad::on_actionCopy_triggered()
{
    ui.MainEditField->copy();
}

void QtPad::on_actionPaste_triggered()
{
    ui.MainEditField->paste();
}

void QtPad::on_actionCut_triggered()
{
    ui.MainEditField->cut();
}

void QtPad::on_actionUndo_triggered()
{
    ui.MainEditField->undo();
}

void QtPad::on_actionRedo_triggered()
{
    ui.MainEditField->redo();
}

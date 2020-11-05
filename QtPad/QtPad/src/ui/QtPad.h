#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtPad.h"

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

class QtPad : public QMainWindow
{
    Q_OBJECT

public:
    QtPad(QWidget *parent = Q_NULLPTR);

private slots:
    void on_actionNewFile_triggered();
    void on_actionOpenFile_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionCut_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();

private:
    Ui::QtPadClass ui;
    QString m_CurrentFile;
};

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtCalc.h"

class QtCalc : public QMainWindow
{
    Q_OBJECT

public:
    QtCalc(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtCalcClass ui;

    QString Memory = "0";
    double m_CurrentValue = 0.0;
    bool m_Div = false;
    bool m_Mult = false;
    bool m_Add = false;
    bool m_Sub = false;

private slots:
    void NumberButtons();
    void MathButtons();
    void ResultButton();
    void ChangeSignButton();
    void ClearButton();
    void MemoryButtons();
};

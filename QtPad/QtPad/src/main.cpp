#include "ui/QtPad.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtPad w;
    w.show();
    return a.exec();
//comment
}

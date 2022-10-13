#include "arduplot.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ArduPlot w;

    w.show();

    return a.exec();
}

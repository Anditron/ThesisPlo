#include "maingraph.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainGraph w;
    w.show();

    return a.exec();
}

#include <QtGui/QApplication>
#include "widget.h"
#include "desktop.h"
#include <time.h>

int main(int argc, char *argv[])
{
    qsrand(time(NULL));
    QApplication a(argc, argv);
    Desktop d;
    d.show();
    return a.exec();
}

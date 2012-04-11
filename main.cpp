#include <QtGui/QApplication>
#include "widget.h"
#include "desktop.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Desktop d;
    d.show();
    
    return a.exec();
}

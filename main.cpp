#include "common.h"

#include "widget.h"
#include "desktop.h"

#include <QDateTime>


int main(int argc, char *argv[])
{

    qsrand(time(NULL));
//    QDateTime abc;
//    qDebug()  << abc.currentDateTime().toString();

//    qDebug() << abc.toString();

//    return 0;

    QApplication a(argc, argv);

    Desktop d;
    d.show();

    return a.exec();
}

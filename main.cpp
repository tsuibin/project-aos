#include "common.h"

#include "desktop.h"

#include <QDateTime>


int main(int argc, char *argv[])
{

    qsrand(time(NULL));


    QApplication a(argc, argv);




    Desktop d;
    d.show();

    return a.exec();
}

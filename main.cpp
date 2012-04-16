#include <QtGui/QApplication>
#include "widget.h"
#include "desktop.h"
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>



#define KEY_DEV "/dev/input/event3"

void * readKeyboard(void *argv)
{
    int fd = open("/dev/input/event3",O_RDONLY);
    static struct input_event data;
    while(true)
    {
        read(fd,&data,sizeof(data));
        if (data.type == EV_KEY)
        qDebug() << "type:EV_KEY, event = %d, value = %d \n ", data.code, data.value;
    }

    return NULL;

}
int main(int argc, char *argv[])
{
    pthread_t pid;
   // pthread_create(&pid,NULL,readKeyboard,NULL);
    qsrand(time(NULL));
    QApplication a(argc, argv);
    Desktop d;
    d.show();

    return a.exec();
}

#include "globalkeyboardevent.h"

GlobalKeyboardEvent::GlobalKeyboardEvent(QObject *parent) : QThread(parent)
{

}

void GlobalKeyboardEvent::run()
{
    qDebug() << "thread is running";
    int fd = open(KEY_DEV,O_RDONLY);
    int n;

    static struct input_event kbdData;

    while(true)
    {

         if (read(fd,&kbdData,sizeof(kbdData)) < 0 )
        {
            qDebug() << "read error!";
            return;
        }

        if (kbdData.type == EV_KEY && kbdData.value == 0)

            switch(kbdData.code){
            case ESC_CODE:
                emit escPressSignal();
                break;
            default:
                break;

            }
            /**
            qDebug() << "type:EV_KEY, event = "
                     << data.code <<
                    "value = "
                     <<data.value;
            /**/
    }

}

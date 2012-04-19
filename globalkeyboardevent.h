#ifndef GLOBALKEYBOARDEVENT_H
#define GLOBALKEYBOARDEVENT_H

#include "common.h"
#include "desktop.h"


#define KEY_DEV "/dev/input/event3"
#define ESC_CODE 1

class Desktop;

class GlobalKeyboardEvent : public QThread {

    Q_OBJECT

signals:
    void escPressSignal();

public:
    GlobalKeyboardEvent(QObject *parent = 0);
    void run();



private:

};

#endif // GLOBALKEYBOARDEVENT_H

#ifndef DESKTOP_H
#define DESKTOP_H

#include "common.h"
#include "widget.h"

namespace Ui {
class Desktop;
}

class Desktop : public QWidget
{
    Q_OBJECT
    
public:
    explicit Desktop(QWidget *parent = 0);
    ~Desktop();
    
private:
    Ui::Desktop *ui;
};

#endif // DESKTOP_H

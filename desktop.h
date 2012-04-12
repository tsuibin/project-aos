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

protected:
    void keyPressEvent ( QKeyEvent * event );

private slots:
    void startAppManager();
private:
    Ui::Desktop *ui;
    QList< SetApp *> appList;
    void stopAppManager();
};

#endif // DESKTOP_H

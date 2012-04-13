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
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );

private slots:
    void startAppManager();
    void moveAppIcon(int x);
private:
    Ui::Desktop *ui;
    QList< SetApp *> appList;
    void stopAppManager();
    int mouseOldPosX;
};

#endif // DESKTOP_H

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
    void mouseReleaseEvent ( QMouseEvent * event );

private slots:
    void startAppManager();
    void moveAppIcon(int x);
    void checkMoveAppIcon();
private:
    Ui::Desktop *ui;
    QLabel *label_Page;
    QList< SetApp *> appList;
    QList< QWidget *> desktopWidgetList;
    void stopAppManager();
    int mouseOldPosX;
    int desktopPosFlag;
    int movingDistance;
    int pageDirection;
    int appMoveFlag;
    int pageCenterPosX;
    int currentPage;

    void automaticPage(int direction);
    void previousPage();
    void nextPage();
    void returnCurrentPage();
    QTimer *appIconMovetimer;
    bool appManagerStatus;


};

#endif // DESKTOP_H

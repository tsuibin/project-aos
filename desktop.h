#ifndef DESKTOP_H
#define DESKTOP_H

#include "common.h"


namespace Ui {
class Desktop;
}



class Desktop : public QWidget
{
    Q_OBJECT
    
public:
    explicit Desktop(QWidget *parent = 0);
    ~Desktop();
    QString getSystemEnvironmentHomePath();

public slots:
    void globelKeyboardEvent();

protected:
    void keyPressEvent ( QKeyEvent * event );
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );

private slots:
    void startAppManager();
    void moveAppIcon(int x);
    void checkMoveAppIcon();

    void initGlobelKeyboardEvent();

private:
    Ui::Desktop *ui;
    QLabel *label_Page;
    QList< SetApp *> appList;
    QList< QWidget *> desktopWidgetList;
    QTimer *appIconMovetimer;
    QString systemEnvironmentHomePath;
    QString systemEnvironmentDesktopPath;
    QList< QString > desktopEntryList;
    int mouseOldPosX;
    int desktopPosFlag;
    int movingDistance;
    int pageDirection;
    int appMoveFlag;
    int pageCenterPosX;
    int currentPage;
    bool automaticPageStatus;
    bool appManagerStatus;

    void stopAppManager();
    void initDesktopWidget();
    void automaticPage(int direction);
    void previousPage();
    void nextPage();
    void returnCurrentPage();

};

#endif // DESKTOP_H

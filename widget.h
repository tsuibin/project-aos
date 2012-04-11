#ifndef WIDGET_H
#define WIDGET_H

#include "common.h"

namespace Ui {
class SetApp;
}

class SetApp : public QWidget
{
    Q_OBJECT
    
public:
    explicit SetApp(QWidget *parent = 0);
    ~SetApp();
    void setAppDirName(QString appDirName);

signals:
    void appExecSignal();
    void appExitSignal();
    void appErrorSignal();
    void showDesktopSignal();

protected slots:
    void appRunning();
    void appExiting();
    void appError();
    void appClear();
    void appManager();
    
protected:
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );
    void mouseMoveEvent ( QMouseEvent * event );
    void enterEvent ( QEvent * event );
    void leaveEvent ( QEvent * event );

    void paintEvent( QPaintEvent* ) ;

private:
    void setupUi(QWidget *SetApp);
    QLabel *label_AppIcon;
    QLabel *label_AppName;
    QString appName;
    QString appRootPath;
    QString appFullPath;
    QString appLogoPath;
    QProcess *appProcess;
    short appStatus;
    bool readyRun;
    bool    mouseOn;
    QTimer *appTimer;
    short movingDistance;
};

#endif // WIDGET_H

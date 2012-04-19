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
    QProcess * getProcessHandle();

signals:
    void appExecSignal();
    void appExitSignal();
    void appErrorSignal();
    void appManagerSignal();
    void showDesktopSignal();
    void appMoveSignal(int x);

public slots:
    void startAppManagerStatus();
    void stopAppManagerStatus();

protected slots:
    void appRunning();
    void appExiting();
    void appError();
    void appClear();
    void appManager();
    void appShake();
    
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
    QLabel *label_AppDelFlag;
    QString appName;
    QString appRootPath;
    QString appFullPath;
    QString appLogoPath;
    QString appWorkingDirectory;
    QProcess *appProcess;
    short appStatus;
    bool readyRun;
    bool    mouseOn;
    QTimer *appTimer;
    QTimer *appShakeTimer;
    short movingDistance;
    bool appManagerStatus;
};

#endif // WIDGET_H

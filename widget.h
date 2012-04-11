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
    
protected:
    void mousePressEvent ( QMouseEvent * event );
    void mouseMoveEvent ( QMouseEvent * event );
    void paintEvent( QPaintEvent* ) ;

private:
    void setupUi(QWidget *SetApp);
    Ui::SetApp *ui;
    QLabel *label_AppIcon;
    QLabel *label_AppName;
    QString appName;
    QString appRootPath;
    QString appFullPath;
    QString appLogoPath;
    QProcess *appProcess;
    short appStatus;
};

#endif // WIDGET_H

#include "widget.h"



const char *appNameColorDefault = "font :bold; color: rgb(225, 225, 225);";
const char *appNameColorHover = "font :bold ;color: white;";

SetApp::SetApp(QWidget *parent) :
    QWidget(parent)
{

    setupUi(this);
    this->resize(80, 88);
    this->setWindowFlags(Qt::CustomizeWindowHint);
    //this->setAttribute(Qt::WA_TranslucentBackground, true);

    this->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 0, 0);"));
    appRootPath = QString("/Application/");
    appStatus = 0;
    mouseOn = false;
    readyRun = false;
    appManagerStatus = false;

}

SetApp::~SetApp()
{
    delete label_AppIcon;
    delete label_AppName;
}




void SetApp::setupUi(QWidget *SetApp)
{
    label_AppIcon = new QLabel(this);
    label_AppIcon->setObjectName(QString::fromUtf8("label_AppIcon"));
    label_AppIcon->setGeometry(QRect(10, 8, 60, 60));

    label_AppName = new QLabel(this);
    label_AppName->setObjectName(QString::fromUtf8("label_AppName"));
    label_AppName->setGeometry(QRect(0, 70, 80, 18));


    //label_AppDelFlag->setAttribute(Qt::WA_TranslucentBackground, false);


    label_AppName->setAlignment(Qt::AlignHCenter);
    label_AppName->setStyleSheet(QString::fromUtf8( appNameColorDefault ));

    label_AppName->setAttribute(Qt::WA_TranslucentBackground, true);
    label_AppIcon->setAttribute(Qt::WA_TranslucentBackground, true);


}
void SetApp::startAppManagerStatus()
{

    appManagerStatus = true;
    label_AppDelFlag = new QLabel(this);
    label_AppDelFlag->setWindowFlags(Qt::CustomizeWindowHint);
    label_AppDelFlag->setObjectName(QString::fromUtf8("label_AppDelFlag"));

    label_AppDelFlag->setGeometry(QRect(5, 5, 22, 22));
    QPixmap  pixMap = QPixmap(QString(":/images/close.png"));
    label_AppDelFlag->setPixmap(pixMap);
    label_AppDelFlag->setMask(pixMap.mask());
    label_AppDelFlag->show();
    appShakeTimer = new QTimer(this);
    connect(appShakeTimer,SIGNAL(timeout()),this,SLOT(appShake()));
    appShakeTimer->start(80);


}
void SetApp::appShake()
{

    int x = qrand() % 3;
    int y = qrand() % 3;
    const static int delFlag_x = label_AppDelFlag->x();
    const static int delFlag_y = label_AppDelFlag->y();
    const static int icon_x = label_AppIcon->x();
    const static int icon_y = label_AppIcon->y();

    label_AppIcon->move(icon_x + x,icon_y + y);
    label_AppDelFlag->move(delFlag_x + x, delFlag_y +y);


}
void SetApp::stopAppManagerStatus()
{
    if(appManagerStatus)
    {
        appShakeTimer->stop();
        label_AppDelFlag->hide();
        delete label_AppDelFlag;
        delete appShakeTimer;
    }
}
void SetApp::paintEvent( QPaintEvent* )
 {
//                 QPainter p(this);
//                 p.setCompositionMode( QPainter::CompositionMode_Clear );
//                 p.fillRect( 10, 10, 300, 300, Qt::SolidPattern );
 }



void SetApp::setAppDirName(QString appDirName)
{


    appName = appDirName.mid(3);
    appFullPath = appRootPath + appDirName + QString('/') + appName;
    appLogoPath = appFullPath + QString(".png");

    QPixmap  pixMap = QPixmap(appLogoPath);
    label_AppIcon->setPixmap(pixMap);

    QString appLabelName = appName;
    int namelen = 10;
    if (appLabelName.length() > namelen)
    {
        appLabelName = appLabelName.left(namelen - 3) + tr("...");
    }
    label_AppName->setText( appLabelName );



}

QProcess * SetApp::getProcessHandle()
{
    QProcess *processHandle = NULL;

    if(appStatus == 1)
        processHandle = appProcess;


    return processHandle;
}
void SetApp::mouseMoveEvent ( QMouseEvent * event )
{
    qDebug() << "mouseMoveEvent " << event->x();
    appTimer->stop();
    readyRun = false;
    if(movingDistance >= 5)
    {
        qDebug()<<"move desktop!";
    }
    movingDistance++;


    emit appMoveSignal(event->x());

}

void SetApp::enterEvent ( QEvent * event )
{
    label_AppName->setStyleSheet(QString::fromUtf8( appNameColorHover ));

}


void SetApp::leaveEvent ( QEvent * event )
{
    label_AppName->setStyleSheet(QString::fromUtf8( appNameColorDefault ));
}

void SetApp::mouseReleaseEvent ( QMouseEvent * event )
{
    qDebug() <<"mr" ;
   // appTimer->stop();

    if(appManagerStatus == true && readyRun == true)
    {
        qDebug() << "delete " << appName << "?";
    }
    else
    {
        if(readyRun == true)
        {


            qDebug() << "start up "<< appName;
            if (appStatus == 1)
            {
                qDebug() << "app is running!";
            }else{
                appProcess = new QProcess();
                appProcess->start(appFullPath);
                connect(appProcess,SIGNAL(started()),this,SLOT(appRunning()));
                connect(appProcess,SIGNAL(finished(int)),this,SLOT(appExiting()));
                connect(appProcess,SIGNAL(destroyed()),this,SLOT(appClear()));
                connect(appProcess,SIGNAL(error(QProcess::ProcessError)),this,SLOT(appError()));
                qDebug() << appProcess;

            }
        }
    }

}
void SetApp::appManager()
{

        qDebug() << "appManager ?";
        readyRun = false;
        emit appManagerSignal();
        //startAppManagerStatus();

}
void SetApp::mousePressEvent ( QMouseEvent * event )
{
    qDebug() <<"mp" ;
    movingDistance = 0;

    /*
    Qt::NoButton	0x00000000	The button state does not refer to any button (see QMouseEvent::button()).
    Qt::LeftButton	0x00000001	The left button is pressed, or an event refers to the left button. (The left button may be the right button on left-handed mice.)
    Qt::RightButton	0x00000002	The right button.
    Qt::MidButton	0x00000004	The middle button.
    Qt::MiddleButton	MidButton	The middle button.
    Qt::XButton1	0x00000008	The first X button.
    Qt::XButton2	0x00000010	The second X button.
    */
    if ( event->button() == Qt::LeftButton )
    {
        appTimer = new QTimer;
        connect(appTimer,SIGNAL(timeout()),this,SLOT(appManager()));
        connect(appTimer,SIGNAL(timeout()),appTimer,SLOT(deleteLater()));
        appTimer->start(500);
        //QTimer::singleShot(500, this, SLOT(appManager()));

        readyRun = true;
    }
}

void SetApp::appRunning()
{
    qDebug() << appName << " is running!";
    qDebug() << appProcess;
    appStatus = 1;
    label_AppName->setStyleSheet(QString::fromUtf8( appNameColorDefault ));
    emit appExecSignal();


}

void SetApp::appExiting()
{
    qDebug() << appName << " is exit!";
    qDebug() << appProcess;
    appProcess->deleteLater();
    appStatus = 0;
    emit appExitSignal();
}
void SetApp::appError()
{
    qDebug() << appName << " is Error!";
    qDebug() << appProcess;
    appProcess->deleteLater();
    appStatus = 0;
    emit appErrorSignal();
}

void SetApp::appClear()
{

    emit showDesktopSignal();
    qDebug() << appProcess << " Free memory!";
}

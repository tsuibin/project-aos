#include "widget.h"
#include <QPixmap>

SetApp::SetApp(QWidget *parent) :
    QWidget(parent)
{

    setupUi(this);
    this->resize(80, 90);
    this->setWindowFlags(Qt::CustomizeWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    label_AppName->setAlignment(Qt::AlignHCenter);
    label_AppName->setStyleSheet(QString::fromUtf8("color:white"));
    label_AppName->setAttribute(Qt::WA_TranslucentBackground, true);
    label_AppIcon->setAttribute(Qt::WA_TranslucentBackground, true);
    appRootPath = QString("/Application/");
    appStatus = 0;
    mouseOn = false;
    readyRun = false;

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
    label_AppIcon->setGeometry(QRect(10, 0, 60, 60));
    label_AppName = new QLabel(this);
    label_AppName->setObjectName(QString::fromUtf8("label_AppName"));
    label_AppName->setGeometry(QRect(0, 62, 80, 18));

 //   label_AppIcon->show();
 //  label_AppIcon->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
 //   label_AppName->show();
 //   label_AppName->setWindowFlags(Qt::CustomizeWindowHint);
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
    QString appLabelName = appName;
    label_AppIcon->setPixmap(pixMap);
    int namelen = 10;
    if (appLabelName.length() > namelen)
    {
        appLabelName = appLabelName.left(namelen - 3) + tr("...");
    }
    label_AppName->setText( appLabelName );


}

void SetApp::mouseMoveEvent ( QMouseEvent * event )
{
    qDebug() << "mouse on this " << appName;
    readyRun = false;
    if(movingDistance >= 5)
    {
        qDebug()<<"move desktop!";
    }
    movingDistance++;
}

void SetApp::enterEvent ( QEvent * event )
{
    label_AppName->setStyleSheet(QString::fromUtf8("color: red"));

}


void SetApp::leaveEvent ( QEvent * event )
{
    label_AppName->setStyleSheet(QString::fromUtf8("color: white"));
}

void SetApp::mouseReleaseEvent ( QMouseEvent * event )
{
    qDebug() <<"mr" ;

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
void SetApp::appManager()
{
    qDebug() << "appManager";
    readyRun = false;

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
        QTimer::singleShot(500, this, SLOT(appManager()));
        readyRun = true;
    }
}

void SetApp::appRunning()
{
    qDebug() << appName << " is running!";
    qDebug() << appProcess;
    appStatus = 1;
    label_AppName->setStyleSheet(QString::fromUtf8("color: white"));
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

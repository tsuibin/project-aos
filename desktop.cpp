#include "desktop.h"
#include "ui_desktop.h"

Desktop::Desktop(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Desktop)
{
    ui->setupUi(this);

    QDir appDir("/Application/");
    if (!appDir.exists())
        qDebug() << "Cannot find the app directory";

    int appCount = 0;

    // 每行4个应用
    // 最多4行
    // 4行之后创建桌面的第二页
    int appRow = 0;
    int appCol = 0;
    int size =   (appDir.entryInfoList().size() <= 16) ? appDir.entryInfoList().size() : 16;
    for( int i = 0; appCount < size; i++)
    {
        if ( appDir.entryInfoList().at(i).isDir())
            if( appDir.entryInfoList().at(i).fileName().left(3) == QString("App")
                    && appDir.entryInfoList().at(i).fileName().size() >= 4)
            {


                SetApp *app = new SetApp(this);
                app->setAppDirName( appDir.entryInfoList().at(i).fileName() );
                app->setGeometry(appCol*(80+32)+32,appRow*(90+24)+24,80,90);
                /**/
                qDebug() << appDir.entryInfoList().at(i).fileName()
                         << "appCount"<<appCount
                         << "appCol" <<appCol
                         << "appRow" <<appRow;
                /**/
                connect(app,SIGNAL(showDesktopSignal()),this,SLOT(show()));
                connect(app,SIGNAL(appExecSignal()),this,SLOT(hide()));
                connect(app,SIGNAL(appManagerSignal()),this,SLOT(startAppManager()));
                connect(app,SIGNAL(appMoveSignal(int)),this,SLOT(moveAppIcon(int)));
                appCount++;
                appCol++;

                if (appCol == 4)
                {
                    appCol = 0;
                    appRow++;
                }

                // add to app list
                appList.append(app);

                // appclass must design a appprocess interface
                //desktop visti

            }
    }





//    SetApp *w = new SetApp(this);
//    w->setAppDirName("AppNote");
//    w->setGeometry(32,20,80,90);
//    SetApp *a = new SetApp(this);
//    a->setAppDirName("AppMusicPlayer");
//    a->setGeometry(1*80+32*2,20,80,90);
//    SetApp *b = new SetApp(this);
//    b->setAppDirName("AppDownloadManger");
//    b->setGeometry(2*80+32*3,20,80,90);
//    SetApp *c = new SetApp(this);
//    c->setAppDirName("AppBrowser");
//    c->setGeometry(3*80+32*4,20,80,90);

//    connect(w,SIGNAL(showDesktopSignal()),this,SLOT(show()));
//    connect(w,SIGNAL(appExecSignal()),this,SLOT(hide()));


}

Desktop::~Desktop()
{
    delete ui;
}


void Desktop::startAppManager()
{
    qDebug() << "desktop manager";
    for(int i = 0; i < appList.size(); i++)
    {
        appList.at(i)->startAppManagerStatus();
    }
   // this->update();
}
void Desktop::stopAppManager()
{
    qDebug() << "desktop manager";
    for(int i = 0; i < appList.size(); i++)
    {
        appList.at(i)->stopAppManagerStatus();
    }
  //  this->update();
}
void Desktop::moveAppIcon(int x)
{
    for(int i = 0; i < appList.size(); i++)
    {
        appList.at(i)->move(appList.at(i)->x()+x,appList.at(i)->y());
    }
}
void Desktop::keyPressEvent ( QKeyEvent * event )
{
    switch(event->key())
    {
    case Qt::Key_Escape:
        stopAppManager();
        break;

    default:
        break;
    }

}

void Desktop::mouseMoveEvent ( QMouseEvent * event )
{
    int x = event->x() - mouseOldPosX;
    for(int i = 0; i < appList.size(); i++)
    {
        appList.at(i)->move(appList.at(i)->x()+x,appList.at(i)->y());
    }
    mouseOldPosX = event->x();
}

void Desktop::mousePressEvent ( QMouseEvent * event )
{
    mouseOldPosX = event->x();
}


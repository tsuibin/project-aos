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
    for( int i = 0; i < appDir.entryInfoList().size(); i++)
    {
        if ( appDir.entryInfoList().at(i).isDir())
            if( appDir.entryInfoList().at(i).fileName().left(3) == QString("App")
                    && appDir.entryInfoList().at(i).fileName().size() >= 4)
            {


                SetApp *w = new SetApp(this);
                w->setAppDirName( appDir.entryInfoList().at(i).fileName() );
                w->setGeometry(appCol*(80+32)+32,appRow*(90+32)+32,80,90);
                qDebug() << appDir.entryInfoList().at(i).fileName()
                         << "appCol" <<appCol
                         << "appRow" <<appRow;
                connect(w,SIGNAL(showDesktopSignal()),this,SLOT(show()));
                connect(w,SIGNAL(appExecSignal()),this,SLOT(hide()));

                appCount++;
                appCol++;

                if (appCol == 4)
                {
                    appCol = 0;
                    appRow++;
                }

                // add to app list

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

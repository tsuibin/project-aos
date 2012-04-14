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
    currentPage = 0;
    appManagerStatus = false;

    // 每行4个应用
    // 最多4行
    // 4行之后创建桌面的第二页
    int appRow = 0;
    int appCol = 0;
    int size =   (appDir.entryInfoList().size() <= 16) ? appDir.entryInfoList().size() : 16;
    int appPage = 0;
    size = 17;
    for( int i = 0; appCount < size; i++)
    {
        if ( appDir.entryInfoList().at(i).isDir())
            if( appDir.entryInfoList().at(i).fileName().left(3) == QString("App")
                    && appDir.entryInfoList().at(i).fileName().size() >= 4)
            {

                if(appCount != 0 && (appCount%16) == 0)
                {
                    qDebug() << "appCount" <<appCount
                             <<"appCount%16" <<appCount%16;
                    appPage++;
                    appRow = 0;
                    qDebug() << "16 +1" <<this->width();
                    qDebug() << appDir.entryInfoList().at(i).fileName();
                }


                SetApp *app = new SetApp(this);
                app->setAppDirName( appDir.entryInfoList().at(i).fileName() );
                app->setGeometry(appCol*(80+32)+32 + (appPage*480),appRow*(90+24)+24,80,90);
                /*
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


    //page tips label
    label_Page = new QLabel(this);
    label_Page->setObjectName(QString::fromUtf8("label_Page"));
    label_Page->setGeometry(QRect(0, 500, 480, 16));
    label_Page->setAlignment(Qt::AlignHCenter);
    label_Page->setText(QString::number(currentPage+1));
    label_Page->setStyleSheet("color:white");

    //page 0 search label
    qDebug() <<"this width" << this->width();
    QLabel* label_Search;
    label_Search = new QLabel(this);
    label_Search->setObjectName(QString::fromUtf8("label_Search"));
    label_Search->setGeometry(QRect(-480+10, 30, 60, 30));
    label_Search->setAlignment(Qt::AlignHCenter);
    label_Search->setText(QString::fromUtf8("Search"));
    label_Search->setStyleSheet("font :bold; color:white");

    QLineEdit *lineEdit_Search;
    lineEdit_Search = new QLineEdit(this);
    lineEdit_Search->setObjectName(QString::fromUtf8("lineEdit_Search"));
    lineEdit_Search->setGeometry(QRect(-480+70,32, 400, 30));

    desktopWidgetList << label_Search
                         <<lineEdit_Search;



}

Desktop::~Desktop()
{
    delete ui;
}


void Desktop::startAppManager()
{
    qDebug() << "desktop manager";
    appManagerStatus = true;
    for(int i = 0; i < appList.size(); i++)
    {
        appList.at(i)->startAppManagerStatus();
    }

}
void Desktop::stopAppManager()
{

    qDebug() << "desktop manager";
    if(appManagerStatus == true)
    {
        for(int i = 0; i < appList.size(); i++)
        {
            appList.at(i)->stopAppManagerStatus();
        }
        appManagerStatus = false;
    }

}
void Desktop::moveAppIcon(int x)
{

    for(int i = 0; i < appList.size(); i++)
    {
        appList.at(i)->move(appList.at(i)->x()+x,appList.at(i)->y());
    }

    for(int i = 0;i < desktopWidgetList.size(); i++)
    {
        desktopWidgetList.at(i)->move(desktopWidgetList.at(i)->x()+x,
                                      desktopWidgetList.at(i)->y());
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

    moveAppIcon(x);
    movingDistance += x;
    mouseOldPosX = event->x();
}

void Desktop::mousePressEvent ( QMouseEvent * event )
{
    movingDistance = 0;
    mouseOldPosX = event->x();
    desktopPosFlag = event->x();
}

void Desktop::mouseReleaseEvent ( QMouseEvent * event )
{
    qDebug() << "mouseOldPosX" <<mouseOldPosX
             <<"movingDistance"<<movingDistance
             << "desktopPosFlag"<<desktopPosFlag;
    //480/2 = 240

    pageDirection = 0;

    if (movingDistance > 200)
    {
        pageDirection = 1;
    }
    else if (movingDistance < (-200))
    {
        pageDirection = -1;
    }
    QString str = (movingDistance < (-200) ) ? "true":"false";
    qDebug() << str;


        automaticPage(pageDirection);


}

void Desktop::automaticPage(int direction)
{
    qDebug()<<"direction"<<direction;
    switch(direction)
    {
    case 1:
        previousPage();
        break;
    case -1:
        nextPage();
        break;
    case 0:
        returnCurrentPage();
        break;
    default:
        break;

    }

}

void Desktop::returnCurrentPage()
{

    qDebug() << "returnCurrentPage" << currentPage;
    bool changeFlag = false;
    if(currentPage < 0)
    {
        currentPage = (-currentPage);
        changeFlag = true;
    }

    if (appList.size() > 0)
    {
        int tmp = appList.first()->x() - (32 +(currentPage*480));//512
        qDebug() << "appList.first()->x()" <<appList.first()->x();

        qDebug() <<"tmp" << tmp;
        if(tmp == 0)
            return;

        if(tmp > 0)
        {
            for(int i = 0;i < tmp;i++)
            {
                moveAppIcon(-1);
            }
        }else{
            for(int i = 0;i > tmp;i--)
            {
                moveAppIcon(1);
            }
        }
    }

    if(changeFlag == true)
    {
        currentPage = (-currentPage);
    }

}
void Desktop::checkMoveAppIcon()
{

}
void Desktop::previousPage()
{
    currentPage--;
    qDebug() << "currentPage" <<currentPage;

    //x == 32+480
    //x = 512

    if (appList.size() > 0)
    {
        int tmp = appList.first()->x() + ((currentPage * 480)-32);

        if(tmp == 0)
            return;

        if(tmp > 0)
        {
            for(int i = 0;i < tmp;i++)
            {
                moveAppIcon(-1);
            }
        }else{
            for(int i = 0;i > tmp;i--)
            {
                moveAppIcon(1);
            }
        }
    }
    label_Page->setText(QString::number(currentPage+1));
}

void Desktop::nextPage()
{
    currentPage++;
    qDebug() <<"currentPage" <<currentPage << appList.first()->x();

    if (appList.size() > 0)
    {
        int tmp = appList.first()->x() + ((currentPage * 480)-32);

        if(tmp == 0)
            return;

        if(tmp > 0)
        {
            for(int i = 0;i < tmp;i++)
            {
                moveAppIcon(-1);
            }
        }else{
            for(int i = 0;i > tmp;i--)
            {
                moveAppIcon(1);
            }
        }
    }

    qDebug() << "appList.first()->x()" <<appList.first()->x();
    label_Page->setText(QString::number(currentPage+1));
}

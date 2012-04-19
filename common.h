#ifndef COMMON_H
#define COMMON_H

#include <QtGui/QApplication>
#include <QtCore>
#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QBitmap>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QPalette>
#include <QProcess>
#include <QDir>
#include <QFileInfoList>
#include <QTimer>
#include <QList>
#include <QPixmap>
#include <QLineEdit>
#include <QGLWidget>
#include <QRunnable>
#include <QThread>



#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <time.h>



#define qDebug() qDebug() << __FILE__ << __LINE__


#endif // COMMON_H

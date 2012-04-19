#-------------------------------------------------
#
# Project created by QtCreator 2012-04-10T14:20:02
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = aos
TEMPLATE = app


SOURCES += main.cpp\
    desktop.cpp \
    globalkeyboardevent.cpp \
    setapp.cpp

HEADERS  += \
    common.h \
    desktop.h \
    globalkeyboardevent.h \
    setapp.h

FORMS    += \
    desktop.ui \
    test.ui

OTHER_FILES += \
    README.txt

RESOURCES += \
    aosres.qrc

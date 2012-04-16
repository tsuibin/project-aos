#-------------------------------------------------
#
# Project created by QtCreator 2012-04-10T14:20:02
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = aos
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    desktop.cpp

HEADERS  += widget.h \
    common.h \
    desktop.h

FORMS    += \
    desktop.ui \
    test.ui

OTHER_FILES += \
    README.txt

RESOURCES += \
    aosres.qrc

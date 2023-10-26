QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/launch.cpp \
    src/output.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/colorselector.cpp \
    src/pixelblock.cpp \
    src/mygraphicsview.cpp \
    src/canvas.cpp \
    src/file.cpp \
    src/favoratecolor.cpp

HEADERS += \
    inc/global_def.h \
    src/launch.h \
    src/output.h \
    src/mainwindow.h \
    src/colorselector.h \
    src/pixelblock.h \
    src/mygraphicsview.h \
    src/canvas.h \
    src/file.h \
    src/favoratecolor.h

FORMS += \
    ui/launch.ui \
    ui/output.ui \
    ui/mainwindow.ui

TRANSLATIONS += \
    xPixelx_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    logo.rc

RC_FILE += \
    logo.rc
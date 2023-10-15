QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/colorselector.cpp \
    src/imageblock.cpp \
    src/pixelblock.cpp \
    src/mygraphicsview.cpp \
    src/canvas.cpp

HEADERS += \
    inc/global_def.h \
    src/mainwindow.h \
    src/colorselector.h \
    src/imageblock.h \
    src/pixelblock.h \
    src/mygraphicsview.h \
    src/canvas.h

FORMS += \
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

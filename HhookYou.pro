QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    opencv_thread.cpp

HEADERS += \
    mainwindow.h \
    opencv_thread.h
win32 {
        LIBS += -luser32
    }




INCLUDEPATH +=E:\OpenCV-4.10.0\build\include  \
              E:\OpenCV-4.10.0\build\include\opencv \
              E:\OpenCV-4.10.0\build\include\opencv2

CONFIG(debug, debug|release): {

        LIBS += E:\OpenCV-4.10.0\build\x64\mingw\lib\libopencv_*d.dll.a
        }

        else:CONFIG(release, debug|release): {

        LIBS += E:\OpenCV-4.10.0\build\x64\mingw\lib\libopencv_*.dll.a

        }
FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    HhookYou_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pic.qrc

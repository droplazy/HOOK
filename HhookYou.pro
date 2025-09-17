QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    display_widget.cpp \
    event_pthread.cpp \
    httpclient.cpp \
    main.cpp \
    mainwindow.cpp \
    opencv_utils.cpp

HEADERS += \
    ProDefine.h \
    display_widget.h \
    event_pthread.h \
    httpclient.h \
    mainwindow.h \
    opencv_utils.h
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
    display_widget.ui \
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

DISTFILES += \
    Element/QingLong/CNW.png \
    Element/QingLong/CSCCZ.png \
    Element/QingLong/CYW.png \
    Element/QingLong/Completed.png \
    Element/QingLong/DYLZ_O.png \
    Element/QingLong/FW_O.png \
    Element/QingLong/GetNPC.png \
    Element/QingLong/JM.png \
    Element/QingLong/KQH_O.png \
    Element/QingLong/LH.png \
    Element/QingLong/LLD.png \
    Element/QingLong/LR_O.png \
    Element/QingLong/LST.png \
    Element/QingLong/MQY.png \
    Element/QingLong/MRXS.png \
    Element/QingLong/Object.png \
    Element/QingLong/QingLongMenu.png \
    Element/QingLong/SH_O.png \
    Element/QingLong/WDS.png \
    Element/QingLong/WFR.png \
    Element/QingLong/WJR.png \
    Element/QingLong/XBLB.png \
    Element/QingLong/XH.png \
    Element/QingLong/XSCH.png \
    Element/QingLong/YKS.png \
    Element/QingLong/ZLF.png \
    Element/QingLong/ZYB.png \
    Element/QingLong/xsch_o.png

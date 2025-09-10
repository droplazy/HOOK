#include "opencv_thread.h"
#include <QApplication>
#include <QScreen>
#include <QStandardPaths>
opencv_thread::opencv_thread()
{
    ZeroPos.setX(0);
    ZeroPos.setY(0);
}

void opencv_thread::run()
{
    while(1)
    {
        if(startDispose)
        {
            disposeIMGformessage();
        }
        usleep(200*1000);
    }

}
void opencv_thread::captureScreenAndDisplay(const QRect &rect)
{

    // 获取主屏幕截图
    QScreen *screen = QApplication::primaryScreen();
    if (!screen) {
        qWarning() << "无法获取屏幕";
        return;
    }

    // 截取指定区域的截图
    QPixmap pixmap = screen->grabWindow(0, rect.x(), rect.y(), rect.width(), rect.height());

    // 将 QPixmap 转换为 QImage
    QImage image = pixmap.toImage();
    if (image.isNull()) {
        qWarning() << "截图转换为QImage失败";
        return;
    }
    emit getPic(image);
    qDebug() <<"init ...";

}
void opencv_thread::disposeIMGformessage()
{
    QRect rect;
   // rect.setRect(ZeroPos.x()+(20-20)*SCALE_FLOAT,ZeroPos.y()+(130-90)*SCALE_FLOAT,90*SCALE_FLOAT,80*SCALE_FLOAT);
    rect.setRect(ZeroPos.x()+(20-20)*SCALE_FLOAT,\
                ZeroPos.y()+(130-90)*SCALE_FLOAT-15,\
                 320,260);
// 90*SCALE_FLOAT,80*SCALE_FLOAT);
    captureScreenAndDisplay(rect);
}

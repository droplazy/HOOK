#include <QApplication>
#include <QMessageBox>
#include <Windows.h>
#include <QString>

#include <QWidget>
#include "mainwindow.h"

/*

// 自定义透明窗口类，重写绘制函数
class TransparentWindow : public QWidget
{
public:
    TransparentWindow() {
        setWindowTitle("Mouse Click Red Dot");
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
        setAttribute(Qt::WA_TranslucentBackground);  // 设置窗口透明

        // 获取所有屏幕的总区域
        QRect totalGeometry;
        for (const auto& screen : QApplication::screens()) {
            totalGeometry |= screen->geometry();
        }

        // 设置窗口为跨多个屏幕的全屏
        setGeometry(totalGeometry);
        installMouseHook();  // 安装鼠标钩子

        // 启动定时器，10秒后退出程序
      //  QTimer::singleShot(10000, this, &TransparentWindow::closeApp);

        // 自动将鼠标移到指定位置 (例如：屏幕中心)
        moveMouseAndClick(422, 453);  // 可以根据需要修改目标位置
    }

protected://画家会影响双击
    void paintEvent(QPaintEvent* event) override {
        // QPainter painter(this);
        // painter.setBrush(Qt::red);
        // painter.setPen(Qt::NoPen);

        // // 绘制每一个点击位置（转换为窗口坐标）
        // for (const QPoint& pos : clickPositions) {
        //     // 将屏幕坐标转换为窗口坐标
        //     QPoint windowPos = mapFromGlobal(pos);  // 将屏幕坐标转换为窗口坐标
        //     painter.drawEllipse(windowPos, 5, 5);  // 半径5的红点
        // }
    }

    void closeEvent(QCloseEvent* event) override {
        removeMouseHook();  // 移除钩子
        QWidget::closeEvent(event);
    }

private:
    // 关闭程序
    void closeApp() {
        if (!appExit) {
            qDebug() << "Automatically closing application after 10 seconds...";
            appExit = true;
            close();
        }
    }
};
*/

bool isRunningAsAdmin()
{
    BOOL isAdmin = FALSE;
    PSID AdministratorsGroup = NULL;
    SID_IDENTIFIER_AUTHORITY ntAuthority = SECURITY_NT_AUTHORITY;

    // 创建管理员组的 SID
    if (AllocateAndInitializeSid(&ntAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &AdministratorsGroup)) {
        // 检查当前进程是否属于管理员组
        CheckTokenMembership(NULL, AdministratorsGroup, &isAdmin);
        FreeSid(AdministratorsGroup);
    }

    return isAdmin == TRUE;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 创建并显示全屏透明窗口
    // TransparentWindow window;
    // window.show();
    if (!isRunningAsAdmin()) {
        QMessageBox::warning(nullptr, "权限不足", "程序未以管理员权限运行。");
        //return -1;  // 不继续运行程序
    }

    MainWindow w;
    w.show();
    // 启动事件循环
    int ret = a.exec();

    return ret;
}

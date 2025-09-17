
#include <Windows.h>//必须位于OPENCV上
#include "event_pthread.h"
#include "opencv_utils.h"
#include <QDebug>
#include <QMap>




event_pthread::event_pthread(QObject *parent)
    : QThread(parent), currentState(Task_State::MOUSER_OFFSET)  // 默认状态为 IDLE
{
#if 1
    QTimer *timer_msr = new QTimer(this);
    //connect(timer_msr, &QTimer::timeout, this, SLOT(MoveMouserToTarget()));
    timer_msr->start(10);
#endif
}
int printKeyUsingWindowsAPI( ) {
    // 打印出按下的键（使用 GetAsyncKeyState 或 GetKeyState）
    // 这里我们使用 GetAsyncKeyState 来检查按键是否被按下
    for (int i = 0; i < 256; ++i) {
        if (GetAsyncKeyState(i) & 0x8000) { // 检查该按键是否被按下
            //qDebug() << "Windows API Key Pressed:" << i;
            return i;
        }
    }
}
void event_pthread::run()
{
    while (!isInterruptionRequested()) // 检查线程是否请求中断
    {



        if(!IsCorrectScreen())
            continue;

        GetCharacterForTess();

        switch (currentState) {
        case Task_State::MOUSER_OFFSET:
            CheckMouserOffset();
            break;
        case Task_State::QINGLONG:
            QingLongTask();
            sleep(10);
            break;
        case Task_State::XUANWU:
           // qDebug() << "State is XUANqU";
            // 执行与 XUANWU 状态相关的操作
            break;
        case Task_State::ZHUQUE:
           // qDebug() << "State is ZHUQUE";
            // 执行与 ZHUQUE 状态相关的操作
            break;
        case Task_State::SHIMEN:
           // qDebug() << "State is SHIMEN";
            // 执行与 SHIMEN 状态相关的操作
            break;
        case Task_State::IDLE:
           // qDebug() << "State is IDLE";
            GetIdleImage();
            break;
        default:
           // qDebug() << "Unknown state!";
            break;
        }

        // 模拟一些需要定时处理的任务，比如等待一段时间
        // if(printKeyUsingWindowsAPI() == 123)

        // QCoreApplication::quit();

        QThread::msleep(350);  // 让线程休眠一秒，防止占用过多CPU资源
    }
}
#include <QElapsedTimer>

bool event_pthread::IsCorrectScreen()
{
    return (std::abs(EndPos.x() - ZeroPos.x()) > 100 && std::abs(EndPos.y() - ZeroPos.y()) > 100);
}

void event_pthread::GetGameScreen()
{
    QRect captureRect(ZeroPos.x(), ZeroPos.y(),EndPos.x()-ZeroPos.x(),EndPos.y()- ZeroPos.y());  // 设置需要截取的位置和宽高
    QImage img = opencv_utils::captureScreenQimage(captureRect);
    if (streamOn) {
        // 发送 img 图像
        emit getPic(img.copy());
        qDebug() << "Sending image with dimensions: " << img.width() << "x" << img.height();
    }
}

void event_pthread::MoveMouseQinglongNPC()
{

    QImage qImage(":/Element/QingLong/GetNPC.png");

    PessF9();
    QRect matchRect;

    TargetClick =  findElemntForScreen(qImage,matchRect);//目标坐标
    MouseNeedMove = true;
    while (MouseNeedMove) {
        usleep(1000);
    }
    qDebug() <<"First Move Compeleted ....";

    QImage tmpPic =  opencv_utils::captureScreenQimage(matchRect);
    // 将图片保存到 C:\Users\KANDAGAWA\Desktop\DEBUG 文件夹
    QString savePath = "C:/Users/KANDAGAWA/Desktop/DEBUG/tmpPic.png";  // 设置保存路径
    if (tmpPic.save(savePath)) {
        qDebug() << "图片成功保存到：" << savePath;
    } else {
        qDebug() << "保存图片失败！";
    }


    QImage m_Image(":/Element/Mouser.png");
    QPoint UI_ZeroP (matchRect.x(),matchRect.y());
    QPoint uiPos =  findElemntForUI(tmpPic,m_Image,UI_ZeroP);//UI鼠标的坐标
    qDebug() << "THE NPC POSTION IS :" << TargetClick;
    qDebug() << "THE offset MOUSER POSTION IS :" << uiPos;

    // 计算偏移量：TargetClick - uiPos
    QPoint offset = TargetClick - uiPos;

    // 输出偏移量
    qDebug() << "The offset is: " << offset;

    // 更新 TargetClick，添加偏移量
    TargetClick += offset;

    qDebug() << "New TargetClick after applying offset: " << TargetClick;
//获得新的目标坐标  并继续移动鼠标

    qDebug() <<"Readt to Move ....";
    sleep(2);
    MouseNeedMove = true;
    while (MouseNeedMove) {
        usleep(1000);
    }
    qDebug() << "现在看看对了没...";
    POINT currentPos;
    qDebug() << "Maybe The mouser IS arrived!";
    if (GetCursorPos(&currentPos)) {
        // 打印当前位置
        qDebug() << "\rCurrent mouse position:" << QPoint(currentPos.x, currentPos.y);
        qDebug() << "\rTarget mouse position:" << TargetClick;
    }



   // moveMouseAndClick(TargetClick.x(),TargetClick.y(),"left");

}
void event_pthread::CheckMouserOffset()
{
    QPoint center_point;
    QImage img= GetGamewindowCenterPoint(center_point);
    if (streamOn) {
        // 发送 img 图像
        emit getPic(img.copy());
        //  qDebug() << "Sending image with dimensions: " << img.width() << "x" << img.height();
    }
    QPoint screnen_point;
    screnen_point = convertCoordinates(ZeroPos, center_point);
    qDebug() << "screnen_point" <<screnen_point;
    TargetClick =  screnen_point;//目标坐标
    TargetClick.setX(TargetClick.x());
    TargetClick.setY(TargetClick.y());
    screnen_point =TargetClick;
    MouseNeedMove = true;
    while (MouseNeedMove) {
        usleep(1000);
    }
    qDebug() <<"First Move Compeleted ....";

    int rectSize = 200;
    int left = screnen_point.x() -250;
    int top = screnen_point.y() - 0;
   // int right = center_point.x() + rectSize / 2;
   // int bottom = center_point.y() + rectSize / 2;
    QPoint topLeft(left, top);
    qDebug() << "Top-left corner: " << topLeft;
    // 创建 QRect 对象
    QRect captureRect(left, top, 100, 200);
    QImage img_center =opencv_utils::captureScreenQimage(captureRect);
    QImage m_Image(":/Element/Mouser.png");
    QPoint UI_ZeroP (topLeft.x(),topLeft.y());
    QPoint uiPos =  findElemntForUI(img_center,m_Image,UI_ZeroP);//UI鼠标的坐标
    qDebug() << "THE NPC POSTION IS :" << TargetClick;
    qDebug() << "THE offset MOUSER POSTION IS :" << uiPos;
 /*
    QImage qImage(":/Element/MHJL.png");

    PessF9();
    QRect matchRect;

    TargetClick =  findElemntForScreen(qImage,matchRect);//目标坐标
    MouseNeedMove = true;
    while (MouseNeedMove) {
        usleep(1000);
    }
    qDebug() <<"First Move Compeleted ....";

    QImage tmpPic =  opencv_utils::captureScreenQimage(matchRect);
    // 将图片保存到 C:\Users\KANDAGAWA\Desktop\DEBUG 文件夹
    QString savePath = "C:/Users/KANDAGAWA/Desktop/DEBUG/tmpPic.png";  // 设置保存路径
    if (tmpPic.save(savePath)) {
        qDebug() << "图片成功保存到：" << savePath;
    } else {
        qDebug() << "保存图片失败！";
    }


    QImage m_Image(":/Element/Mouser.png");
    QPoint UI_ZeroP (matchRect.x(),matchRect.y());
    QPoint uiPos =  findElemntForUI(tmpPic,m_Image,UI_ZeroP);//UI鼠标的坐标
    qDebug() << "THE NPC POSTION IS :" << TargetClick;
    qDebug() << "THE offset MOUSER POSTION IS :" << uiPos;

    // 计算偏移量：TargetClick - uiPos
    QPoint offset = TargetClick - uiPos;

    // 输出偏移量
    qDebug() << "The offset is: " << offset;

    // 更新 TargetClick，添加偏移量
    TargetClick += (offset*MoveScale);

    qDebug() << "New TargetClick after applying offset: " << TargetClick;
    //获得新的目标坐标  并继续移动鼠标

    qDebug() <<"Readt to Move ....";
    sleep(5);
    MouseNeedMove = true;
    while (MouseNeedMove) {
        usleep(1000);
    }
    qDebug() << "现在看看对了没...";
    POINT currentPos;
    qDebug() << "Maybe The mouser IS arrived!";
    if (GetCursorPos(&currentPos)) {
        // 打印当前位置
        qDebug() << "\rCurrent mouse position:" << QPoint(currentPos.x, currentPos.y);
        qDebug() << "\rTarget mouse position:" << TargetClick;
    }

*/

}
void event_pthread::GetTaskStart()
{
    MoveMouseQinglongNPC();
}
void event_pthread::SetMouserOffset()
{

}
/*
 *  moveMouseAndClick(TargetClick().x(),TargetClick().y(),"left");
qImage.load(":/Element/QingLong/QingLongMenu.png");


npc_pos =  findElemntForScreen(qImage);

moveMouseAndClick(npc_pos.x(),npc_pos.y(),"left");*/
void event_pthread::QingLongTask()
{
    GetTaskStart();
}
QImage event_pthread::GetGamewindowCenterPoint(QPoint& point)
{
    // 捕获游戏窗口图像
    cv::Mat targetImg = opencv_utils::captureGameWindow();

    // 获取图像的中心点
    int centerX = targetImg.cols / 2;
    int centerY = targetImg.rows / 2;

    // 在图像的中心绘制一个红色圆点
    cv::circle(targetImg, cv::Point(centerX, centerY), 10, cv::Scalar(0, 0, 255), -1); // 红色圆点，半径 10

    // 更新传入的 point 参数为圆点坐标
    point = QPoint(centerX, centerY);

    // 将 cv::Mat 转换为 QImage
    // 注意：OpenCV 使用的是 BGR 色彩模式，而 QImage 使用 RGB，所以需要转换
    QImage img(targetImg.data, targetImg.cols, targetImg.rows, targetImg.step, QImage::Format_RGB888);

    // 由于 OpenCV 使用 BGR 格式，需转换为 RGB 格式
    img = img.rgbSwapped();

    // 返回修改后的图像
    return img;
}

QPoint event_pthread::findElemntForScreen(QImage image, QRect &rectoffset)
{
    cv::Mat targetImg = opencv_utils::captureGameWindow();

    // 从资源路径加载图片

    //QImage qImage(":/Element/QingLong/GetNPC.png");

    // 将 QImage 转换为 cv::Mat
    cv::Mat posText = opencv_utils::QImageToMat(image);  // 假设你已经实现了 QImageToMat 函数

    // 开始计时
    QElapsedTimer timer;
    timer.start();

    // 执行 FindPicTarget 接口
    QPoint getPoint;
    //QRect matchRect;
    QImage img = opencv_utils::FindPicTarget(targetImg, posText,getPoint,rectoffset,ZeroPos);//第一次用整体界面坐标作为归零点
    //qDebug() << "NPC在屏幕的坐标: (" << getPoint.x() << ", " << getPoint.y() << ")";
    // qDebug() << "画布坐标: (" << ZeroPos.x() << ", " << ZeroPos.y() << ")" <<"画布大小 :" <<EndPos.x()-ZeroPos.x() <<" X" <<EndPos.y()- ZeroPos.y();

    // 计算耗时
    //qint64 elapsed = timer.elapsed();  // 获取执行时间（单位：毫秒）

    // 输出耗时
    //qDebug() << "FindPicTarget executed in" << elapsed << "milliseconds";

    // 检查 streamOn 是否为 true，并发送图像
    if (streamOn) {
        // 发送 img 图像
        emit getPic(img.copy());
      //  qDebug() << "Sending image with dimensions: " << img.width() << "x" << img.height();
    }
    return getPoint;
}
QPoint event_pthread::findElemntForUI(QImage image,QImage image_UI,QPoint zeroP)
{
    // 将 QImage 转换为 cv::Mat
    cv::Mat TargetUI = opencv_utils::QImageToMat(image);  // 假设你已经实现了 QImageToMat 函数
    // 将 QImage 转换为 cv::Mat
    cv::Mat posText = opencv_utils::QImageToMat( image_UI);  // 假设你已经实现了 QImageToMat 函数

    // 开始计时
    // QElapsedTimer timer;
    // timer.start();

    // 执行 FindPicTarget 接口
    QPoint getPoint;
    QRect matchRect;

    QImage img = opencv_utils::FindPicTarget(TargetUI, posText, getPoint, matchRect,zeroP);


    QString savePath = "C:/Users/KANDAGAWA/Desktop/DEBUG/output_image.png";  // 设置保存路径
    if (img.save(savePath)) {
        qDebug() << "图片成功保存到：" << savePath;
    } else {
        qDebug() << "保存图片失败！";
    }

    return getPoint;

}
void event_pthread::GetIdleImage()
{
    //opencv_utils::disposeIMGformessage();
    if(!IsCorrectScreen())
        return ;
    //获得IMG 格式的窗口
    GetGameScreen();

}
void event_pthread::GetCharacterForTess()
{
   // qDebug() << "ZeroPos: (" << ZeroPos.x() << "," << ZeroPos.y() << ")";
   // qDebug() << "EndPos: (" << EndPos.x() << "," << EndPos.y() << ")";

    // cv::Mat targetImg = captureGameWindow();
    //  cv::Mat templateImg =capturePosition();

   // qDebug() << "****************************************************";
    QRect rect(+53,+207,138,20);
    cv::Mat posText = opencv_utils::capturePositionForRect(rect);
    QString position=opencv_utils::recognizeTextFromMat(posText,OCR_ENGLISH);

    rect.setRect(+45,+116,115,35);
    posText = opencv_utils::capturePositionForRect(rect);
    QString location =   opencv_utils::recognizeTextFromMat(posText,OCR_CHINESE_SIMPLE);
    QString result = findMostSimilarLocation(location, dreamWorldLocations);

    //qDebug()<< "最相似的地名是: " << result << "OCR:"<<position;
    t_loaction = result;
    t_position = position;
 //   return ("location"+result+"pos:"+position);
}

void event_pthread::GameopenTaskMenu()
{
    //holdKey1();
    pressKey("alt");
    QThread::msleep(50);
    pressKey("q");
    QThread::msleep(50);
    releaseKey("q");
    QThread::msleep(50);
    releaseKey("alt");
}

void event_pthread::GameGiveObject()
{
    //holdKey1();
    pressKey("alt");
    QThread::msleep(50);
    pressKey("g");
    QThread::msleep(50);
    releaseKey("g");
    QThread::msleep(50);
    releaseKey("alt");
}
void event_pthread::GameAttack()
{
    //holdKey1();
    pressKey("alt");
    QThread::msleep(50);
    pressKey("a");
    QThread::msleep(50);
    releaseKey("a");
    QThread::msleep(50);
    releaseKey("alt");
}
void event_pthread::GameOpenInventoryMenu()
{
    //holdKey1();
    pressKey("alt");
    QThread::msleep(50);
    pressKey("e");
    QThread::msleep(50);
    releaseKey("e");
    QThread::msleep(50);
    releaseKey("alt");
}
void event_pthread::GameGroup()
{
    //holdKey1();
    pressKey("alt");
    QThread::msleep(50);
    pressKey("t");
    QThread::msleep(50);
    releaseKey("t");
    QThread::msleep(50);
    releaseKey("alt");
}
void event_pthread::PessF9()
{
    //holdKey1();
    pressKey("F9");
    QThread::msleep(50);
    releaseKey("F9");
    QThread::msleep(50);
}
void event_pthread::GetCharacterPostion()
{
    QRect rect(+53,+207,138,20);
    cv::Mat posText = opencv_utils::capturePositionForRect(rect);
    //QString position=recognizeTextFromMat(posText,OCR_ENGLISH);
    QString base64pic=  opencv_utils::recognizeTextFromMatBackBase(posText);
    // qDebug() << "**************************************\n";
    // qDebug() << base64pic;
    // qDebug() << "**************************************\n";
    emit regnize(base64pic);
}
void event_pthread::GetCharacterLocation()
{

    QRect rect(+45,+120,115,30);
    cv::Mat posText = opencv_utils::capturePositionForRect(rect);
    //QString position=recognizeTextFromMat(posText,OCR_ENGLISH);
    QString base64pic=  opencv_utils::recognizeTextFromMatBackBase(posText);
    // qDebug() << "**************************************\n";
    // qDebug() << base64pic;
    // qDebug() << "**************************************\n";
    emit regnize(base64pic);
}
void event_pthread::GetCharacterlocInfo()
{

    GetCharacterLocation();
    GetCharacterPostion();
}


void event_pthread::setState(Task_State state)
{
    currentState = state;
}

Task_State event_pthread::getState() const
{
    return currentState;
}

void pressKey(const QString& key) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;

    // 将输入的键转换为小写，避免区分大小写
    QString lowerKey = key.toLower();

    // 字母 a~z 和 数字 1~9 键映射
    QMap<QString, WORD> keyMap = {
        {"a", 0x41}, {"b", 0x42}, {"c", 0x43}, {"d", 0x44}, {"e", 0x45}, {"f", 0x46},
        {"g", 0x47}, {"h", 0x48}, {"i", 0x49}, {"j", 0x4A}, {"k", 0x4B}, {"l", 0x4C},
        {"m", 0x4D}, {"n", 0x4E}, {"o", 0x4F}, {"p", 0x50}, {"q", 0x51}, {"r", 0x52},
        {"s", 0x53}, {"t", 0x54}, {"u", 0x55}, {"v", 0x56}, {"w", 0x57}, {"x", 0x58},
        {"y", 0x59}, {"z", 0x5A}, {"1", 0x31}, {"2", 0x32}, {"3", 0x33}, {"4", 0x34},
        {"5", 0x35}, {"6", 0x36}, {"7", 0x37}, {"8", 0x38}, {"9", 0x39}, {"0", 0x30}
    };

    // 功能键 F1~F12 键映射
    QMap<QString, WORD> fKeyMap = {
        {"f1", VK_F1}, {"f2", VK_F2}, {"f3", VK_F3}, {"f4", VK_F4}, {"f5", VK_F5},
        {"f6", VK_F6}, {"f7", VK_F7}, {"f8", VK_F8}, {"f9", VK_F9}, {"f10", VK_F10},
        {"f11", VK_F11}, {"f12", VK_F12}
    };

    // 特殊键：ALT, SHIFT, CTRL, BACKSPACE
    QMap<QString, WORD> specialKeyMap = {
        {"alt", VK_MENU}, {"shift", VK_SHIFT}, {"ctrl", VK_CONTROL}, {"backspace", VK_BACK}
    };

    // 如果是单个键，直接处理
    if (keyMap.contains(lowerKey)) {
        input.ki.wVk = keyMap[lowerKey];
        input.ki.dwFlags = 0;  // 按下事件
        SendInput(1, &input, sizeof(INPUT));  // 发送按下事件
        qDebug() << "Pressed" << key << "key...";  // 输出调试信息
    }
    else if (fKeyMap.contains(lowerKey)) {
        input.ki.wVk = fKeyMap[lowerKey];
        input.ki.dwFlags = 0;  // 按下事件
        SendInput(1, &input, sizeof(INPUT));  // 发送按下事件
        qDebug() << "Pressed" << key << "key...";  // 输出调试信息
    }
    else if (specialKeyMap.contains(lowerKey)) {
        input.ki.wVk = specialKeyMap[lowerKey];
        input.ki.dwFlags = 0;    // 按下事件
        SendInput(1, &input, sizeof(INPUT));  // 发送按下事件
        qDebug() << "Pressed" << key << "key...";  // 输出调试信息
    }
    else {
        qDebug() << "Invalid key specified!";
    }
}

void releaseKey(const QString& key) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;

    // 将输入的键转换为小写，避免区分大小写
    QString lowerKey = key.toLower();

    // 字母 a~z 和 数字 1~9 键映射
    QMap<QString, WORD> keyMap = {
        {"a", 0x41}, {"b", 0x42}, {"c", 0x43}, {"d", 0x44}, {"e", 0x45}, {"f", 0x46},
        {"g", 0x47}, {"h", 0x48}, {"i", 0x49}, {"j", 0x4A}, {"k", 0x4B}, {"l", 0x4C},
        {"m", 0x4D}, {"n", 0x4E}, {"o", 0x4F}, {"p", 0x50}, {"q", 0x51}, {"r", 0x52},
        {"s", 0x53}, {"t", 0x54}, {"u", 0x55}, {"v", 0x56}, {"w", 0x57}, {"x", 0x58},
        {"y", 0x59}, {"z", 0x5A}, {"1", 0x31}, {"2", 0x32}, {"3", 0x33}, {"4", 0x34},
        {"5", 0x35}, {"6", 0x36}, {"7", 0x37}, {"8", 0x38}, {"9", 0x39}, {"0", 0x30}
    };

    // 功能键 F1~F12 键映射
    QMap<QString, WORD> fKeyMap = {
        {"f1", VK_F1}, {"f2", VK_F2}, {"f3", VK_F3}, {"f4", VK_F4}, {"f5", VK_F5},
        {"f6", VK_F6}, {"f7", VK_F7}, {"f8", VK_F8}, {"f9", VK_F9}, {"f10", VK_F10},
        {"f11", VK_F11}, {"f12", VK_F12}
    };

    // 特殊键：ALT, SHIFT, CTRL, BACKSPACE
    QMap<QString, WORD> specialKeyMap = {
        {"alt", VK_MENU}, {"shift", VK_SHIFT}, {"ctrl", VK_CONTROL}, {"backspace", VK_BACK}
    };

    // 如果是单个键，直接处理
    if (keyMap.contains(lowerKey)) {
        input.ki.wVk = keyMap[lowerKey];
        input.ki.dwFlags = KEYEVENTF_KEYUP;  // 松开事件
        SendInput(1, &input, sizeof(INPUT));  // 发送松开事件
        qDebug() << "Released" << key << "key.";  // 输出调试信息
    }
    else if (fKeyMap.contains(lowerKey)) {
        input.ki.wVk = fKeyMap[lowerKey];
        input.ki.dwFlags = KEYEVENTF_KEYUP;  // 松开事件
        SendInput(1, &input, sizeof(INPUT));  // 发送松开事件
        qDebug() << "Released" << key << "key.";  // 输出调试信息
    }
    else if (specialKeyMap.contains(lowerKey)) {
        input.ki.wVk = specialKeyMap[lowerKey];
        input.ki.dwFlags = KEYEVENTF_KEYUP;    // 松开事件
        SendInput(1, &input, sizeof(INPUT));  // 发送松开事件
        qDebug() << "Released" << key << "key.";  // 输出调试信息
    }
    else {
        qDebug() << "Invalid key specified!";
    }
}
// 坐标转换函数
QPoint convertCoordinates(const QPoint& canvasOffset, const QPoint& targetCenter) {
    // canvasOffset: 画布相对于屏幕的偏移坐标 (canvasX, canvasY)
    // targetCenter: 目标图像中的匹配中心坐标 (targetX, targetY)

    // 计算匹配中心在屏幕中的坐标
    int screenX = canvasOffset.x() + targetCenter.x();
    int screenY = canvasOffset.y() + targetCenter.y();

    // 返回转换后的屏幕坐标
    return QPoint(screenX, screenY);
}

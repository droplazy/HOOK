
#include <Windows.h>//必须位于OPENCV上
#include "event_pthread.h"
#include "opencv_utils.h"
#include <QDebug>
#include <QMap>




event_pthread::event_pthread(QObject *parent)
    : QThread(parent), currentState(Task_State::IDLE)  // 默认状态为 IDLE
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
    return -1 ;
}

//QPoint lastMousePos = QPoint(-1, -1); // 初始时设置为一个无效值

// void IsMouseMoving()
// {
//     QPoint mousePos = QCursor::pos(); // 获取当前鼠标坐标

//     // 判断鼠标是否在移动
//     if (mousePos != lastMousePos) {
//         // 如果当前坐标与上一次坐标不同，说明鼠标在移动
//         qDebug() << "Mouse is moving. Current position:" << mousePos;

//         // 更新上一次的鼠标坐标
//         lastMousePos = mousePos;
//     } else {
//         // 鼠标没有移动
//         qDebug() << "Mouse is not moving.";
//     }
// }
void event_pthread::MovetoXIULIANNpc()
{
    PessF9();

    QImage qImage(":/Element/XIULIAN/GetNpc.png");
    MoveMouseSpeicefImg(qImage);
    setState(Task_State::IDLE);
}

void event_pthread::run()
{
    int samplecnt=0;


    while (!isInterruptionRequested()) // 检查线程是否请求中断
    {

        //qDebug() << MouseNeedMove << CheckUIMouserPos;

        if(!IsCorrectScreen())
            continue;
        if(MouseNeedMove)//鼠标移动中
        {

            continue;
        }
        if(CheckUIMouserPos)
        {
           // qDebug()<<"321";
            streamOn =true;
            QPoint uiPos =   FindUIMouserPos(UIImage);
            if(samplecnt++>=200)
            {
                if(M_score >=0.71)// 已经得到光标位置    将光标移动到图片点上
                {
                    qDebug() << "Ready to second Move for offset ....";
                    sleep(1);

                    CheckUIMouserPos= false;
                    TargetClick =TargetClick+ (TargetClick-uiPos);
                    TargetClick.setX(TargetClick.x() +5);
                    TargetClick.setY(TargetClick.y() +5);

                    MouseNeedMove = true;
                }
                else// 不能正确得到光标
                {
                     qDebug() << "不能正确获得光标位置";
                    // sleep(1);

                    // CheckUIMouserPos= false;
                    // TargetClick =TargetClick+ (TargetClick-uiPos);
                    // MouseNeedMove = true;

                }
                samplecnt =0;
            }
            qDebug() << "Timestamp:" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz")
                     << "samplecnt :" <<samplecnt       << "uipos:" << uiPos << "target :" << TargetClick << "对焦UI:"<<UIImage << "avrg:" <<M_score;             continue;

            continue ;
        }

        GetCharacterForTess();

        switch (currentState) {
        case Task_State::MOUSER_OFFSET:
            CheckMouserOffset();
            break;
        case Task_State::QINGLONG:
            QingLongTask();
            //sleep(10);
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
           // GetIdleImage();
           //ClacUIMouserPostion();
                       break;
        case Task_State::DIANXIU:
        MovetoXIULIANNpc();
           break;
        default:
           // qDebug() << "Unknown state!";
            break;
        }

        // 模拟一些需要定时处理的任务，比如等待一段时间
        // if(printKeyUsingWindowsAPI() == 123)

        // QCoreApplication::quit();

      //  QThread::msleep(1);  // 让线程休眠一秒，防止占用过多CPU资源
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
void event_pthread::MoveMouseSpeicefImg(QImage qImage)
{

    //QImage qImage(":/Element/QingLong/GetNPC.png");

    PessF9();
    QRect matchRect;

    TargetClick =  findElemntForScreen(qImage,matchRect);//目标坐标
    MouseNeedMove = true;
    UIImage =matchRect;

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


    TargetClick = TargetClick+  (t_offset*MoveScale);
    MouseNeedMove = true;
    while (MouseNeedMove) {
        usleep(1000);
    }
    qDebug() <<"First Move Compeleted ....";

    setState(Task_State::IDLE);
}
void event_pthread::MoveMouserToUI(QImage qImage)
{

   // QImage qImage(":/Element/MHJL.png");

    PessF9();
    QRect matchRect;

    QPoint point_t =  findElemntForScreen(qImage,matchRect);//目标坐标
    qDebug() << "The Setting Rect Center is : " << point_t;

    TargetClick = point_t;// findElemntForScreen(qImage,matchRect);//目标坐标
    MouseNeedMove = true;
    while (MouseNeedMove) {
        usleep(1000);
    }
    sleep(1);
    qDebug() <<"First Move Compeleted ....";

    QImage img_center =opencv_utils::captureScreenQimage(matchRect);
    QString savePath = "C:/Users/KANDAGAWA/Desktop/DEBUG/output_image_correct222.png";
    if (img_center.save(savePath)) {
        qDebug() << "图片成功保存到：" << savePath;
    } else {
        qDebug() << "保存图片失败！";
    }

    QImage m_Image(":/Element/Mouser.png");
    QPoint UI_ZeroP (matchRect.x(),matchRect.y());//归零点坐标
    double sorce;
    QPoint uiPos =  findElemntForUI(img_center,m_Image,UI_ZeroP,sorce);//UI鼠标的坐标
    qDebug()<<"Device POS:"<< TargetClick<<"UIpos:"<<uiPos;
    QPoint offset =TargetClick - uiPos;
    offset.setY(offset.y()+25);//UI自带的宽高
    offset.setX(offset.x()+15);
    TargetClick = TargetClick +offset;
    MouseNeedMove = true;
    while (MouseNeedMove) {
        usleep(1000);
    }
    sleep(1);
    double  score;
    uiPos =  findElemntForUI(img_center,m_Image,UI_ZeroP,score);//UI鼠标的坐标
    qDebug() <<"Second Move Compeleted ....";
    qDebug() <<"New UI pos : " << uiPos <<"The Center (Target) Pos:"<< point_t;



    img_center =opencv_utils::captureScreenQimage(matchRect);
    savePath = "C:/Users/KANDAGAWA/Desktop/DEBUG/output_image_correct333.png";
    if (img_center.save(savePath)) {
        qDebug() << "图片成功保存到：" << savePath;
    } else {
        qDebug() << "保存图片失败！";
    }

    t_offset = offset;
    // setState(Task_State::IDLE);

    MouseClick("right");

    setState(Task_State::IDLE);
}
QPoint event_pthread::FindUIMouserPos(QRect CorrectRect)
{
    QPoint curMouser = mousePos;

    static int cnt =1;
    static double t_score=0.5f;
    if(bZero)
    {
        t_score =0.5f;
        cnt =1;
        bZero=false;
    }

    // 矩形的宽度和高度
    int rectWidth = 130;
    int rectHeight = 130;

    // 判断 CorrectRect 是否是 (0, 0, 0, 0)
    QRect SearchRect;
    if (CorrectRect != QRect(0, 0, 0, 0)) {
        // 如果 CorrectRect 不是 (0, 0, 0, 0)，则使用 CorrectRect 作为 SearchRect
        CorrectRect =QRect(CorrectRect.x(),CorrectRect.y(),CorrectRect.width()+100,CorrectRect.height()+50);
        SearchRect = CorrectRect;
    } else {
        // 否则按原逻辑计算 SearchRect
        int x = curMouser.x() + 50 - rectWidth / 2;
        int y = curMouser.y() + 50 - rectHeight / 2;
        SearchRect = QRect(x, y, rectWidth, rectHeight);
    }

    QImage img_center = opencv_utils::captureScreenQimage(SearchRect);
    QString savePath = "C:/Users/KANDAGAWA/Desktop/DEBUG/output_image_correct999.png";
    if (img_center.save(savePath)) {
        // qDebug() << "图片成功保存到：" << savePath;
    } else {
        qDebug() << "保存图片失败！";
    }

    QPoint UI_ZeroP(SearchRect.x(), SearchRect.y()); // 归零点坐标

    QImage m_Image(":/Element/Mouser.png");
    double score;
    QPoint uiPos = findElemntForUI(img_center, m_Image, UI_ZeroP, score); // UI鼠标的坐标
    t_score +=score;
    M_score =(t_score) /++cnt;
    qDebug() << "Device POS:" << TargetClick << "UIpos:" << uiPos << "score:" << score << t_score<<cnt;

    // if(score > 0.7f)
    // {
    //     sleep(3);
    // }

    return uiPos;
}
void event_pthread::CheckMouserOffset()
{
    //pressKey()
    GameSetting();

    QImage qImage(":/Element/MHJL.png");

    PessF9();
    QRect matchRect;

    QPoint point_t =  findElemntForScreen(qImage,matchRect);//目标坐标
    qDebug() << "The Setting Rect Center is : " << point_t;

    TargetClick = point_t;// findElemntForScreen(qImage,matchRect);//目标坐标
    MouseNeedMove = true;
    while (MouseNeedMove) {
        usleep(1000);
    }
      sleep(1);
    qDebug() <<"First Move Compeleted ....";

      MouseNeedMove = true;
      while (MouseNeedMove) {
          usleep(1000);
      }
      sleep(1);
      qDebug() <<"First Move Compeleted ....";
    // matchRect.setX(matchRect.x()-100);
    // matchRect.setWidth(matchRect.width()+100);
    // matchRect.setHeight(matchRect.height()+100);

    QImage img_center =opencv_utils::captureScreenQimage(matchRect);
    QString savePath = "C:/Users/KANDAGAWA/Desktop/DEBUG/output_image_correct000.png";
    if (img_center.save(savePath)) {
        qDebug() << "图片成功保存到：" << savePath;
    } else {
        qDebug() << "保存图片失败！";
    }

    QImage m_Image(":/Element/Mouser.png");
    QPoint UI_ZeroP (matchRect.x(),matchRect.y());//归零点坐标
    double score;
    QPoint uiPos =  findElemntForUI(img_center,m_Image,UI_ZeroP,score);//UI鼠标的坐标
    qDebug()<<"Device POS:"<< TargetClick<<"UIpos:"<<uiPos;
    QPoint offset =TargetClick - uiPos;
    offset.setY(offset.y()+25);//UI自带的宽高
    offset.setX(offset.x()+15);
    TargetClick = TargetClick +offset;
    MouseNeedMove = true;
    while (MouseNeedMove) {
        usleep(1000);
    }
    sleep(1);
    uiPos =  findElemntForUI(img_center,m_Image,UI_ZeroP,score);//UI鼠标的坐标
    qDebug() <<"Second Move Compeleted ....";
    qDebug() <<"New UI pos : " << uiPos <<"The Center (Target) Pos:"<< point_t;



     img_center =opencv_utils::captureScreenQimage(matchRect);
     savePath = "C:/Users/KANDAGAWA/Desktop/DEBUG/output_image_correct111.png";
    if (img_center.save(savePath)) {
        qDebug() << "图片成功保存到：" << savePath;
    } else {
        qDebug() << "保存图片失败！";
    }

    t_offset = offset;
   // setState(Task_State::IDLE);

    MouseClick("right");

    setState(Task_State::XUANWU);
}
void event_pthread::GetTaskStart()
{
    MoveMouseQinglongNPC();
}
void event_pthread::SetMouserOffset()
{
    //  FindUIMouserPos();
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
    //QImage img_mask ;
    double score;
    QImage img = opencv_utils::FindPicTarget(targetImg, posText,getPoint,rectoffset,ZeroPos,score);//第一次用整体界面坐标作为归零点
    QString savePath = "C:/Users/KANDAGAWA/Desktop/DEBUG/output_image_correct_1.png";
    if (img.save(savePath)) {
        qDebug() << "图片成功保存到：" << savePath;
    } else {
        qDebug() << "保存图片失败！";
    }
    qDebug ()<< "score = " <<score;
    return getPoint;
}
QPoint event_pthread::findElemntForUI(QImage image, QImage image_UI, QPoint zeroP, double &score)
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


     //;
    QImage img = opencv_utils::FindPicTarget(TargetUI, posText, getPoint, matchRect,zeroP,score);

    //    QPoint center(ZeroPos.x() + 285, ZeroPos.y() + 500);
    if (streamOn) {
        // 发送 img 图像
        emit getPic(img.copy());
        //qDebug() << "Sending image with dimensions: " << img.width() << "x" << img.height();
    }
    QString savePath = "C:/Users/KANDAGAWA/Desktop/DEBUG/output_image.png";  // 设置保存路径
    if (img.save(savePath)) {
        qDebug() << "图片成功保存到：" << savePath;
    } else {
        qDebug() << "保存图片失败！";
    }

    return getPoint;

}

QPoint event_pthread::ClacUIMouserPostion()
{
    QPoint curMouser = mousePos;

    // 矩形的宽度和高度
    int rectWidth = 130;
    int rectHeight = 130;

    // 计算矩形左上角的坐标
    int x = curMouser.x() + 50 - rectWidth / 2;
    int y = curMouser.y() +50- rectHeight / 2;

    // 创建矩形
    QRect SearchRect(x, y, rectWidth, rectHeight);
    QImage RectImage =opencv_utils::captureScreenQimage(SearchRect);
    QImage mouse_Image(":/Element/Mouser.png");

    // 将 QImage 转换为 cv::Mat
    cv::Mat TargetUI = opencv_utils::QImageToMat(RectImage);  // 假设你已经实现了 QImageToMat 函数
    // 将 QImage 转换为 cv::Mat
    cv::Mat posText = opencv_utils::QImageToMat( mouse_Image);  // 假设你已经实现了 QImageToMat 函数
    // 开始计时
    // QElapsedTimer timer;
    // timer.start();
    QPoint getPoint;
    QPoint UI_ZeroP (SearchRect.x(),SearchRect.y());//归零点坐标
    qDebug() <<"开始采样30次";
     QPoint MaybeP;
    double highestScore = -1.0;  // 初始得分设为一个较低值
     // 获取桌面路径
     QString desktopPath = QDir::homePath() + "/Desktop/DEBUG/";
     for (int i = 0; i < 30; ++i)
     {
         double score;
         QImage img = opencv_utils::FindPicTarget(TargetUI, posText, getPoint, SearchRect, UI_ZeroP, score);
         if (score > highestScore) {
             highestScore = score;
             MaybeP = getPoint;  // 更新得分最高的点
         }
         QString filePath = desktopPath + QString("output_image_%1a.png").arg(i + 1);  // 文件名格式：output_image_1.png, output_image_2.png, ...

         // 保存图片到桌面
         if (img.save(filePath)) {
             qDebug() << "图片成功保存到桌面：" << filePath;
         } else {
             qDebug() << "保存图片失败！";
         }
         cv::Mat TargetUI = opencv_utils::QImageToMat(img);  // 假设你已经实现了 QImageToMat 函数

         QImage res = opencv_utils::DrawPointOnPic(TargetUI, UI_ZeroP, MaybeP);



         // 修改文件名，加入循环次数 i
          filePath = desktopPath + QString("output_image_%1b.png").arg(i + 1);  // 文件名格式：output_image_1.png, output_image_2.png, ...

         // 保存图片到桌面
         if (res.save(filePath)) {
             qDebug() << "图片成功保存到桌面：" << filePath;
         } else {
             qDebug() << "保存图片失败！";
         }
     }

   // sleep(100);

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
  //  QString result = findMostSimilarLocation(location, dreamWorldLocations);

    //qDebug()<< "最相似的地名是: " << result << "OCR:"<<position;
    t_loaction = location;
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
void event_pthread::GameSetting()
{
    //holdKey1();
    pressKey("alt");
    QThread::msleep(50);
    pressKey("s");
    QThread::msleep(50);
    releaseKey("s");
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

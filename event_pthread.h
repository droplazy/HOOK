#ifndef EVENT_PTHREAD_H
#define EVENT_PTHREAD_H

#include <QObject>
#include <QThread>
#include <ProDefine.h>
#include <QImage>
#include <httpclient.h>
#include <QTimer>
#include <QString>
//#include <iostream>

class event_pthread : public QThread
{
    Q_OBJECT

public:
    bool streamOn = false;
    Task_State currentState = Task_State::MOUSER_OFFSET;  // 当前的状态
    QINGLONG_Task QL_State= QINGLONG_Task::IDLE;

    QString t_loaction;
    QString t_position;

    explicit event_pthread(QObject *parent = nullptr);  // 构造函数，支持传递 parent 对象
    virtual void run() override;  // 重载 run 函数

    // 设置当前状态
    void setState(Task_State state);

    // 获取当前状态
    Task_State getState() const;
    void GetORCRegnizeToNetwork(QString picBase64);
    void GetCharacterPostion();
    bool IsCorrectScreen();
    void GetGameScreen();
    void GetCharacterLocation();
    void GetCharacterForTess();

    void GameopenTaskMenu();
    void GameGroup();
    void GameOpenInventoryMenu();
    void GameAttack();
    void GameGiveObject();
    void QingLongTask();
    QPoint findElemntForScreen(QImage image, QRect &rectoffset);//返回鼠标坐标
    void PessF9();
    void GetTaskStart();

    void MoveMouseQinglongNPC();
    QPoint TargetClick;
    bool MouseNeedMove= false;
    void CheckMouserOffset();
    void SetMouserOffset();
    QPoint findElemntForUI(QImage image, QImage image_UI,QPoint zeroP);
    QImage GetGamewindowCenterPoint(QPoint &point);
    void GameSetting();
protected:
    void GetIdleImage();

private:
    double MoveScale = 0.7f;


signals:
    void getPic(QImage);
    void regnize(QString);

private slots:
    void GetCharacterlocInfo(); //很准的图文识别接口  2毛一次

};

#endif // EVENT_PTHREAD_H

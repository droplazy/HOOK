#ifndef EVENT_PTHREAD_H
#define EVENT_PTHREAD_H

#include <QObject>
#include <QThread>
#include <ProDefine.h>
#include <QImage>


class event_pthread : public QThread
{
    Q_OBJECT

public:
    bool streamOn = false;
    Task_State currentState = Task_State::IDLE;  // 当前的状态


    explicit event_pthread(QObject *parent = nullptr);  // 构造函数，支持传递 parent 对象
    virtual void run() override;  // 重载 run 函数

    // 设置当前状态
    void setState(Task_State state);

    // 获取当前状态
    Task_State getState() const;
protected:
    void GetIdleImage();
private:
signals:
    void getPic(QImage);
};

#endif // EVENT_PTHREAD_H

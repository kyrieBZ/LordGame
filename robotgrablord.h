#ifndef ROBOTGRABLORD_H
#define ROBOTGRABLORD_H

//机器人抢地主线程类 负责实现机器人玩家抢地主的操作


#include <QObject>
#include <QThread>

#include "robot.h"

class RobotGrabLord : public QThread
{
    Q_OBJECT
public:
    explicit RobotGrabLord(Robot *robot,QObject *parent = nullptr);

protected:
    void run();

signals:

private:
    Robot *m_robot;
};

#endif // ROBOTGRABLORD_H

#ifndef ROBOT_H
#define ROBOT_H

//机器人玩家类  实现机器人玩家相关的游戏操作

#include <QObject>
#include <QDebug>

#include "player.h"
#include "strategy.h"
#include "robotplayhand.h"
//#include "robotgrablord.h"

//注意：由于玩家对象需要在游戏开始时设置自己的一个名字
//子类同样需要，这里有两种方法
//1.两个子类中均加上一个带有名字参数的构造函数
//2.使用继承构造函数

class Robot : public Player
{
    Q_OBJECT
public:
    using Player::Player;//使用父类中的所有构造函数
    explicit Robot(QObject *parent = nullptr);

    //重写父类（Player）的准备叫地主/出牌函数
    void prepareCallLord() override;
    void preparePlayHand() override;

    //考虑叫地主
    void thinkCallLord() override;
    //考虑出牌
    void thinkPlayHand() override;
};

#endif // ROBOT_H

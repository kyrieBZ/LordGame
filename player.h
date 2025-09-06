#ifndef PLAYER_H
#define PLAYER_H

//玩家类  游戏中一共有两类玩家：真人玩家和机器人玩家
//这个类是玩家的基类

#include <QObject>

#include "card.h"
#include "cards.h"

class Player : public QObject
{
    Q_OBJECT
public:
    enum Role{LORD,FARMER};   //玩家角色枚举
    enum Sex{MAN,WOMAN};      //玩家角色性别枚举
    enum Direction{LEFT,RIGHT};    //玩家头像的显示方位
    enum Type{ROBOT,USER,UNKNOWN};  //玩家类型

    explicit Player(QObject *parent = nullptr);
    explicit Player(QString name,QObject *parent = nullptr);

    //以下是对玩家的相关属性的set和get方法的定义
    //名字
    void setName(QString name);
    QString getName();
    //角色
    void setRole(Role role);
    Role getRole();
    //性别
    void setSex(Sex sex);
    Sex getSex();
    //头像显示方向
    void setDirection(Direction direction);
    Direction getDirection();
    //玩家类型
    void setType(Type type);
    Type getType();
    //玩家的分数
    void setScore(int score);
    int getScore();
    //玩家这局游戏的输赢
    void setIsWin(bool flag);
    bool getIsWin();

    //保存当前玩家的上家/下家的玩家对象
    void setPrevPlyer(Player *player);
    void setNextPlayer(Player *player);
    Player* getPrevPlayer();
    Player* getNextPlayer();

    //叫地主/抢地主
    void grabLordBet(int point);

    //存储扑克牌(发牌时所得到的扑克牌)
    void storeDispatchCard(Card&card);//一张一张地发
    void storeDispatchCard(Cards&cards);//地主玩家最后的三张牌一次性发放

    //得到玩家获得的所有的牌
    Cards getCards();
    //清空玩家手中所有的牌
    void clearCards();

    //出牌
    void playHand(Cards&cards);

    //设置出牌的玩家待处理的扑克牌
    void setPendingInfo(Player*player,Cards&cards);
    Player* getPendPlayer();//获取待处理扑克牌的所有者
    Cards getPendCards();//获取待处理的扑克牌

    //槽函数
    //存储出牌玩家对象和打出的牌
    void storePendingInfo(Player *player,Cards &cards);


    //注意：游戏进行过程中用户的出牌和叫地主操作是思考后执行
    //而机器人玩家则是由子线程程序自动实现  考虑使用多态来实现
    //虚函数
    virtual void prepareCallLord();//准备叫地主
    virtual void preparePlayHand();//准备出牌
    virtual void thinkCallLord();//考虑叫地主
    virtual void thinkPlayHand();//考虑出牌

signals:
    //通知游戏控制类玩家已进行抢地主下注操作
    void notifyGrabLordBet(Player *player,int bet);
    //通知已经出牌
    void notifyPlayHand(Player *player,Cards &cards);
    //通知已经发牌了
    void notifyPickCards(Player *player,Cards &cards);

//注意：子类需要继承这些玩家属性，使用protected权限而非private权限

//注意：声明的顺序即为初始化顺序
protected:
    QString m_name;//玩家名字
    Role m_role;//玩家角色
    Sex m_sex;//玩家性别
    Direction m_direction;//头像显示方向
    Type m_type;//玩家类型
    int m_score;//玩家的分数
    bool m_isWin;//玩家的输赢
    Player* m_prevPlayer;//当前玩家的上家
    Player* m_nextPlayer;//当前玩家的下家
    Cards m_cards;//存储多张扑克牌（玩家手里的牌）

    Cards m_pendCards;//当前打出的牌
    Player* m_pendPlayer = nullptr;//当前打出的牌的所有者
};

#endif // PLAYER_H

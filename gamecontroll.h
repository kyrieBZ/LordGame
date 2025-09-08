#ifndef GAMECONTROLL_H
#define GAMECONTROLL_H

//游戏控制类，负责控制游戏中当前处于什么状态，当前玩家是谁，当前打出的牌是什么等等
//注意：游戏中当前玩家实时变化

#include <QObject>
#include <QRandomGenerator>
#include <QTimer>

#include "robot.h"
#include "userplayer.h"
#include "cards.h"
#include "card.h"


struct BetRecord{
    BetRecord(){
        reset();
    }

    void reset(){
        player=nullptr;
        bet=0;
        times=0;
    }

    Player *player;//下注玩家
    int bet;//下注分数
    int times;//第几次叫地主
};

class GameControll : public QObject
{
    Q_OBJECT
public:
    //对于机器人玩家，游戏状态与玩家状态是必要的，因为它的逻辑实现由子线程程序实现

    //游戏状态
    enum GameStatus{
        DispatchCard,   //发牌状态
        CallingLord,      //叫地主状态
        PlayingHand     //出牌状态
    };
    //玩家状态
    enum PlayerStatus{
        ThinkingForCallLord,  //考虑叫地主状态
        ThinkingForPlayHand,  //考虑出牌状态
        Winning                          //玩家胜利状态
    };

    explicit GameControll(QObject *parent = nullptr);

    //初始化玩家和扑克牌
    void playerInit();

    //得到玩家的实例对象
    Robot* getLeftRobot();
    Robot* getRightRobot();
    UserPlayer* getUserPlayer();

    //设置和获取当前玩家
    void setCurrentPlayer(Player *player);
    Player* getCurrentPlayer();

    //得到当前出牌玩家和打出的牌
    Player* getPendPlayer();
    Cards getPendCards();

    //初始化扑克牌（52张）
    void initAllCards();
    //每次发一张牌
    Card takeOneCard();
    //得到最后的三张牌
    Cards getSurplusCards();
    //重置卡牌数据
    void resetCardData();

    //准备叫地主
    void startLordCard();
    //成为地主
    void becomeLord(Player* player,int bet);
    //清空所有玩家的得分
    void clearPlayerScore();
    //得到玩家下注的最高分数
    int getPlayerMaxBet();

    //槽函数
    //处理叫地主
    void onGrabBet(Player *player,int bet);
    //处理出牌
    void onPlayHand(Player *player,Cards &cards);
signals:
    void playerStatusChanged(Player *player,PlayerStatus status);
    //通知玩家执行了抢地主操作
    void notifyGrabLordBet(Player *player,int bet,bool flag);
    //游戏状态变化
    void gameStatusChanged(GameStatus status);
    //通知玩家出牌了
    void notifyPlayHand(Player *player,Cards &cards);
    //给玩家传递出牌数据
    void pendingInfo(Player *player,Cards &cards);

private:
    Robot* m_robotLeft = nullptr;    //左侧机器人玩家
    Robot* m_robotRight = nullptr; //右侧机器人玩家
    UserPlayer* m_user = nullptr;   //真人用户玩家

    //注意：当前玩家是实时发生变化的，既可能为机器人又可能为真人用户
    //，因此需要用Player*
    Player* m_currPlayer;//当前玩家

    Cards m_pendCards;//打出的待处理的扑克牌
    Player* m_pendPlayer = nullptr;//出牌的玩家

    Cards m_allCards;//一幅扑克牌（52张）

    BetRecord m_betRecord;//记录玩家的抢地主信息

    int m_currBet = 0;//底分

};

#endif // GAMECONTROLL_H

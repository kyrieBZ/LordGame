#ifndef STRATEGY_H
#define STRATEGY_H

//出牌策略类，负责实现与机器人玩家相关的出牌逻辑
#include <QVector>
#include<functional>
#include <QMap>
#include <QDebug>

#include "player.h"
#include "playhand.h"
#include "cards.h"

class Strategy
{
public:
    Strategy(Player *player,const Cards &cards);

    // 1.制定出牌策略
    Cards makeStrategy();
    // 2.第一个出牌 FirstPlay
    Cards firstPlay();
    // 3.得到比指定牌型大的牌
    Cards getGreaterCards(PlayHand type);
    // 4.能大过指定的牌时，判断是出牌还是放弃，返回true->出牌  返回false->放弃
    bool whetherToBeat(Cards &cards);

    // 5.找出指定数量（count）的相同点数的牌（point），找出count张点数为point的牌
    Cards findSamePointCards(Card::CardPoint point,int count);
    // 6.找出所有点数数量为count的牌 ==>得到一个多张扑克牌数组
    QVector<Cards> findCardsByCount(int count);
    // 7.根据点数范围找牌
    Cards getRangeCards(Card::CardPoint begin,Card::CardPoint end);
    // 8.按排型找牌，并且指定要找的牌是否大过指定的牌型
    QVector<Cards> findCardType(PlayHand hand,bool beat);
    //9.从指定的Cards对象中挑选出满足条件的顺子
    void pickSeqSingles(Cards &cards,QVector<QVector<Cards>> &allSeqRecord,QVector<Cards> &seqSingle);
    //10.最优顺子的集合的筛选函数
    QVector<Cards> pickOptimalSeqSingles();

private:
    //函数指针 参数为point 返回值为Cards  需要存储下面的getBaseSeqPair或getBaseSeqSingle函数的地址
    using function=Cards (Strategy::*)(Card::CardPoint point);
    //找顺子或连对时需要传入getSeqPairOrSeqSingle()函数的数据信息
    struct CardInfo{
        Card::CardPoint begin;//起始点数
        Card::CardPoint end;//终止点数
        int extra;//顺子或连对连续的数量
        bool beat;//是否需要找出大过原顺子或连对的牌
        int number;//指定点数的牌的数量
        int base;//最基础的顺子或连对连续的数量
        function getSeq;//函数指针
    };

    QVector<Cards> getCards(Card::CardPoint point,int number);
    QVector<Cards> getTripleSingleOrPair(Card::CardPoint begin,PlayHand::HandType type);
    QVector<Cards> getPlane(Card::CardPoint begin);
    QVector<Cards> getPlane2SingleOr2Pair(Card::CardPoint begin,PlayHand::HandType type);
    QVector<Cards> getSeqPairOrSeqSingle(CardInfo &info);
    QVector<Cards> getBomb(Card::CardPoint begin);
    Cards getBaseSeqPair(Card::CardPoint point);//找到一个最基础的连对（3个连续的对）
    Cards getBaseSeqSingle(Card::CardPoint point);//找到一个最基础的顺子（5张连续的单牌）
private:
    Player *m_player;
    Cards m_cards;
};

#endif // STRATEGY_H

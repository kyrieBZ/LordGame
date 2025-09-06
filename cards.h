#ifndef CARDS_H
#define CARDS_H

//多张卡牌类  实现玩家一次性出多张排等的功能
//使用QSet容器存储  但QSet容器与常规STL容器不一致 底层使用哈希表实现
//需要自行实现排序功能

#include <QSet>
#include <QRandomGenerator>

#include "card.h"

class Cards
{
public:
    //排序类型：升序，降序，不排序
    enum SortType{ASC,DESC,NOSORT};
    Cards();
    Cards(const Card&card);

    //添加扑克牌
    void add(const Card &card);//添加一张
    void add(const Cards &cards);//添加多张

    //容器初始化操作  一次性插入多个数据（重载操作符<<）
    Cards& operator << (const Card& card);
    Cards& operator <<(const Cards& cards);

    //删除扑克牌
    void remove(const Card &card);//删除一张
    void remove(const Cards &cards);//删除多张
    void remove(const QVector<Cards> &cards);

    //扑克牌的数量
    int cardCount();
    //是否为空
    bool isEmpty();
    //清空扑克牌
    void clear();

    //最大点数
    Card::CardPoint maxPoint();
    //最小点数
    Card::CardPoint minPoint();

    //指定点数的牌的数量
    int pointCount(Card::CardPoint point);

    //某张牌是否在集合中
    bool contains(const Card&card);//判断某一张牌
    bool contains(const Cards&cards);//判断某几张牌

    //随机取出一张牌  注意：由于QSet中元素无序，直接取就行
    Card takeRandCard();

    //注意：由于存入QSet后里面的牌就无序了，需要将排序后的牌放入QVector容器
    //QVector<Card>  使用别名CardList来代替

    //将扑克牌排序好  默认为降序排序
    //真人玩家的牌显示时从左到右 按点数从大到小进行显示
    CardList toCardList(SortType type=DESC);

private:
    //注意：初始时的所有扑克牌也都存在这个集合中
    QSet<Card> m_cards;//存储多张卡牌
};

#endif // CARDS_H

#ifndef CARD_H
#define CARD_H

//扑克牌类，用于实现对扑克牌对象的抽象

#include <QVector>

class Card
{
public:
    //花色
    enum CardSuit{
        Suit_Begin,
        Diamond,     //方片
        Club,            //梅花
        Heart,           //红桃
        Spade,         //黑桃
        Suit_End
    };
    //点数
    enum CardPoint{
        Card_Begin,
        Card_3,
        Card_4,
        Card_5,
        Card_6,
        Card_7,
        Card_8,
        Card_9,
        Card_10,
        Card_J,
        Card_Q,
        Card_K,
        Card_A,
        Card_2,
        Card_SJ,   //small joker
        Card_BJ,  //big joker
        Card_End
    };


    Card();
    //带参构造函数用于初始化对象
    Card(CardPoint point,CardSuit suit);

    //提供对应的get和set方法来对类中的私有成员进行间接访问
    void setPoint(CardPoint point);
    void setSuit(CardSuit suit);
    CardPoint getPoint() const;
    CardSuit getSuit() const;

private:
    CardPoint m_point;//点数
    CardSuit m_suit;//花色
};

//std::sort()需要的比较函数
bool lessSort(const Card&c1,const Card&c2);//升序比较
bool greaterSort(const Card&c1,const Card&c2);//降序比较

//操作符重载（==）
bool operator==(const Card&left,const Card&right);

bool operator<(const Card& left, const Card& right);

//重写哈希值计算的全局函数
uint qHash(const Card&card);

//别名定义
using CardList=QVector<Card>;

#endif // CARD_H

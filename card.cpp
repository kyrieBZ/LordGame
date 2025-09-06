#include "card.h"

Card::Card() {}

Card::Card(CardPoint point, CardSuit suit)
{
    setPoint(point);
    setSuit(suit);
}

void Card::setPoint(CardPoint point)
{
    this->m_point=point;
}

void Card::setSuit(CardSuit suit)
{
    this->m_suit=suit;
}

Card::CardPoint Card::getPoint() const
{
    return m_point;
}

Card::CardSuit Card::getSuit() const
{
    return m_suit;
}

//注意：由于是要传入两个Card类型的对象做比较，以下2个函数不是类的成员函数
 //用于升序的比较函数
bool lessSort(const Card &c1, const Card &c2)
{
    if(c1.getPoint()==c2.getPoint()){
        //点数相同时按照花色枚举中的顺序按花色进行排序
        return c1.getSuit()<c2.getSuit();
    }
    else{
        //点数不同则直接按照点数进行排序
        return c1.getPoint()<c2.getPoint();
    }
}

//用于升序的比较函数
bool greaterSort(const Card &c1, const Card &c2)
{
    if(c1.getPoint()==c2.getPoint()){
        //点数相同则按照花色枚举中的顺序按花色进行排序
        return c1.getSuit()>c2.getSuit();
    }
    else{
        //点数不同则直接按点数大小进行排序
        return c1.getPoint()>c2.getPoint();
    }
}

//重载==操作符
bool operator==(const Card&left,const Card&right){
    //点数和花色均相同则这两张扑克牌相等
    return (left.getPoint()==right.getPoint() &&left.getSuit()==left.getSuit());
}

bool operator<(const Card& left, const Card& right)
{
    // 先比较点数，再比较花色（根据你的游戏规则调整）
    if (left.getPoint() != right.getPoint()) {
        return left.getPoint() < right.getPoint();
    }
    return left.getSuit() < right.getSuit();
}

uint qHash(const Card &card)
{
    //注意：Hash值用于区分card对象，因此计算时每张扑克牌对象的哈希值应不同
    return card.getPoint()*100+card.getSuit();
}

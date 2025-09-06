#include "cards.h"

Cards::Cards() {}

Cards::Cards(const Card &card)
{
    add(card);
}

void Cards::add(const Card &card)
{
    //添加一张扑克牌
    m_cards.insert(card);
}

void Cards::add(const Cards &cards)
{
    //添加多张扑克牌  相当于m_cards容器中的多张扑克牌与传入的多张扑克牌做并集
    m_cards.unite(cards.m_cards);
}

Cards &Cards::operator <<(const Card &card)
{
    add(card);
    return *this;
}

Cards &Cards::operator <<(const Cards &cards)
{
    add(cards);
    return *this;
}

void Cards::remove(const Card &card)
{
    m_cards.remove(card);
}

void Cards::remove(const Cards &cards)
{
    //从当前的容器m_cards中去除另一个集合中的一些元素，相当于差集
    m_cards.subtract(cards.m_cards);
}

void Cards::remove(const QVector<Cards> &cards)
{
    for(int i=0;i<cards.size();i++){
        remove(cards[i]);
    }
}

int Cards::cardCount()
{
    return m_cards.size();
}

bool Cards::isEmpty()
{
    return m_cards.isEmpty();
}

void Cards::clear()
{
    m_cards.clear();
}

Card::CardPoint Cards::maxPoint()
{
    //遍历集合，找到集合中的最大点数
    //注意极端情况（容器为空，并没有任何一张卡牌对象
    Card::CardPoint max=Card::Card_Begin;
    if(!m_cards.empty()){
        for ( const Card &card : m_cards) {
            if (card.getPoint() > max) {
                max = card.getPoint();
            }
        }
    }
    return max;
}

Card::CardPoint Cards::minPoint()
{
    //遍历集合，找到集合中的最小点数
    //注意极端情况（容器为空，并没有任何一张卡牌对象
    Card::CardPoint min=Card::Card_End;

    if(!m_cards.empty()){
        for(const Card&card : m_cards){
            if(card.getPoint()<min){
                min=card.getPoint();
            }
        }
    }
    return min;
}

int Cards::pointCount(Card::CardPoint point)
{
    //统计某个点数的牌在容器中的数量
    int count=0;
    for(const Card&card:m_cards){
        if(card.getPoint()==point){
            count++;
        }
    }
    return count;
}

//注意：QSet下有一个contains()函数即可实现该判断功能
//该函数有两个重载版本，一个传入具体的T类型的一个对象，一个需要传入QSet
bool Cards::contains(const Card &card)
{
    //判断某一张牌是否在集合中
    //在则返回true，不在返回false
    return m_cards.contains(card);
}

bool Cards::contains(const Cards &cards)
{
    //判断某几张牌是否在集合中
    //在则返回true，不在返回false
    return m_cards.contains(cards.m_cards);
}

Card Cards::takeRandCard()
{
    //从容器中随机取出一张扑克牌
    //注意：通过QRandomGenerator类可以获取到一个随机数
    //关键：先通过global()静态方法得到一个随机数对象，再调用bounded()获取
    //注意：参数可以只传递最大值，此时最小值为0，也可以同时传递最大和最小值
    //注意：随机数生成的范围：[lowest,heightest)  左闭右开
    int num=QRandomGenerator::global()->bounded(m_cards.size());

    //从0开始遍历，当遍历到num数目时即找到要取的牌
    QSet<Card>::const_iterator it=m_cards.constBegin();
    for(int i=0;i<num;i++,it++){

    }

    //循环了num次以后it迭代器指向我们需要取出的扑克牌
    Card card=*it;
    m_cards.erase(it);//清除这张被取出的牌
    return card;
}

CardList Cards::toCardList(SortType type)
{
    //思路：遍历QSet将其中的所有元素放到一个CardList中,再对CardList进行排序
    CardList list;
    //1.存储扑克牌到list中
    for(auto it=m_cards.begin();it!=m_cards.end();it++){
        list<<*it;
    }

    //2.对list进行排序
    if(type==ASC){
        //升序
        std::sort(list.begin(),list.end(),lessSort);
    }
    else if(type==DESC){
        //降序
        std::sort(list.begin(),list.end(),greaterSort);
    }
    else{
        //不排序
    }
    return list;
}

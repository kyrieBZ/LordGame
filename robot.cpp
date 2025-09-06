#include "robot.h"
#include "robotgrablord.h"

Robot::Robot(QObject *parent)
    : Player{parent}
{
    m_type=Player::ROBOT;
}

void Robot::prepareCallLord()
{
    //创建并启动子线程
    RobotGrabLord *subThread=new RobotGrabLord(this);
    connect(subThread,&QThread::finished,this,[=](){
        qDebug()<<"RobotGrabLord子线程对象析构..."<<"Robot name: "<<this->getName();
        subThread->deleteLater();
    });
    subThread->start();
}

void Robot::preparePlayHand()
{
    RobotPlayHand *subThread=new RobotPlayHand(this);
    connect(subThread,&QThread::finished,this,[=](){
        qDebug()<<"RobotPlayHand子线程对象析构..."<<"Robot name: "<<this->getName();
        subThread->deleteLater();
    });
    subThread->start();
}

void Robot::thinkCallLord()
{
    /*
        基于手中的牌计算权重
        大/小王：6
        顺子/炸弹：5
        三张点数相同的牌：4
        2的权重：3
        对牌：1
    */
    int weight=0;//权重
    Strategy st(this,m_cards);
    weight += st.getRangeCards(Card::Card_SJ,Card::Card_BJ).cardCount() * 6;

    QVector<Cards> optSeq = st.pickOptimalSeqSingles();
    weight += optSeq.size() * 5;

    QVector<Cards> bombs=st.findCardsByCount(4);
    weight += bombs.size() * 5;

    weight += m_cards.pointCount(Card::Card_2) * 3;

    Cards temp=m_cards;
    temp.remove(optSeq);
    temp.remove(bombs);
    Cards card2=st.getRangeCards(Card::Card_2,Card::Card_2);
    temp.remove(card2);
    QVector<Cards> triples= Strategy(this,temp).findCardsByCount(3);
    weight += triples.size() *4;

    temp.remove(triples);
    QVector<Cards> pair=Strategy(this,temp).findCardsByCount(2);
    weight += pair.size() * 1;

    if(weight>=22){
        grabLordBet(3);
    }
    else if(weight>=18){
        grabLordBet(2);
    }
    else if(weight>=10){
        grabLordBet(1);
    }
    else {
        grabLordBet(0);
    }
}

void Robot::thinkPlayHand()
{
    Strategy st(this,m_cards);
    Cards cs=st.makeStrategy();
    //出牌
    playHand(cs);
}

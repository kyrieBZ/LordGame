#include "player.h"

Player::Player(QObject *parent)
    : QObject{parent}
{
    m_score=0;
    m_isWin=false;
}

//委托构造函数  会先执行上面的构造函数再接着执行下面设置名字的部分
Player::Player(QString name, QObject *parent) : Player(parent)
{
    m_name=name;
}

void Player::setName(QString name)
{
    m_name=name;
}

QString Player::getName()
{
    return m_name;
}

void Player::setRole(Role role)
{
    m_role=role;
}

Player::Role Player::getRole()
{
    return m_role;
}

void Player::setSex(Sex sex)
{
    m_sex=sex;
}

Player::Sex Player::getSex()
{
    return m_sex;
}

void Player::setDirection(Direction direction)
{
    m_direction=direction;
}

Player::Direction Player::getDirection()
{
    return m_direction;
}

void Player::setType(Type type)
{
    m_type=type;
}

Player::Type Player::getType()
{
    return m_type;
}

void Player::setScore(int score)
{
    m_score=score;
}

int Player::getScore()
{
    return m_score;
}

void Player::setIsWin(bool flag)
{
    m_isWin=flag;
}

bool Player::getIsWin()
{
    return m_isWin;
}

void Player::setPrevPlyer(Player *player)
{
    m_prevPlayer=player;
}

void Player::setNextPlayer(Player *player)
{
    m_nextPlayer=player;
}

Player *Player::getPrevPlayer()
{
    return m_prevPlayer;
}

Player *Player::getNextPlayer()
{
    return m_nextPlayer;
}

void Player::grabLordBet(int point)
{
    emit notifyGrabLordBet(this,point);
}

void Player::storeDispatchCard(Card &card)
{
    m_cards.add(card);
    Cards cs;
    cs.add(card);
    emit notifyPickCards(this,cs);
}

void Player::storeDispatchCard(Cards &cards)
{
    m_cards.add(cards);
    emit notifyPickCards(this,cards);
}

Cards Player::getCards()
{
    return m_cards;
}

void Player::clearCards()
{
    m_cards.clear();
}

void Player::playHand(Cards &cards)
{
    m_cards.remove(cards);
    //通知玩家已出牌
    emit notifyPlayHand(this,cards);
}

void Player::setPendingInfo(Player *player, Cards &cards)
{
    m_pendPlayer=player;
    m_pendCards=cards;
}

Player *Player::getPendPlayer()
{
    return m_pendPlayer;
}

Cards Player::getPendCards()
{
    return m_pendCards;
}

void Player::storePendingInfo(Player *player, Cards &cards)
{
    m_pendPlayer=player;
    m_pendCards=cards;
}

void Player::prepareCallLord()
{

}

void Player::preparePlayHand()
{

}

void Player::thinkCallLord()
{

}

void Player::thinkPlayHand()
{

}

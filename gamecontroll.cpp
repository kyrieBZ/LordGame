#include "gamecontroll.h"

GameControll::GameControll(QObject *parent)
    : QObject{parent}
{
    // 在程序初始化时（如main函数中）注册
    qRegisterMetaType<Cards>("Cards");
    // 如果需要使用引用类型，也可以一并注册
    qRegisterMetaType<const Cards&>("Cards&");
}

void GameControll::playerInit()
{
    //玩家对象实例化
    m_robotLeft=new Robot("机器人A",this);
    m_robotRight=new Robot("机器人B",this);
    m_user=new UserPlayer("我自己",this);

    //头像显示方位
    m_robotLeft->setDirection(Player::LEFT);
    m_robotRight->setDirection(Player::RIGHT);
    m_user->setDirection(Player::RIGHT);

    //性别  随机生成  0表示男，1表示女
    Player::Sex sex;
    sex=(Player::Sex)QRandomGenerator::global()->bounded(2);
    m_robotLeft->setSex(sex);

    sex=(Player::Sex)QRandomGenerator::global()->bounded(2);
    m_robotRight->setSex(sex);

    sex=(Player::Sex)QRandomGenerator::global()->bounded(2);
    m_user->setSex(sex);

    //出牌顺序  按逆时针顺序   出牌顺序即需要设置每一个玩家的上家和下家
    //真人玩家m_user
    m_user->setPrevPlyer(m_robotLeft);
    m_user->setNextPlayer(m_robotRight);

    //左侧机器人m_robotLeft
    m_robotLeft->setPrevPlyer(m_robotRight);
    m_robotLeft->setNextPlayer(m_user);

    //右侧机器人m_robotRight
    m_robotRight->setPrevPlyer(m_user);
    m_robotRight->setNextPlayer(m_robotLeft);

    //初始时指定真人玩家为当前玩家
    m_currPlayer=m_user;

    //处理玩家抢地主下注时所发射的信号
    connect(m_user,&UserPlayer::notifyGrabLordBet,this,&GameControll::onGrabBet);
    connect(m_robotLeft,&UserPlayer::notifyGrabLordBet,this,&GameControll::onGrabBet);
    connect(m_robotRight,&UserPlayer::notifyGrabLordBet,this,&GameControll::onGrabBet);

    //传递出牌玩家对象和玩家打出的牌
    connect(this,&GameControll::pendingInfo,m_robotLeft,&Robot::storePendingInfo);
    connect(this,&GameControll::pendingInfo,m_robotRight,&Robot::storePendingInfo);
    connect(this,&GameControll::pendingInfo,m_user,&UserPlayer::storePendingInfo);

    //处理玩家出牌
    connect(m_robotLeft,&Robot::notifyPlayHand,this,&GameControll::onPlayHand);
    connect(m_robotRight,&Robot::notifyPlayHand,this,&GameControll::onPlayHand);
    connect(m_user,&UserPlayer::notifyPlayHand,this,&GameControll::onPlayHand);
}

Robot *GameControll::getLeftRobot()
{
    return m_robotLeft;
}

Robot *GameControll::getRightRobot()
{
    return m_robotRight;
}

UserPlayer *GameControll::getUserPlayer()
{
    return m_user;
}

void GameControll::setCurrentPlayer(Player *player)
{
    m_currPlayer=player;
}

Player *GameControll::getCurrentPlayer()
{
    return m_currPlayer;
}

Player *GameControll::getPendPlayer()
{
    return m_pendPlayer;
}

Cards GameControll::getPendCards()
{
    return m_pendCards;
}

void GameControll::initAllCards()
{
    m_allCards.clear();
    //除了大王小王外的50张扑克牌的初始化
    for(int p=Card::Card_Begin+1;p<Card::Card_SJ;++p){
        for(int s=Card::Suit_Begin+1;s<Card::Suit_End;++s){
            Card c((Card::CardPoint)p,(Card::CardSuit)s);
            m_allCards.add(c);
        }
    }


    //注意：大王和小王不属于四个花色中的任意一个，因此需要单独初始化
    m_allCards.add(Card(Card::Card_SJ,Card::Suit_Begin));
    m_allCards.add(Card(Card::Card_BJ,Card::Suit_End));
}

Card GameControll::takeOneCard()
{
   return  m_allCards.takeRandCard();
}

Cards GameControll::getSurplusCards()
{
    return m_allCards;
}

void GameControll::resetCardData()
{
    //洗牌
    initAllCards();
    //清空所有玩家的牌
    m_robotLeft->clearCards();
    m_robotRight->clearCards();
    m_user->clearCards();

    //初始化出牌玩家和牌
    m_pendPlayer=nullptr;
    m_pendCards.clear();
}

void GameControll::startLordCard()
{
    //由当前玩家执行该操作
    m_currPlayer->prepareCallLord();
    //发射考虑叫地主状态发生时的信号
    emit playerStatusChanged(m_currPlayer,ThinkingForCallLord);
}

void GameControll::becomeLord(Player* player,int bet)
{
    m_currBet=bet;
    player->setRole(Player::LORD);
    player->getPrevPlayer()->setRole(Player::FARMER);
    player->getNextPlayer()->setRole(Player::FARMER);

    m_currPlayer=player;//地主最先出牌，因此设置当前玩家为初始的地主
    player->storeDispatchCard(m_allCards);//存储地主获取的最后的三张牌

    QTimer::singleShot(1000,this,[=](){
        emit gameStatusChanged(PlayingHand);
        emit playerStatusChanged(player,ThinkingForPlayHand);
        m_currPlayer->preparePlayHand();
    });
}

void GameControll::clearPlayerScore()
{
    //清空所有玩家的分数
    m_robotLeft->setScore(0);
    m_robotRight->setScore(0);
    m_user->setScore(0);
}

int GameControll::getPlayerMaxBet()
{
    return m_betRecord.bet;
}

void GameControll::onGrabBet(Player *player, int bet)
{
    //1.通知主界面玩家执行了抢地主的操作（更新信息提示）
    if(bet == 0 || m_betRecord.bet>=bet){
        //放弃抢地主或是下注分数无效，直接通知放弃
        emit notifyGrabLordBet(player,0,false);
    }
    else if(bet>0&&m_betRecord.bet==0){
        //第一个抢地主的玩家
        emit notifyGrabLordBet(player,bet,true);
    }
    else{
        //第2,3个抢地主的玩家
        emit notifyGrabLordBet(player,bet,false);
    }
    //2.判断玩家下注是否为3分，是则抢地主结束
    if(bet == 3){
        //玩家成为地主
        becomeLord(player,bet);
        //清空抢地主信息
        m_betRecord.reset();
        return;
    }
    //3.下注不够3分，对下注分数进行比较，分数高的即为地主
    //需要存储下最高的分数
    if(m_betRecord.bet<bet){
        m_betRecord.bet = bet;
        m_betRecord.player=player;
    }
    m_betRecord.times++;
    //如果三个玩家均抢过了一次地主，则抢地主结束
    if(m_betRecord.times == 3){
        if(m_betRecord.bet == 0){
            //三个玩家均执行抢地主操作，且下注均为0分（不抢）
            //重新发牌，发牌操作由主界面执行，因此这里发射一个游戏状态改变的信号
            emit gameStatusChanged(DispatchCard);
        }
        else{
            becomeLord(m_betRecord.player,m_betRecord.bet);
        }
        m_betRecord.reset();
        return;
    }
    //4.切换玩家，通知下一个玩家继续抢地主
    m_currPlayer = player->getNextPlayer();
    //发送信号给主界面，告知当前状态为抢地主
    emit playerStatusChanged(m_currPlayer,ThinkingForCallLord);
    m_currPlayer->prepareCallLord();
}

void GameControll::onPlayHand(Player *player, Cards &cards)
{
    //1.将玩家出牌的信号转发给主界面
    emit notifyPlayHand(player,cards);
    //2.如果不是空牌，给其他玩家发送信号，保存出牌玩家对象和打出的牌
    if(!cards.isEmpty()){
        m_pendCards = cards;
        m_pendPlayer = player;
        emit pendingInfo(player,cards);
    }
    //如果有炸弹，底分翻倍
    PlayHand::HandType type=PlayHand(cards).getHandType();
    if(type == PlayHand::Hand_Bomb || type == PlayHand::Hand_Bomb_Jokers){
        m_currBet *= 2;
    }
    //3.如果玩家的牌出完了，计算本局游戏的总得分
    if(player->getCards().isEmpty()){
        Player *prev=player->getPrevPlayer();
        Player *next=player->getNextPlayer();
        if(player->getRole() == Player::LORD){
            player->setScore(player->getScore() + 2*m_currBet);
            prev->setScore(prev->getScore() - m_currBet);
            next->setScore(next->getScore() - m_currBet);
            player->setIsWin(true);
            prev->setIsWin(false);
            prev->setIsWin(false);
        }
        else{
            player->setIsWin(true);
            player->setScore(player->getScore() + m_currBet);
            if(prev->getRole() == Player::LORD){
                prev->setScore(prev->getScore() - 2*m_currBet);
                next->setScore(next->getScore() + m_currBet);
                prev->setIsWin(false);
                next->setIsWin(true);
            }
            else{
                prev->setScore(prev->getScore() + m_currBet);
                next->setScore(next->getScore() - 2*m_currBet);
                prev->setIsWin(true);
                next->setIsWin(false);
            }
        }
        emit playerStatusChanged(player,GameControll::Winning);
        return;
    }
    //4.牌没有出完，下一个玩家继续出牌
    m_currPlayer=player->getNextPlayer();
    m_currPlayer->preparePlayHand();
    emit playerStatusChanged(m_currPlayer,GameControll::ThinkingForPlayHand);
}

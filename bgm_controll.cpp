#include "bgm_controll.h"

BGM_Controll::BGM_Controll(QObject *parent)
    : QObject{parent}
{
    for(int i=0;i<5;i++){
        PlayerInfo info;
        info.player = new QMediaPlayer(this);
        info.audioOutPut = new QAudioOutput(this);
        info.player->setAudioOutput(info.audioOutPut);
        info.audioOutPut->setVolume(1.0f);//默认最大音量

        //设置播放结束处理
        if(i < 2 || i == 4){
            //单次播放模式
            connect(info.player,&QMediaPlayer::mediaStatusChanged,this,[=](QMediaPlayer::MediaStatus status){
                if(status == QMediaPlayer::EndOfMedia){
                    info.player->stop();
                }
                else if(i == 2){
                    //循环播放模式
                    connect(info.player,&QMediaPlayer::mediaStatusChanged,this,[=](QMediaPlayer::MediaStatus status){
                        if(status == QMediaPlayer::EndOfMedia){
                            info.player->setPosition(0);
                            info.player->play();
                        }
                    });
                }
            });
        }
        m_players.append(info);
    }

    //初始化播放列表
    initPlayerList();
}

void BGM_Controll::initPlayerList()
{
    QStringList list;
    list<<"Man"<<"Woman"<<"BGM"<<"Other"<<"Ending";

    //读取json配置文件
    QFile file(":/conf/playList.json");
    file.open(QFile::ReadOnly);
    QByteArray json = file.readAll();
    file.close();

    //解析从文件中读取的JSON数据
    QJsonDocument doc = QJsonDocument::fromJson(json);
    QJsonObject obj = doc.object();

    for(int i=0;i<list.size();i++){
        QString prefix = list[i];
        QJsonArray array = obj.value(prefix).toArray();

        //初始化多媒体播放列表
        for(int j=0;j<array.size();j++){
            m_players[i].mediaList.append(QUrl(array[i].toString()));
        }
    }
}

void BGM_Controll::startBGM(int volume)
{
    auto &playerInfo = m_players[2];
    playerInfo.currentIndex = 0;
    playerInfo.audioOutPut->setVolume(volume / 100.0f);
    playerInfo.player->setSource(playerInfo.mediaList[0]);
    playerInfo.player->play();
}

void BGM_Controll::stopBGM()
{
    m_players[2].player->stop();
}

//1.玩家下注了没有？
//2.玩家的性别？
//3.什么时候播放什么样的音频文件
void BGM_Controll::playerRobLordMusic(int point,RoleSex sex,bool isFirst)
{
    int index = sex == Man ? 0 : 1;
    auto &playerInfo = m_players[index];

    if(isFirst && point > 0){
        playerInfo.currentIndex = Order;//叫地主
    }
    else if(point == 0){
        if(isFirst){
            playerInfo.currentIndex = NoOrder;//不叫
        }
        else{
            playerInfo.currentIndex = NoRob;//不抢
        }
    }
    else if(point == 2){
        playerInfo.currentIndex = Rob1;//抢地主
    }
    else if(point == 3){
        playerInfo.currentIndex = Rob2;//抢地主
    }

    playerInfo.player->setSource(playerInfo.mediaList[playerInfo.currentIndex]);
    playerInfo.player->play();
}

void BGM_Controll::playCardMusic(Cards cards, bool isFirst, RoleSex sex)
{
    int index = sex == Man ? 0 : 1;
    auto &playerInfo = m_players[index];

    Card::CardPoint pt = Card::CardPoint::Card_Begin;
    //取出牌型，然后判断
    PlayHand hand(cards);
    PlayHand::HandType type = hand.getHandType();
    if(type == PlayHand::Hand_Single || type == PlayHand::Hand_Pair || type == PlayHand::Hand_Triple){
        pt = cards.takeRandCard().getPoint();
    }

    int number = 0;//计算播放列表索引（索引即CardType枚举索引）
    switch (type) {
    case PlayHand::Hand_Single:{
        number = pt - 1;
        break;
    }
    case PlayHand::Hand_Pair:{
        number = pt -1 + 15;
        break;
    }
    case PlayHand::Hand_Triple:{
        number = pt -1 + 15 + 13;
        break;
    }
    case PlayHand::Hand_Triple_Single:{
        number = ThreeBindOne;
        break;
    }
    case PlayHand::Hand_Triple_Pair:{
        number = ThreeBindPair;
        break;
    }
    case PlayHand::Hand_Plane:
    case PlayHand::Hand_Plane_Two_Single:
    case PlayHand::Hand_Plane_Two_Pair:
    {
        number = Plane;
        break;
    }
    case PlayHand::Hand_Seq_Pair:{
        number = SequencePair;
        break;
    }
    case PlayHand::Hand_Seq_Single:{
        number = Sequence;
        break;
    }
    case PlayHand::Hand_Bomb:{
        number = Bomb;
        break;
    }
    case PlayHand::Hand_Bomb_Jokers:{
        number = JokerBomb;
        break;
    }
    case PlayHand::Hand_Bomb_Pair:
    case PlayHand::Hand_Bomb_Two_Single:
    case PlayHand::Hand_Bomb_Jokers_Pair:
    case PlayHand::Hand_Bomb_Jokers_Two_Single:
    {
        number = FourBindTwo;
    }

    default:
        break;
    }

    if(!isFirst && (number >= Plane && number <= FourBindTwo)){
        //MoreBiger1,// 大你  MoreBiger2   两个中的一个
        playerInfo.currentIndex = MoreBiger1 + QRandomGenerator::global()->bounded(2);
    }
    else{
        playerInfo.currentIndex = number;
    }

    playerInfo.player->setSource(playerInfo.mediaList[playerInfo.currentIndex]);
    playerInfo.player->play();

    if(number == Bomb || number == JokerBomb){
        playAssistMusic(BombVoice);
    }
    if(number == Plane){
        playAssistMusic(PlaneVoice);
    }
}

void BGM_Controll::playLastMusic(CardType type, RoleSex sex)
{
    int index = sex == Man ? 0 : 1;
    auto &playerInfo = m_players[index];

    if(playerInfo.player->playbackState() == QMediaPlayer::StoppedState){
        playerInfo.currentIndex = type;
        playerInfo.player->setSource(playerInfo.mediaList[playerInfo.currentIndex]);
        playerInfo.player->play();
    }
    else{
        QTimer::singleShot(1500,this,[=](){
            //playerInfo.currentIndex = type;
            playerInfo.player->setSource(playerInfo.mediaList[type]);
            playerInfo.player->play();
        });
    }
}

void BGM_Controll::playPassMusic(RoleSex sex)
{
    //1.玩家的性别
    int index = sex == Man ? 0 : 1;
    //2.找到播放列表
    auto &playerInfo = m_players[index];
    //3.找到要播放的音乐  Pass1 ~ Pass4中的任意一个
    int random = QRandomGenerator::global()->bounded(4);
    playerInfo.currentIndex = Pass1 + random;
    playerInfo.player->setSource(playerInfo.mediaList[playerInfo.currentIndex]);
    //4.播放音乐
    playerInfo.player->play();
}

void BGM_Controll::playAssistMusic(AssistMusic type)
{
    auto &playerInfo = m_players[3];
    playerInfo.currentIndex = type;
    playerInfo.player->setSource(playerInfo.mediaList[playerInfo.currentIndex]);

    if(type == Dispatch){
        //循环播放
        connect(playerInfo.player,&QMediaPlayer::mediaStatusChanged,this,[=](QMediaPlayer::MediaStatus status){
            if(status == QMediaPlayer::EndOfMedia){
                playerInfo.player->setPosition(0);
                playerInfo.player->play();
            }
        });
    }
    else{
        //单次播放
        disconnect(playerInfo.player,&QMediaPlayer::mediaStatusChanged,this,nullptr);
    }

    playerInfo.player->play();
}

void BGM_Controll::stopAssistMusic()
{
    m_players[3].player->stop();
}

void BGM_Controll::playEndingMusic(bool isWin)
{
    auto &playerInfo = m_players[4];
    playerInfo.currentIndex = isWin ? 0 : 1;
    playerInfo.player->setSource(playerInfo.mediaList[playerInfo.currentIndex]);
    playerInfo.player->play();
}

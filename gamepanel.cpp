#include "gamepanel.h"
#include "ui_gamepanel.h"



GamePanel::GamePanel(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GamePanel)
{
    ui->setupUi(this);

    //1.背景图  一共有10张，每次显示的背景图片随机生成
    int num=QRandomGenerator::global()->bounded(10);//0~9
    //拼接背景图的路径
    QString path=QString(":/images/background-%1.png").arg(num+1);
    m_bpImage.load(path);

    //2.窗口的标题大小
    this->setWindowTitle("欢乐斗地主");
    this->setFixedSize(1000,650);

    //3.实例化游戏控制类对象
    gameControllInit();

    //4.玩家得分(更新)
    updatePlayerScore();

    //5.切割扑克牌图片
    //注意:游戏中52张扑克牌正面以及背面由一张图片显示，显示时需要进行切割
    initCardMap();

    //6.初始化游戏中的按钮组
    initButtonsGroup();

    //7.初始化玩家在窗口中的上下文环境（三名玩家扑克牌以及头像的显示位置）
    initPlayerContext();

    //8.扑克牌场景初始化
    initGameScene();

    //9.倒计时窗口初始化
    initCountDown();

    //定时器实例化
    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&GamePanel::onDispatchCard);

    //动画窗口实例化
    m_animation=new AnimationWindow(this);
    //游戏音乐对象实例化
    m_bgm = new BGM_Controll(this);

    //测试游戏胜利窗口动画效果
    //showEndingScorePanel();

    //测试特殊牌型的动画效果
    // QTimer::singleShot(5000,this,[=](){
    //     //showAnimation(Plane);
    //     //showAnimation(Bomb);
    //     showAnimation(JokerBomb);
    // });
}

GamePanel::~GamePanel()
{
    delete ui;
}

void GamePanel::gameControllInit()
{
    m_gameControll=new GameControll(this);
    m_gameControll->playerInit();
    //得到游戏中三个玩家的实例对象
    Robot *leftRobot=m_gameControll->getLeftRobot();
    Robot *rightRobot=m_gameControll->getRightRobot();
    UserPlayer *user=m_gameControll->getUserPlayer();
    //存储顺序：左侧机器人，右侧机器人，真人玩家
    m_playerList<<leftRobot<<rightRobot<<user;

    //处理某个玩家的状态变化
    connect(m_gameControll,&GameControll::playerStatusChanged,this,&GamePanel::onPlayerStatusChanged);

    connect(m_gameControll,&GameControll::notifyGrabLordBet,this,&GamePanel::onGrabLordBet);
    connect(m_gameControll,&GameControll::gameStatusChanged,this,&GamePanel::gameStatusProcess);
    //处理玩家出牌信号
    connect(m_gameControll,&GameControll::notifyPlayHand,this,&GamePanel::onDisposePlayHand);
    //处理发牌信号
    connect(leftRobot,&Player::notifyPickCards,this,&GamePanel::disposeCard);
    connect(rightRobot,&Player::notifyPickCards,this,&GamePanel::disposeCard);
    connect(user,&Player::notifyPickCards,this,&GamePanel::disposeCard);
}

void GamePanel::updatePlayerScore()
{
    ui->scorePanel->setScores(m_playerList[0]->getScore()
                              ,m_playerList[1]->getScore(),m_playerList[2]->getScore());
}

void GamePanel::initCardMap()
{
    //1.加载整张card.png大图片
    QPixmap pixmap(":/images/card.png");
    //2.计算每张扑克牌小图片的大小
    //注意：每张扑克牌图片的宽度和高度均相同 且没有空隙
    //大图中共有5行，13列，因此直接用大图的宽度高度除以13和5即可
    m_cardSize.setWidth(pixmap.width() / 13);
    m_cardSize.setHeight(pixmap.height() / 5);

    //3.取出每张扑克牌图片
    //注意：取小图方法：先得到每张小图左上角的坐标，加上宽高即可得到当前扑克牌图片
    //QPixmap中的copy(int x,int y,int width,int height)即可裁剪出参数指定的矩形区域的图片
    //扑克牌背景图
    m_cardBackgroud = pixmap.copy(2*m_cardSize.width(),4*m_cardSize.height()
                                  ,m_cardSize.width(),m_cardSize.height());
    //正常花色扑克牌图片（方片，梅花，红桃，黑桃）
    for(int i=0,suit=Card::Suit_Begin+1;suit<Card::Suit_End;++suit,++i){
        for(int j=0,pt=Card::Card_Begin+1;pt<Card::Card_SJ;++pt,++j){
            Card card((Card::CardPoint)pt,(Card::CardSuit)suit);
            //裁剪图片
            cropImage(pixmap,j*m_cardSize.width(),i*m_cardSize.height(),card);
        }
    }

    //大王和小王
    Card card;
    card.setPoint(Card::Card_SJ);
    card.setSuit(Card::Suit_Begin);
    cropImage(pixmap,0,4*m_cardSize.height(),card);

    card.setPoint(Card::Card_BJ);
    card.setSuit(Card::Suit_End);
    cropImage(pixmap,m_cardSize.width(),4*m_cardSize.height(),card);
}

//x,y为需要裁剪的图片左上角的坐标
void GamePanel::cropImage(QPixmap &pix, int x, int y,Card &card)
{
    QPixmap sub=pix.copy(x,y,m_cardSize.width(),m_cardSize.height());
    CardPanel *panel=new CardPanel(this);
    panel->setImage(sub,m_cardBackgroud);
    panel->setCard(card);
    panel->hide();
    m_cardMap.insert(card,panel);
    //接收扑克牌选择信号
    connect(panel,&CardPanel::cardSelected,this,&GamePanel::onCardSelected);
}

void GamePanel::initButtonsGroup()
{
    //初始化按钮组按钮
    ui->btnGroup->initButtons();
    //显示初始时的start这一页
    ui->btnGroup->selectPanel(ButtonGroup::Start);

    //处理按钮按下后发射的信号
    connect(ui->btnGroup,&ButtonGroup::startGame,this,[=](){
        //界面的初始化
        ui->btnGroup->selectPanel(ButtonGroup::Empty);
        m_gameControll->clearPlayerScore();
        updatePlayerScore();
        //修改游戏状态->发牌
        gameStatusProcess(GameControll::DispatchCard);
        //播放背景音乐
        m_bgm->startBGM(80);
    });

    //处理出牌
    connect(ui->btnGroup,&ButtonGroup::playHand,this,&GamePanel::onUserPlayHand);
    //处理跳过
    connect(ui->btnGroup,&ButtonGroup::pass,this,&GamePanel::onUserPass);
    //处理下注
    connect(ui->btnGroup,&ButtonGroup::betPoint,this,[=](int bet){
        m_gameControll->getUserPlayer()->grabLordBet(bet);
        ui->btnGroup->selectPanel(ButtonGroup::Empty);
    });
}

void GamePanel::initPlayerContext()
{
    //1.放置玩家扑克牌的区域
    QRect cardsRect[]={
        //x,y,width,height
        QRect(90,130,100,height()-200),                         //左侧机器人
        QRect(rect().right()-190,130,100,height()-200),  //右侧机器人
        QRect(250,rect().bottom()-120,width()-500,100) //真人玩家
    };

    //2.玩家出牌的区域
    QRect playHandRect[]={
        QRect(260,150,100,100),                                  //左侧机器人
        QRect(rect().right()-360,150,100,100),              //右侧机器人
        QRect(150,rect().bottom()-290,width()-300,105)    //真人玩家
    };

    //3.玩家头像显示的位置
    QPoint roleImgPos[]={
        QPoint(cardsRect[0].left()-80,cardsRect[0].height()/2+20),              //左侧机器人
        QPoint(cardsRect[1].right()+10,cardsRect[1].height()/2+20),           //右侧机器人
        QPoint(cardsRect[2].right()-10,cardsRect[2].top()-10)                     //真人玩家
    };

    //循环
    //取出非机器人玩家在m_playerList中对应的索引
    int index=m_playerList.indexOf(m_gameControll->getUserPlayer()); //2
    for(int i=0;i<m_playerList.size();i++){
        PlayerContext context;
        //真人玩家扑克牌水平排列，机器人玩家扑克牌垂直排列
        context.align = i == index ? Horizontal : Vertical;
        //真人玩家展示扑克牌正面，机器人玩家展示扑克牌背面
        context.isFrontSide = i == index ? true : false;
        context.cardRect=cardsRect[i];
        context.playHandRect=playHandRect[i];
        //提示信息
        context.info=new QLabel(this);
        context.info->resize(160,98);
        context.info->hide();
        //提示信息显示到出牌区域的中心位置
        QRect rect=playHandRect[i];
        QPoint pt(rect.left()+(rect.width()-context.info->width())/2,rect.top()+(rect.height()-context.info->height())/2);
        context.info->move(pt);
        //玩家的头像
        context.roleImg=new QLabel(this);
        context.roleImg->resize(84,120);
        context.roleImg->hide();
        context.roleImg->move(roleImgPos[i]);

        m_contextMap.insert(m_playerList[i],context);
    }

}

void GamePanel::initGameScene()
{
    //1.发牌区中的扑克牌
    m_baseCard=new CardPanel(this);
    m_baseCard->setImage(m_cardBackgroud,m_cardBackgroud);
    //2.发牌过程中移动的扑克牌
    m_moveCard=new CardPanel(this);
    m_moveCard->setImage(m_cardBackgroud,m_cardBackgroud);
    //3.最后的三张底牌（用于显示在窗口正上方）
    for(int i=0;i<3;i++){
        CardPanel *panel=new CardPanel(this);
        panel->setImage(m_cardBackgroud,m_cardBackgroud);
        m_last3Card.push_back(panel);
        panel->hide();
    }
    //扑克牌位置  (中心位置靠上100像素)
    m_baseCardPos = QPoint((width()-m_cardSize.width())/2,height()/2-100);
    m_baseCard->move(m_baseCardPos);
    m_moveCard->move(m_baseCardPos);

    //最后三张底牌的第一张牌的左上角的x坐标  10为扑克牌间的间隔
    int base=(width()-3*m_cardSize.width()-2*10)/2;
    for(int i=0;i<3;i++){
        m_last3Card[i]->move(base+(m_cardSize.width()+10)*i,20);
    }
}

void GamePanel::gameStatusProcess(GameControll::GameStatus status)
{
    //记录游戏状态
    m_gameStatus=status;
    //处理游戏状态
    switch(status){
    case GameControll::DispatchCard:{
        startDispatchCard();
        break;
    }
    case GameControll::CallingLord:{
        //取出三张底牌的数据
        CardList last3Card=m_gameControll->getSurplusCards().toCardList();
        //给底牌窗口设置图片
        for(int i=0;i<last3Card.size();i++){
            QPixmap front=m_cardMap[last3Card[i]]->getImage();
            m_last3Card[i]->setImage(front,m_cardBackgroud);
            m_last3Card[i]->hide();
        }
        //开始叫地主
        m_gameControll->startLordCard();
        break;
    }
    case GameControll::PlayingHand:{
        //隐藏发牌区的底牌和移动的牌
        m_baseCard->hide();
        m_moveCard->hide();
        //显示留给地主的三张底牌
        for(int i=0;i<m_last3Card.size();i++){
            m_last3Card[i]->show();
        }
        //隐藏各个玩家抢地主过程中的提示信息
        for(int i=0;i<m_playerList.size();i++){
            //注意需要对原数据进行修改而不是对副本修改，因此需要通过指针或引用保存
            PlayerContext &context = m_contextMap[m_playerList[i]];
            context.info->hide();
            //显示各个玩家的头像
            Player *player = m_playerList[i];
            QPixmap pixmap = loadRoleImage(player->getSex(),player->getDirection(),player->getRole());
            context.roleImg->setPixmap(pixmap);
            context.roleImg->show();
        }
        break;
    }
    }
}

void GamePanel::startDispatchCard()
{
    //重置每张卡牌的属性
    for(auto it=m_cardMap.begin();it!=m_cardMap.end();++it){
        it.value()->setSelected(false);
        it.value()->setFrontSide(true);
        it.value()->hide();
    }
    //隐藏三张底牌
    for(int i=0;i<m_last3Card.size();i++){
        m_last3Card.at(i)->hide();
    }
    //重置玩家的窗口上下文信息
    int index=m_playerList.indexOf(m_gameControll->getUserPlayer());
    for(int i=0;i<m_playerList.size();++i){
        m_contextMap[m_playerList[i]].lastCards.clear();
        m_contextMap[m_playerList[i]].info->hide();
        m_contextMap[m_playerList[i]].roleImg->hide();
        m_contextMap[m_playerList[i]].isFrontSide= i == index ? true : false;
    }
    //重置所有玩家的卡牌数据
    m_gameControll->resetCardData();
    //显示底牌
    m_baseCard->show();
    //隐藏按钮面板
    ui->btnGroup->selectPanel(ButtonGroup::Empty);
    //启动定时器 每10ms启动一次
    m_timer->start(10);
    //播放背景音乐
    m_bgm->playAssistMusic(BGM_Controll::Dispatch);
}

void GamePanel::onDispatchCard()
{
    //记录扑克牌的位置
    static int currMovePos = 0;
    //当前玩家
    Player * currPlayer=m_gameControll->getCurrentPlayer();
    if(currMovePos >= 100){
        //给玩家发一张牌
        Card card=m_gameControll->takeOneCard();
        currPlayer->storeDispatchCard(card);
        Cards cs(card);

        //disposeCard(currPlayer,cs);

        //切换当前玩家
        m_gameControll->setCurrentPlayer(currPlayer->getNextPlayer());
        currMovePos=0;
        //发牌动画
        cardMoveStep(currPlayer,currMovePos);
        //判断牌是否已经发完
        if(m_gameControll->getSurplusCards().cardCount() == 3){
            //终止计时器
            m_timer->stop();
            //切换游戏状态->叫地主
            gameStatusProcess(GameControll::CallingLord);
            //停止发牌音乐的播放
            m_bgm->stopAssistMusic();
            return;
        }
    }
    //移动扑克牌
    cardMoveStep(currPlayer,currMovePos);
    currMovePos+=15;
}

void GamePanel::cardMoveStep(Player *player,int currPos)
{
    //得到每个玩家的扑克牌区域
    QRect cardRect=m_contextMap[player].cardRect;
    //每个玩家扑克牌的单元步长
    int unit[]={
        (m_baseCardPos.x() - cardRect.right())/100,     //左
        (cardRect.left() - m_baseCardPos.x())/100,       //右
        (cardRect.top()-m_baseCardPos.y())/100          //中
    };

    //每次窗口移动的时候每个玩家对应的牌的实时坐标位置
    QPoint pos[]={
        QPoint(m_baseCardPos.x()-currPos*unit[0],m_baseCardPos.y()),
        QPoint(m_baseCardPos.x()+currPos*unit[1],m_baseCardPos.y()),
        QPoint(m_baseCardPos.x(),m_baseCardPos.y()+currPos*unit[2])
    };

    //移动扑克牌窗口
    int index=m_playerList.indexOf(player);
    m_moveCard->move(pos[index]);

    //临界状态的处理
    if(currPos == 0){
        //起始
        m_moveCard->show();
    }
    if(currPos == 100){
        m_moveCard->hide();
    }
}

void GamePanel::disposeCard(Player *player, Cards &cards)
{
    CardList list=cards.toCardList();
    for(int i=0;i<list.size();i++){
        CardPanel *panel=m_cardMap[list[i]];
        panel->setOwner(player);
    }

    //更新扑克牌在界面中的显示
    updatePlayerCards(player);
}

void GamePanel::updatePlayerCards(Player *player)
{
    Cards cards=player->getCards();
    CardList list=cards.toCardList();

    m_cardsRect = QRect();//用于记录非机器人玩家的出牌区域
    m_userCards.clear();
    //取出展示扑克牌的区域
    int cardSpace=20;
    QRect cardRect=m_contextMap[player].cardRect;
    for(int i=0;i<list.size();i++){
        CardPanel *panel=m_cardMap[list[i]];
        panel->show();
        panel->raise();//使得窗口每次都显示在父窗口的上方
        panel->setFrontSide(m_contextMap[player].isFrontSide);
        //水平或者垂直展示
        if(m_contextMap[player].align == Horizontal){
            int leftX=cardRect.left() + (cardRect.width() - (list.size()-1)*cardSpace - panel->width())/2;
            int topY=cardRect.top() + (cardRect.height()-m_cardSize.height())/2;
            if(panel->isSelected()){
                //当前扑克牌被选中，有一个弹跳效果 y坐标变小
                topY-=10;
            }
            panel->move(leftX + cardSpace*i,topY);
            //只有最后一张显示完整宽度，其余均显示间隙宽度的部分
            m_cardsRect = QRect(leftX,topY,cardSpace*i + m_cardSize.width(),m_cardSize.height());
            int currWidth = 0;
            if(list.size() - 1 == i){
                //最后一张牌
                currWidth = m_cardSize.width();//完整宽度
            }
            else{
                //不是最后一张牌
                currWidth = cardSpace;//间隙宽度
            }
            QRect cardRect(leftX + cardSpace*i,topY,currWidth,m_cardSize.height());
            m_userCards.insert(panel,cardRect);
        }
        else{
            int leftX=cardRect.left()+(cardRect.width()-m_cardSize.width())/2;
            int topY=cardRect.top()+(cardRect.height()-(list.size()-1)*cardSpace-panel->height())/2;
            panel->move(leftX,topY + i*cardSpace);
        }
    }

    //显示玩家打出的牌
    //得到当前玩家的出牌区域以及本轮打出的牌
    QRect playCardRect = m_contextMap[player].playHandRect;
    Cards lastCards = m_contextMap[player].lastCards;
    if(!lastCards.isEmpty()){
        int playSpacing = 24;//打出的扑克牌堆叠显示的间隙
        CardList lastCardList = lastCards.toCardList();
        CardList::ConstIterator itPlayed = lastCardList.constBegin();
        for(int i=0;itPlayed !=lastCardList.constEnd();itPlayed++,i++){
            CardPanel *panel = m_cardMap[*itPlayed];
            panel->setFrontSide(true);
            panel->raise(); //设置堆叠显示
            //将打出的牌移动到出牌区域
            if(m_contextMap[player].align == Horizontal){
                //水平显示
                int leftBase = playCardRect.left() +
                               (playCardRect.width() - (lastCardList.size() - 1)*playSpacing - panel->width()) / 2;
                int top = playCardRect.top() + (playCardRect.height() - panel->height()) / 2;
                panel->move(leftBase + i*playSpacing,top);
            }
            else{
                //垂直显示
                //注意：由于垂直方向空间有限，不能将其进行垂直居中，否则会与下面真人玩家的区域重叠
                //因此topBase直接指定为出牌区域最上方的y坐标
                int left = playCardRect.left() + (playCardRect.width() - panel->width()) / 2;
                int topBase = playCardRect.top();
                panel->move(left,topBase + i*playSpacing);
            }
            panel->show();
        }
    }
}

void GamePanel::showAnimation(AnimationType type, int bet)
{
    switch (type) {
    case AnimationType::SeqPair:
    case AnimationType::SeqSingle:
        //设置动画窗口大小与图片
        m_animation->setFixedSize(250,150);
        m_animation->move((width() - m_animation->width()) / 2,200);
        m_animation->showSequence((AnimationWindow::Type)type);
        break;
    case AnimationType::Plane:
    {
        m_animation->setFixedSize(800,75);
        m_animation->move((width() - m_animation->width()) / 2,200);
        m_animation->showPlane();
        break;
    }
    case AnimationType::Bomb:
    {
        m_animation->setFixedSize(180,200);
        m_animation->move((width() - m_animation->width()) / 2,(height() - m_animation->width()) / 2 - 70);
        m_animation->showBomb();
        break;
    }
    case AnimationType::JokerBomb:
    {
        m_animation->setFixedSize(250,200);
        m_animation->move((width() - m_animation->width()) / 2,(height() - m_animation->width()) / 2 - 70);
        m_animation->showJokerBomb();
        break;
    }
    case AnimationType::Bet:{
        //设置动画窗口大小与图片（例如 :/images/score1.png）大小一致（160*98）
        m_animation->setFixedSize(160,98);
        m_animation->move((width() - m_animation->width()) / 2,(height() - m_animation->height()) / 2 - 140);
        m_animation->showBetScore(bet);
        break;

    }
    default:
        break;
    }
    //注意：每一种动画窗口在显示了一段指定的时间后便隐藏，但下次调用时还需要显示别的动画
    //因此需要让其show一下
    m_animation->show();
}

void GamePanel::hidePlayerDisposeCards(Player *player)
{
    /*处理思路：首先根据传入的玩家对象player从m_contextMap容器中获取到与
        该玩家相关的扑克牌数据（该玩家打出的牌lastCards）
        然后根据lastCards在m_cardMap容器中获取到这些打出去的牌的窗口对象
        最后通过窗口对象调用hide方法隐藏即可
    */
    auto it=m_contextMap.find(player);
    if(it != m_contextMap.end()){
        if(it.value().lastCards.isEmpty()){
            //打出的牌为空说明该玩家上次pass了，需要将相应的提示信息隐藏起来
            it.value().info->hide();
        }
        else{
            //Cards --> Card
            CardList list = it.value().lastCards.toCardList();
            for(auto last = list.begin();last != list.end();last++){
                m_cardMap[*last]->hide();
            }
        }
        //清空上一次打出的牌的数据
        it->lastCards.clear();
    }
}

QPixmap GamePanel::loadRoleImage(Player::Sex sex, Player::Direction direct, Player::Role role)
{
    //找图片
    QVector<QString> lordMan;
    QVector<QString> lordWoman;
    QVector<QString> farmerMan;
    QVector<QString> farmerWoman;
    lordMan<<":/images/lord_man_1.png"<<":/images/lord_man_2.png";
    lordWoman<<":/images/lord_woman_1.png"<<":/images/lord_woman_2.png";
    farmerMan<<":/images/farmer_man_1.png"<<":/images/farmer_man_2.png";
    farmerWoman<<":/images/farmer_woman_1.png"<<":/images/farmer_woman_2.png";

    //加载图片QPixmap QImage
    //注意：以上所有图片上的人的朝向都是向右，而有着朝向向左的需求，因此需要使用QImage类中
    //的镜像来实现，QPixmap类并没有提供该功能
    QImage image;
    int random=QRandomGenerator::global()->bounded(2);
    if(sex == Player::MAN && role == Player::LORD){
        //男地主
        image.load(lordMan[random]);
    }
    else if(sex == Player::MAN && role == Player::FARMER){
        //男农民
        image.load(farmerMan[random]);
    }
    else if(sex == Player::WOMAN && role == Player::LORD){
        //女地主
        image.load(lordWoman[random]);
    }
    else if(sex == Player::WOMAN && role == Player::FARMER){
        //女农民
        image.load(farmerWoman[random]);
    }

    QPixmap pixmap;
    if(direct == Player::LEFT){
        //显示在窗口左侧则不需要镜像处理，直接转换
        pixmap = QPixmap::fromImage(image);
    }
    else if(direct == Player::RIGHT){
        //显示在窗口右侧则需要水平镜像处理后再转换
        pixmap = QPixmap::fromImage(image.mirrored(true,false));
    }
    return pixmap;
}

void GamePanel::showEndingScorePanel()
{
    //为方便测试使得显示玩家得分的窗口在当前主界面窗口出现后两秒出现
    // QTimer::singleShot(2000,this,[=](){
    //     bool isLord = m_gameControll->getUserPlayer()->getRole() == Player::LORD ? true : false;
    //     bool isWin = m_gameControll->getUserPlayer()->getIsWin();
    //     EndingPanel *panel = new EndingPanel(isLord,isWin);
    //     panel->show();
    //     panel->move((width()-panel->width()) / 2,(height() - panel->heightMM()) / 2);
    //     panel->setPlayerScore(m_gameControll->getLeftRobot()->getScore(),
    //                           m_gameControll->getRightRobot()->getScore(),
    //                           m_gameControll->getUserPlayer()->getScore());
    // });

    bool isLord = m_gameControll->getUserPlayer()->getRole() == Player::LORD ? true : false;
    bool isWin = m_gameControll->getUserPlayer()->getIsWin();
    EndingPanel *panel = new EndingPanel(isLord,isWin,this);
    panel->show();
    panel->move((width()-panel->width()) / 2,- panel->height());
    panel->setPlayerScore(m_gameControll->getLeftRobot()->getScore(),
                          m_gameControll->getRightRobot()->getScore(),
                          m_gameControll->getUserPlayer()->getScore());

    if(isWin){
        m_bgm->playEndingMusic(true);
    }
    else{
        m_bgm->playEndingMusic(false);
    }

    QPropertyAnimation *animation = new QPropertyAnimation(panel,"geometry",this);
    //设置动画持续的时间
    animation->setDuration(1500);   //1.5秒
    //设置窗口的起始位置和终止位置
    animation->setStartValue(QRect(panel->x(),panel->y(),panel->width(),panel->height()));
    animation->setEndValue(QRect((width()-panel->width()) / 2,(height() - panel->height()) / 2
                                 ,panel->width(),panel->height()));
    //设置窗口的运动曲线
    animation->setEasingCurve(QEasingCurve(QEasingCurve::OutBounce));
    //播放动画效果
    animation->start();

    //处理游戏继续信号
    connect(panel,&EndingPanel::contiueGame,this,[=](){
        panel->close();
        panel->deleteLater();
        animation->deleteLater();
        ui->btnGroup->selectPanel(ButtonGroup::Empty);
        gameStatusProcess(GameControll::DispatchCard);
        //新的一局游戏开始，播放背景音乐
        m_bgm->startBGM(80);
    });
}

void GamePanel::initCountDown()
{
    m_countDown = new CountDown(this);
    m_countDown->move((width() - m_countDown->width()) / 2,(height() - m_countDown->height()) / 2 + 30);
    //计时器中两个信号的处理（剩5秒以及时间结束）
    connect(m_countDown,&CountDown::notMuchTime,this,[=](){
        //播放提示音乐
        m_bgm->playAssistMusic(BGM_Controll::Alert);
    });
    //时间到了则直接跳过出牌
    connect(m_countDown,&CountDown::timeOut,this,&GamePanel::onUserPass);
    UserPlayer *userPlayer = m_gameControll->getUserPlayer();
    connect(userPlayer,&UserPlayer::startCountDown,this,[=](){
        if(m_gameControll->getPendPlayer() != userPlayer && m_gameControll->getPendPlayer() != nullptr){
            m_countDown->showCountDown();
        }
    });
}

void GamePanel::onPlayerStatusChanged(Player *player, GameControll::PlayerStatus status)
{
    switch(status){
    case GameControll::ThinkingForCallLord:{
        //机器人玩家的相关操作由相应程序实现，不需要切换按钮组显示
        //而真人玩家则需要自行叫地主，需要显示按钮组
        if(player == m_gameControll->getUserPlayer()){
            ui->btnGroup->selectPanel(ButtonGroup::CallLord,m_gameControll->getPlayerMaxBet());
        }
        break;
    }
    case GameControll::ThinkingForPlayHand:{
        //1.隐藏上一轮打出的牌
        hidePlayerDisposeCards(player);

        if(player == m_gameControll->getUserPlayer()){
            //取出出牌玩家的对象
            Player *pendPlayer = m_gameControll->getPendPlayer();
            //注意：游戏刚开始时当前出牌玩家pendPlayer为空
            if(pendPlayer == m_gameControll->getUserPlayer() || pendPlayer == nullptr){
                ui->btnGroup->selectPanel(ButtonGroup::PlayCard);
            }
            else{
                ui->btnGroup->selectPanel(ButtonGroup::PassOrPlay);
            }
        }
        else{
            ui->btnGroup->selectPanel(ButtonGroup::Empty);
        }
        break;
    }
    case GameControll::Winning:{
        //停止背景音乐的播放
        m_bgm->stopBGM();

        m_contextMap[m_gameControll->getLeftRobot()].isFrontSide=true;
        m_contextMap[m_gameControll->getRightRobot()].isFrontSide=true;
        updatePlayerCards(m_gameControll->getLeftRobot());
        updatePlayerCards(m_gameControll->getRightRobot());
        //更新玩家的得分
        updatePlayerScore();
        m_gameControll->setCurrentPlayer(player);
        showEndingScorePanel();
        break;
    }
    default:
        break;
    }
}

void GamePanel::onGrabLordBet(Player *player, int bet, bool flag)
{
    //显示抢地主的信息提示
    PlayerContext context=m_contextMap[player];
    if(bet == 0){
        context.info->setPixmap(QPixmap(":/images/buqinag.png"));
    }
    else{
        if(flag){
            context.info->setPixmap(QPixmap(":/images/jiaodizhu.png"));
        }
        else{
            context.info->setPixmap(QPixmap(":/images/qiangdizhu.png"));
        }
        //显示叫地主的分数
        showAnimation(Bet,bet);
    }
    context.info->show();

    //播放背景音乐
    m_bgm->playerRobLordMusic(bet,(BGM_Controll::RoleSex)player->getSex(),flag);
}

void GamePanel::onDisposePlayHand(Player *player, Cards &cards)
{
    //存储玩家打出的牌
    auto it = m_contextMap.find(player);
    it.value().lastCards = cards;
    //2.根据出牌的牌型播放对应的游戏特效
    PlayHand hand(cards);
    PlayHand::HandType type = hand.getHandType();
    if(type == PlayHand::Hand_Plane || type == PlayHand::Hand_Plane_Two_Pair
        || type == PlayHand::Hand_Plane_Two_Single){
        showAnimation(Plane);
    }
    else if(type == PlayHand::Hand_Seq_Pair){
        showAnimation(SeqPair);
    }
    else if(type == PlayHand::Hand_Seq_Single){
        showAnimation(SeqSingle);
    }
    else if(type == PlayHand::Hand_Bomb){
        showAnimation(Bomb);
    }
    else if(type == PlayHand::Hand_Bomb_Jokers){
        showAnimation(JokerBomb);
    }
    //如果玩家打出的牌是空牌（不出牌），显示提示信息
    if(cards.isEmpty()){
        //对于QMap容器  it-> 可以直接取到it迭代器指向键值对的value
        it->info->setPixmap(QPixmap(":/images/pass.png"));
        it->info->show();
        //播放不要/不出的背景音乐
        m_bgm->playPassMusic((BGM_Controll::RoleSex)player->getSex());
    }
    else{
        if(m_gameControll->getPendPlayer() == player || m_gameControll->getPendPlayer() == nullptr){
            m_bgm->playCardMusic(cards,true,(BGM_Controll::RoleSex)player->getSex());
        }
        else{
            m_bgm->playCardMusic(cards,false,(BGM_Controll::RoleSex)player->getSex());
        }
    }

    //3.更新玩家剩余的牌
    updatePlayerCards(player);
    //4.播放提示音乐
    //判断玩家剩余牌的数量
    if(player->getCards().cardCount() == 2){
        m_bgm->playLastMusic(BGM_Controll::Last2,(BGM_Controll::RoleSex)player->getSex());
    }
    else if(player->getCards().cardCount() == 1){
        m_bgm->playLastMusic(BGM_Controll::Last1,(BGM_Controll::RoleSex)player->getSex());
    }
}

void GamePanel::onCardSelected(Qt::MouseButton button)
{
    //1.判断是不是出牌状态
    if(m_gameStatus == GameControll::DispatchCard
        || m_gameStatus == GameControll::CallingLord){
        return;
    }
    //2.判断发出信号的牌的所有者是不是当前用户玩家
    //注意：sender()返回一个指向发送当前信号的对象的QObject指针
    CardPanel *panel = (CardPanel*)sender();
    if(panel->getOwner() != m_gameControll->getUserPlayer()){
        return;
    }
    //3.保存当前被选中的牌的窗口对象
    m_currSelectCard = panel;
    //4.判断参数的鼠标键是左键还是右键
    if(button == Qt::LeftButton){
        //设置扑克牌的选中状态
        //注意：取反的原因是：当前扑克牌在选中的状态下点了左键：取消选中
        //                                      当前扑克牌在未选中的状态下点了左键：选中
        panel->setSelected(!panel->isSelected());
        //更新扑克牌在窗口中的显示
        updatePlayerCards(panel->getOwner());
        //保存或删除扑克牌窗口对象
        QSet<CardPanel*>::const_iterator it = m_selectCards.find(panel);
        if(it == m_selectCards.end()){
            //没有找到当前扑克牌窗口（说明没有被选中，此时点击左键需要选中该扑克牌，因此需要加到容器中
            m_selectCards.insert(panel);
        }
        else{
            //找到说明当前扑克牌被选中，此时点击左键需要取消选中该扑克牌，因此需要从容器中删除
            m_selectCards.erase(it);
        }
        //播放选牌音乐
        m_bgm->playAssistMusic(BGM_Controll::SelectCard);
    }
    else if(button == Qt::RightButton){
        //直接出牌
        //调用出牌按钮的槽函数
        onUserPlayHand();
    }
}

void GamePanel::onUserPlayHand()
{
    //判断游戏状态
    if(m_gameStatus != GameControll::PlayingHand){
        return;
    }
    //判断玩家是不是用户玩家
    if(m_gameControll->getCurrentPlayer() != m_gameControll->getUserPlayer()){
        return;
    }
    //判断要出的牌是否为空
    if(m_selectCards.isEmpty()){
        return;
    }
    //得到要打出的牌的牌型
    Cards cs;
    for(auto it = m_selectCards.begin();it != m_selectCards.end();it++){
        Card card = (*it)->getCard();
        cs.add(card);
    }
    PlayHand hand(cs);
    PlayHand::HandType type = hand.getHandType();
    if(type == PlayHand::Hand_Unkown){
        return;
    }
    //判断当前玩家的牌能不能压住上一家的牌
    if(m_gameControll->getPendPlayer() != m_gameControll->getUserPlayer()){
        Cards cards = m_gameControll->getPendCards();
        if(!hand.canBeat(PlayHand(cards))){
            return;
        }
    }
    m_countDown->stopCountDown();
    //通过玩家对象出牌
    m_gameControll->getUserPlayer()->playHand(cs);
    //清空容器
    m_selectCards.clear();
}

void GamePanel::onUserPass()
{
    m_countDown->stopCountDown();
    //判断是不是用户玩家
    Player *currPlayer = m_gameControll->getCurrentPlayer();
    Player *userPlayer = m_gameControll->getUserPlayer();
    if(currPlayer != userPlayer){
        return;
    }
    //判断当前用户玩家是不是上一次出牌的玩家（可不处理）
    Player *pendPlayer = m_gameControll->getPendPlayer();
    if(pendPlayer == userPlayer || pendPlayer == nullptr){
        return;
    }
    //打出一个空的cards对象
    Cards empty;
    userPlayer->playHand(empty);
    //清空用户选择的牌（玩家可能选择了一些牌，但没有打出去）
    for(auto it = m_selectCards.begin();it != m_selectCards.end();it++){
        (*it)->setSelected(false);
    }
    m_selectCards.clear();
    //更新玩家待出牌区域的牌
    updatePlayerCards(userPlayer);
}

void GamePanel::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    p.drawPixmap(rect(),m_bpImage);
}

void GamePanel::mouseMoveEvent(QMouseEvent *ev)
{
    //注意：该事件可能有许多触发方式，应该使用ev->buttons
    //多个按钮可能同时按下：ev->button() 返回的是事件发生时发生变化的按钮
    //（即刚刚被按下或释放的按钮），而 ev->buttons() 返回的是当前所有按下的按钮状态（用位掩码表示）。
    if(ev->buttons()  & Qt::LeftButton){
        //左键进行框选
        QPoint pt = ev->pos();
        if(!m_cardsRect.contains(pt)){
            m_currSelectCard = nullptr;
        }
        else{
            QList<CardPanel*> list = m_userCards.keys();
            for(int i=0;i<list.size();i++){
                CardPanel *panel = list[i];
                if(m_userCards[panel].contains(pt) && m_currSelectCard != panel){
                    //点击这张扑克牌
                    panel->clicked();
                    m_currSelectCard = panel;
                }
            }
        }
    }
}

#ifndef GAMEPANEL_H
#define GAMEPANEL_H

//游戏窗口类，实现游戏的主界面

//注意：paintEvent()函数重写一般都是用来将某些图片加载到一个pixmap对象中
//然后通过QPainter类将pixmap画到当前窗口

#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QRandomGenerator>
#include <QVector>
#include <QMap>
#include <QLabel>
#include <QTimer>
#include <QImage>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QEasingCurve>

#include "gamecontroll.h"
#include "player.h"
#include "cardpanel.h"
#include "animationwindow.h"
#include "endingpanel.h"
#include "countdown.h"
#include "bgm_controll.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class GamePanel;
}
QT_END_NAMESPACE

class GamePanel : public QMainWindow
{
    Q_OBJECT

public:
    GamePanel(QWidget *parent = nullptr);
    ~GamePanel();

    //动画类型
    enum AnimationType{
        SeqSingle,SeqPair,Plane,JokerBomb,Bomb,Bet
    };

    //初始化游戏控制类相关信息
    void gameControllInit();
    //更新分数面板的分数
    void updatePlayerScore();
    //切割并存储图片
    void initCardMap();
    //裁剪图片
    void cropImage(QPixmap &pix,int x,int y,Card &card);

    //初始化游戏按钮组
    void initButtonsGroup();
    //初始化玩家在窗口中的上下文环境
    void initPlayerContext();
    //初始化游戏场景
    void initGameScene();
    //处理游戏的状态
    void gameStatusProcess(GameControll::GameStatus status);
    //发牌
    void startDispatchCard();

    //定时器的处理动作
    void onDispatchCard();
    //扑克牌移动
    void cardMoveStep(Player *player,int currPos);
    //处理分发得到的扑克牌
    void disposeCard(Player *player,Cards &cards);
    //更新扑克牌在界面中的显示
    void updatePlayerCards(Player *player);
    //显示特效动画
    void showAnimation(AnimationType type,int bet = 0);
    //隐藏玩家打出的牌
    void hidePlayerDisposeCards(Player*player);
    //加载玩家头像
    QPixmap loadRoleImage(Player::Sex sex,Player::Direction direct,Player::Role role);
    //显示玩家的最终得分
    void showEndingScorePanel();
    //初始化闹钟倒计时
    void initCountDown();

    //槽函数
    void onPlayerStatusChanged(Player *player,GameControll::PlayerStatus status);
    //处理玩家抢地主
    void onGrabLordBet(Player *player,int bet,bool flag);
    //处理玩家出牌
    void onDisposePlayHand(Player *player,Cards &cards);
    //处理玩家选牌
    void onCardSelected(Qt::MouseButton button);
    //处理用户玩家出牌
    void onUserPlayHand();
    //处理用户玩家放弃出牌
    void onUserPass();

protected:
    //重写事件处理函数
    void paintEvent(QPaintEvent *ev);
    //鼠标移动事件（用于实现鼠标框选扑克牌的功能）
    void mouseMoveEvent(QMouseEvent *ev);

private:
    //扑克牌对齐方式枚举
    enum CardAlign{Horizontal,Vertical};
    //玩家游戏信息结构体
    struct PlayerContext{
        //1.玩家扑克牌显示的区域
        QRect cardRect;
        //2.出牌的区域
        QRect playHandRect;
        //3.扑克牌的对齐方式
        CardAlign align;
        //4.扑克牌显示正面还是背面
        bool isFrontSide;
        //5.游戏过程中的提示信息(例如：不出)
        QLabel *info;
        //6.玩家的头像
        QLabel *roleImg;
        //7.玩家打出的牌
        Cards lastCards;
    };

    Ui::GamePanel *ui;

    QPixmap m_bpImage;//背景图片
    GameControll *m_gameControll;//游戏控制类对象
    QVector<Player*> m_playerList;//保存游戏玩家对象
    QMap<Card,CardPanel*> m_cardMap;//存储扑克牌及其对应窗口的容器
    QSize m_cardSize;//每张扑克牌图片的大小（宽度和高度）
    QPixmap m_cardBackgroud;//扑克牌背面图片
    QMap<Player*,PlayerContext> m_contextMap;//把玩家对象作为键值存储游戏信息
    CardPanel *m_baseCard;//基本牌窗口对象
    CardPanel *m_moveCard;//游戏发牌时移动的扑克牌窗口对象
    QVector<CardPanel*> m_last3Card;//最后三张底牌窗口对象
    QPoint m_baseCardPos;//基本扑克牌坐标
    GameControll::GameStatus m_gameStatus;//游戏状态
    QTimer *m_timer;//定时器
    AnimationWindow *m_animation;//动画窗口
    CardPanel *m_currSelectCard;//当前选中的牌的窗口对象
    QSet<CardPanel*> m_selectCards;//存储选中的窗口对象的容器
    QRect m_cardsRect;//非机器人玩家的扑克牌区域
    QHash<CardPanel*,QRect> m_userCards;//存储非机器人玩家的每张卡牌窗口对应的区域
    CountDown *m_countDown;//倒计时
    BGM_Controll *m_bgm;//游戏音乐

};
#endif // GAMEPANEL_H

#ifndef ANIMATIONWINDOW_H
#define ANIMATIONWINDOW_H

//游戏动画窗口类 负责实现对游戏中特定牌型打出或是叫地主抢地主时玩家下注的分数等的动画

#include <QPaintEvent>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QTimer>

class AnimationWindow : public QWidget
{
    Q_OBJECT
public:
    enum Type{Sequence,Pair};
    explicit AnimationWindow(QWidget *parent = nullptr);

    //显示下注分数
    void showBetScore(int bet);
    //显示顺子和连对
    void showSequence(Type type);
    //显示王炸
    void showJokerBomb();
    //显示炸弹
    void showBomb();
    //显示飞机
    void showPlane();

protected:
    void paintEvent(QPaintEvent *ev);

signals:

private:
    QPixmap m_image;//用于绘制窗口图片的对象
    int m_index;//记录图片索引
    int m_x;//“飞机”图片的x坐标
};

#endif // ANIMATIONWINDOW_H

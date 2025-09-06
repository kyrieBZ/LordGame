#ifndef CARDPANEL_H
#define CARDPANEL_H

#include <QWidget>
#include <QPixmap>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>

#include "card.h"
#include "player.h"

//扑克牌窗口类，负责实现与游戏中单张扑克牌的显示

class CardPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CardPanel(QWidget *parent = nullptr);

    //设置图片的函数
    void setImage(QPixmap &front,QPixmap &back);
    QPixmap getImage();

    //记录扑克牌显示哪一面 (设置m_isFront)
    void setFrontSide(bool flag);
    //判断当前的扑克牌显示的是哪一面
    bool isFrontSide();

    //记录窗口是否被选中 (设置)
    void setSelected(bool flag);
    //判断窗口是否被选中
    bool isSelected();

    //扑克牌的花色以及点数
    void setCard(Card &card);
    Card getCard();

    //扑克牌的所有者
    void setOwner(Player *player);
    Player* getOwner();

    //模拟扑克牌的点击事件
    void clicked();

protected:
    //绘图事件处理
    void paintEvent(QPaintEvent *event);
    //重写鼠标按下事件
    void mousePressEvent(QMouseEvent *event);

signals:
    //鼠标选择扑克牌
    //注意：鼠标左键选择则是点选，鼠标右键选择则直接出牌
    void cardSelected(Qt::MouseButton button);

private:
    QPixmap m_front;
    QPixmap m_back;
    bool m_isFront;//标识扑克牌对象窗口当前是正面还是背面
    bool m_isSelect;//标识当前扑克牌窗口是否被选中
    Card m_card;//扑克牌
    Player* m_player;//玩家
};

#endif // CARDPANEL_H

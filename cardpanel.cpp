#include "cardpanel.h"

CardPanel::CardPanel(QWidget *parent)
    : QWidget{parent}
{
    m_isFront=true;//默认显示扑克牌的正面

}

void CardPanel::setImage(QPixmap &front, QPixmap &back)
{
    this->m_front=front;
    this->m_back=back;

    //设置该窗口与扑克牌图片的大小一致
    setFixedSize(m_front.size());

    //更新窗口图片绘制
    update();
}

QPixmap CardPanel::getImage()
{
    //注意：每张扑克牌对象的背面图片均一致，不需要获取
    return m_front;
}

void CardPanel::setFrontSide(bool flag)
{
    m_isFront=flag;
}

bool CardPanel::isFrontSide()
{
    //为true则正面，为false则反面
    return m_isFront;
}

void CardPanel::setSelected(bool flag)
{
    m_isSelect=flag;
}

bool CardPanel::isSelected()
{
    //为true则表示选中，为false表示未选中
    return m_isSelect;
}

void CardPanel::setCard(Card &card)
{
    m_card=card;
}

Card CardPanel::getCard()
{
    return m_card;
}

void CardPanel::setOwner(Player *player)
{
    m_player=player;
}

Player *CardPanel::getOwner()
{
    return m_player;
}

void CardPanel::clicked()
{
    emit cardSelected(Qt::LeftButton);
}

void CardPanel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(m_isFront){
        //绘制正面图片  注意：rect()可以获取到当前窗口的大小
        painter.drawPixmap(rect(),m_front);
    }
    else{
        //绘制背面
        painter.drawPixmap(rect(),m_back);
    }
}

void CardPanel::mousePressEvent(QMouseEvent *event)
{
    emit cardSelected(event->button());
}

#include "mybutton.h"

MyButton::MyButton(QWidget *parent)
    : QPushButton{parent}
{}

void MyButton::setImage(QString normal, QString hover, QString pressed)
{
    m_normal=normal;
    m_hover=hover;
    m_pressed=pressed;
    m_pixmap.load(m_normal);
}

void MyButton::mousePressEvent(QMouseEvent *ev)
{
    //鼠标左键按下时加载m_pressed图片
    if(ev->button() == Qt::LeftButton){
        m_pixmap.load(m_pressed);
        update();
    }

    //注意：子类重写该函数后鼠标按下并不发送click信号
    //方法一：再次调用父类QPushButton中的mousePressEvent()函数发送
    //方法二：在子类中重新定义一个信号来发送
    QPushButton::mousePressEvent(ev);
}

void MyButton::mouseReleaseEvent(QMouseEvent *ev)
{
    //鼠标左键释放时加载m_normal图片
    if(ev->button() == Qt::LeftButton){
        m_pixmap.load(m_normal);
        update();
    }

    //这里同样要重新调用父类QPushButton中的mouseReleaseEvent()函数
    QPushButton::mouseReleaseEvent(ev);
}

void MyButton::enterEvent(QEnterEvent *ev)
{
    m_pixmap.load(m_hover);
    update();
}

void MyButton::leaveEvent(QEvent *ev)
{
    m_pixmap.load(m_normal);
    update();
}

void MyButton::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    p.drawPixmap(rect(),m_pixmap);
}

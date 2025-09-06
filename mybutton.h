#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include <QEvent>
#include <QPaintEvent>
#include <QPainter>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = nullptr);

    //设置图片 一共有三种状态分别用三张图片来显示
    void setImage(QString normal,QString hover,QString pressed);

protected:
    //鼠标按下
    void mousePressEvent(QMouseEvent *ev);
    //鼠标释放
    void mouseReleaseEvent(QMouseEvent *ev);
    //鼠标进入
    void enterEvent(QEnterEvent *ev);
    //鼠标离开
    void leaveEvent(QEvent *ev);
    //绘图
    void paintEvent(QPaintEvent *ev);

signals:

private:
    //三种状态对应的图片的路径
    QString m_normal;
    QString m_hover;
    QString m_pressed;
    QPixmap m_pixmap;
};

#endif // MYBUTTON_H

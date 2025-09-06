#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <QPaintEvent>
#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>

//倒计时窗口类，负责实现用户玩家一段时间不出牌后自动跳过这一效果

class CountDown : public QWidget
{
    Q_OBJECT
public:
    explicit CountDown(QWidget *parent = nullptr);

    void showCountDown();//显示倒计时
    void stopCountDown();//停止倒计时

signals:
    void notMuchTime();//倒计时即将结束提示信号（剩余5秒）
    void timeOut();//倒计时结束信号（用于通知主窗口）
protected:
    void paintEvent(QPaintEvent *ev);

private:
    QPixmap m_clock;//倒计时时钟图片
    QPixmap m_number;//倒计时数字
    QTimer *m_timer;//倒计时数字变化定时器
    int m_count;//定时器总时长
};

#endif // COUNTDOWN_H

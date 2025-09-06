#ifndef LOADING_H
#define LOADING_H

//加载窗口类，负责实现进入游戏时的加载动画

#include <QWidget>
#include <QPaintEvent>
#include <QPixmap>
#include <QPainter>
#include <QTimer>

#include "gamepanel.h"

class Loading : public QWidget
{
    Q_OBJECT
public:
    explicit Loading(QWidget *parent = nullptr);

signals:

protected:
    void paintEvent(QPaintEvent *event);

private:
    QPixmap m_bk;//加载背景图
    QPixmap m_progress;//加载进度条
    int m_dist = 15;//记录当前子进度条的宽度
};

#endif // LOADING_H

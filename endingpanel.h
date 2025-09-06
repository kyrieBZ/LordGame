#ifndef ENDINGPANEL_H
#define ENDINGPANEL_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QPushButton>

#include "scorepanel.h"

class EndingPanel : public QWidget
{
    Q_OBJECT
public:
    explicit EndingPanel(bool isLord,bool isWin,QWidget *parent = nullptr);
    //设置玩家得分
    void setPlayerScore(int left,int right,int user);

signals:
    void contiueGame();//继续游戏
protected:
    void paintEvent(QPaintEvent *ev);

private:
    QPixmap m_bk;
    QLabel *m_title;
    ScorePanel *m_score;
    QPushButton *m_continue;
};

#endif // ENDINGPANEL_H

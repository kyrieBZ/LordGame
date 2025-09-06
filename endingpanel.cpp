#include "endingpanel.h"

EndingPanel::EndingPanel(bool isLord,bool isWin,QWidget *parent)
    : QWidget{parent}
{
    m_bk.load(":/images/gameover.png");
    setFixedSize(m_bk.size());

    //显示用户玩家的角色以及游戏状态
    m_title = new QLabel(this);
    if(isLord && isWin){
        m_title->setPixmap(QPixmap(":/images/lord_win.png"));
    }
    else if(isLord && !isWin){
        m_title->setPixmap(QPixmap(":/images/lord_fail.png"));
    }
    else if(!isLord && isWin){
        m_title->setPixmap(QPixmap(":/images/farmer_win.png"));
    }
    else if(!isLord && !isWin){
        m_title->setPixmap(QPixmap(":/images/farmer_fail.png"));
    }
    m_title->move(125,125);

    //分数面板
    m_score = new ScorePanel(this);
    m_score->move(75,230);
    m_score->setFixedSize(200,160);
    m_score->setMyFontColor(ScorePanel::Red);
    m_score->setMyFontSize(18);
    //继续游戏按钮
    m_continue = new QPushButton(this);
    m_continue->move(84,429);
    //注意：以下代码中使用了C++11中的新特性：原始字符串
    //顺序一定是正常状态，悬停状态，按下状态
    QString style = R"(
        QPushButton{border-image:url(:/images/button_normal.png)}
        QPushButton:hover{border-image:url(:/images/button_hover.png)}
        QPushButton:press{border-image:url(:/images/button_pressed.png)}
    )";
    m_continue->setStyleSheet(style);
    m_continue->setFixedSize(231,48);

    connect(m_continue,&QPushButton::clicked,this,&EndingPanel::contiueGame);
}

void EndingPanel::setPlayerScore(int left, int right, int user)
{
    m_score->setScores(left,right,user);
}

void EndingPanel::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    p.drawPixmap(rect(),m_bk);
}

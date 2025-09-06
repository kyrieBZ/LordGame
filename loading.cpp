#include "loading.h"

Loading::Loading(QWidget *parent)
    : QWidget{parent}
{
    m_bk.load(":/images/loading.png");
    setFixedSize(m_bk.size());

    //去除窗口边框(窗口原来的属性windowFlags加上无边框属性)
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //设置背景为透明
    setAttribute(Qt::WA_TranslucentBackground);

    QTimer *timer = new QTimer(this);

    QPixmap pixmap(":/images/progress.png");

    connect(timer,&QTimer::timeout,this,[=](){
        m_progress = pixmap.copy(0,0,m_dist,pixmap.height());
        update();
        if(m_dist >= pixmap.width()){
            timer->stop();
            timer->deleteLater();
            //显示主窗口
            GamePanel *panel = new GamePanel;
            panel->show();
            close();
        }
        m_dist += 5;
    });
    timer->start(15);
}

void Loading::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);//告诉编译器event参数没有被使用时不要给出警告
    QPainter p(this);
    p.drawPixmap(rect(),m_bk);
    p.drawPixmap(62,417,m_progress.width(),m_progress.height(),m_progress);
}

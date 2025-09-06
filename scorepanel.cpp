#include "scorepanel.h"
#include "ui_scorepanel.h"

const QString MYCOLOR[] = {"black","white","red","blue","green"};

ScorePanel::ScorePanel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ScorePanel)
{
    ui->setupUi(this);
    m_list<<ui->meTitle<<ui->leftTitle<<ui->rightTitle
           <<ui->userScore<<ui->leftScore<<ui->rightScore
           <<ui->score_1<<ui->score_2<<ui->score_3;
}

ScorePanel::~ScorePanel()
{
    delete ui;
}

void ScorePanel::setScores(int left, int right, int user)
{
    //将参数中的三个分数设置到窗口的三个标签中
    ui->leftScore->setText(QString::number(left));
    ui->rightScore->setText(QString::number(right));
    ui->userScore->setText(QString::number(user));
}

void ScorePanel::setMyFontSize(int point)
{
    QFont font("微软雅黑",point,QFont::Bold);
    for(int i=0;i<m_list.size();i++){
        m_list[i]->setFont(font);
    }
}

void ScorePanel::setMyFontColor(FontColor color)
{
    QString style = QString("QLabel{color:%1}").arg(MYCOLOR[color]);
    for(int i=0;i<m_list.size();i++){
        m_list[i]->setStyleSheet(style);
    }
}

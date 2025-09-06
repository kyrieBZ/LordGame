#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H

//按钮组类，用于实现主窗口中出牌，叫地主，过牌等按钮的组合显示

#include <QWidget>

namespace Ui {
class ButtonGroup;
}

class ButtonGroup : public QWidget
{
    Q_OBJECT

public:
    //按钮组stack页的索引枚举
    enum Panel{Start,PlayCard,PassOrPlay,CallLord,Empty};

    explicit ButtonGroup(QWidget *parent = nullptr);
    ~ButtonGroup();

    //初始化按钮
    void initButtons();

    //处理page页的切换
    void selectPanel(Panel type,int bet=0);

//按钮组中
signals:
    //开始游戏
    void startGame();
    //出牌
    void playHand();
    //不出牌
    void pass();
    //抢地主
    void betPoint(int bet);
private:
    Ui::ButtonGroup *ui;
};

#endif // BUTTONGROUP_H

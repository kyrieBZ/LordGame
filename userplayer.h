#ifndef USERPLAYER_H
#define USERPLAYER_H

#include <QObject>
#include "player.h"

class UserPlayer : public Player
{
    Q_OBJECT
public:
    using Player::Player;//使用父类中的所有构造函数
    explicit UserPlayer(QObject *parent = nullptr);

    //重写父类（Player）的准备叫地主/出牌函数
    void prepareCallLord() override;
    void preparePlayHand() override;

signals:
    void startCountDown();
};

#endif // USERPLAYER_H

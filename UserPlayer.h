#ifndef USERPLAYER_H
#define USERPLAYER_H

#include "Player.h"

class UserPlayer : public Player
{
    Q_OBJECT
public:
    UserPlayer(QObject* parent = NULL);

public:
    virtual void StartCallLord();
    virtual void StartPlayHand();
};

#endif // USERPLAYER_H

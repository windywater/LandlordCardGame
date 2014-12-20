#ifndef ROBOT_H
#define ROBOT_H

#include "Player.h"

class Robot : public Player
{
    Q_OBJECT
public:
    Robot(QObject* parent = NULL);

public:
    virtual void StartCallLord();
    virtual void StartPlayHand();

    virtual void ThinkForCallLord();
    virtual void ThinkForPlayHand();
};

#endif // ROBOT_H

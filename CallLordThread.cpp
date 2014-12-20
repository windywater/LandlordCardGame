#include "CallLordThread.h"
#include "Player.h"

CallLordThread::CallLordThread(Player* player) :
    QThread(player)
{
    m_player = player;
}

void CallLordThread::run()
{
    msleep(600);
    m_player->ThinkForCallLord();
}

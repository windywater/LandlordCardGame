#include "PlayHandThread.h"
#include "Player.h"

PlayHandThread::PlayHandThread(Player* player) :
    QThread(player)
{
    m_player = player;
}

void PlayHandThread::run()
{
    msleep(600);
    m_player->ThinkForPlayHand();
}

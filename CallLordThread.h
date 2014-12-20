#ifndef CALLLORDTHREAD_H
#define CALLLORDTHREAD_H

#include <QThread>

class Player;

class CallLordThread : public QThread
{
    Q_OBJECT
public:
    explicit CallLordThread(Player* player);

protected:
    virtual void run();

private:
    Player* m_player;
};

#endif // CALLLORDTHREAD_H

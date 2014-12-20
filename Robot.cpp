#include "Robot.h"
#include "CallLordThread.h"
#include "PlayHandThread.h"
#include "Strategy.h"

Robot::Robot(QObject *parent)
{
    m_type = Player::Robot;
}

void Robot::StartCallLord()
{
    CallLordThread* thread = new CallLordThread(this);
    thread->start();
}

void Robot::StartPlayHand()
{
    PlayHandThread* thread = new PlayHandThread(this);
    thread->start();
}

void Robot::ThinkForCallLord()
{
    int weight = 0;

    Strategy st(this, m_cards);
    weight += st.GetRangeCards(Card_SJ, Card_BJ).Count() * 6;
    weight += m_cards.PointCount(Card_2) * 3;

    QVector<Cards> optSeq = st.PickOptimalSeqSingles();
    weight += optSeq.size() * 5;

    Cards left = m_cards;
    left.Remove(optSeq);
    Strategy stLeft(this, left);

    QVector<Cards> bombs = stLeft.FindCardsByCount(4);
    weight += bombs.size() * 5;

    QVector<Cards> triples = stLeft.FindCardsByCount(3);
    weight += triples.size() * 4;

    QVector<Cards> pairs = stLeft.FindCardsByCount(2);
    weight += pairs.size() * 1;

    if (weight >= 22)
    {
        CallLord(3);
    }
    else if (weight < 22 && weight >= 18)
    {
        CallLord(2);
    }
    else if (weight > 18 && weight >= 10)
    {
        CallLord(1);
    }
    else
    {
        CallLord(0);
    }
}

void Robot::ThinkForPlayHand()
{
    Strategy strategy(this, m_cards);
    PlayHand(strategy.MakeStrategy());
}


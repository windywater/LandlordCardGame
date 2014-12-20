#ifndef HAND_H
#define HAND_H

#include "Cards.h"
#include <QVector>

class Hand
{
public:
    Hand();
    Hand(HandType type, CardPoint base, int extra);
    Hand(const Cards& cards);

    bool operator ==(const Hand& hand);

public:
    void FromCards(const Cards& cards);
    void JudgeHand();

    bool CanBeat(const Hand& other);
    HandType GetType();
    CardPoint GetBasePoint();
    int GetExtra();

protected:
    HandType m_handType;
    CardPoint m_basePoint;
    int m_extra;

    QVector<CardPoint> m_oneCard;
    QVector<CardPoint> m_twoCards;
    QVector<CardPoint> m_threeCards;
    QVector<CardPoint> m_fourCards;
};

#endif // HAND_H

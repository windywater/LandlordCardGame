#include "Cards.h"
#include "Hand.h"
#include <QTime>

Cards::Cards()
{
}

Cards::~Cards()
{

}

void Cards::Clear()
{
    m_cards.clear();
}

bool Cards::IsEmpty() const
{
    return m_cards.isEmpty();
}

void Cards::Add(const Cards& cards)
{
    m_cards = m_cards.unite(cards.m_cards);

    QSet<Card>::const_iterator it = cards.m_cards.constBegin();
    for (; it != cards.m_cards.constEnd(); it++)
    {
        CardPoint point = it->point;
    }
}

void Cards::Add(const Card& card)
{
    m_cards.insert(card);
}

void Cards::Add(const QVector<Cards>& cardsArray)
{
    for (int i = 0; i < cardsArray.size(); i++)
    {
        Add(cardsArray[i]);
    }
}

Cards& Cards::operator <<(const Cards& cards)
{
    Add(cards);
    return *this;
}

Cards& Cards::operator <<(const Card& card)
{
    Add(card);
    return *this;
}

Cards& Cards::operator <<(const QVector<Cards>& cardsArray)
{
    Add(cardsArray);
    return *this;
}

void Cards::Remove(const Cards& cards)
{
    m_cards.subtract(cards.m_cards);

    QSet<Card>::const_iterator it = cards.m_cards.constBegin();
    for (; it != cards.m_cards.constEnd(); it++)
    {
        CardPoint point = it->point;
    }
}

void Cards::Remove(const Card& card)
{
    m_cards.remove(card);
}

void Cards::Remove(const QVector<Cards>& cardsArray)
{
    for (int i = 0; i < cardsArray.size(); i++)
    {
        Remove(cardsArray[i]);
    }
}

bool Cards::Contains(const Cards& cards) const
{
    return m_cards.contains(cards.m_cards);
}

bool Cards::Contains(const Card& card) const
{
    return m_cards.contains(card);
}

Card Cards::TakeRandomCard()
{
    QTime time;
    time = QTime::currentTime();
    qsrand(time.msec() + time.second() * 1000);

    int randomIndex = qrand() % m_cards.size();
    QSet<Card>::iterator it = m_cards.begin() + randomIndex;
    Card takeCard = *it;
    m_cards.erase(it);

    return takeCard;
}

int Cards::Count()
{
    return m_cards.size();
}

int Cards::PointCount(CardPoint point)
{
    int count = 0;
    for (QSet<Card>::ConstIterator it = m_cards.constBegin(); it != m_cards.constEnd(); it++)
    {
        if (it->point == point)
        {
            count++;
        }
    }

    return count;
}

CardPoint Cards::MinPoint()
{
    CardPoint min = Card_End;
    if (m_cards.isEmpty()) return Card_End;

    QSet<Card>::ConstIterator it = m_cards.constBegin();
    for (; it != m_cards.constEnd(); it++)
    {
        if (it->point < min)
        {
            min = it->point;
        }
    }

    return min;
}

CardPoint Cards::MaxPoint()
{
    CardPoint max = Card_Begin;
    if (m_cards.isEmpty()) return Card_Begin;

    QSet<Card>::ConstIterator it = m_cards.constBegin();
    for (; it != m_cards.constEnd(); it++)
    {
        if (it->point > max)
        {
            max = it->point;
        }
    }

    return max;
}

CardList Cards::ToCardList(SortType sortType) const
{
    CardList cardList;
    for (QSet<Card>::const_iterator it = m_cards.constBegin(); it != m_cards.constEnd(); it++)
    {
        cardList << *it;
    }

    if (sortType == Asc)
    {
        qSort(cardList.begin(), cardList.end(), qLess<Card>());
    }
    else if (sortType == Desc)
    {
        qSort(cardList.begin(), cardList.end(), qGreater<Card>());
    }

    return cardList;
}

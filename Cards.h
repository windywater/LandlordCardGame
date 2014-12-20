#ifndef CARDS_H
#define CARDS_H

#include <QVector>
#include <QSet>
#include <QMap>
#include <QList>

class Hand;

enum CardPoint
{
    Card_Begin,

    Card_3,
    Card_4,
    Card_5,
    Card_6,
    Card_7,
    Card_8,
    Card_9,
    Card_10,
    Card_J,
    Card_Q,
    Card_K,
    Card_A,
    Card_2,

    Card_SJ,
    Card_BJ,

    Card_End
};

const int PointCount = 15;

enum CardSuit
{
    Suit_Begin,

    Diamond,	// 方块
    Club,		// 梅花
    Heart,		// 红桃
    Spade,		// 黑桃

    Suit_End
};

enum HandType
{
    Hand_Unknown,			// 未知
    Hand_Pass,				// 过

    Hand_Single,			// 单
    Hand_Pair,				// 对

    Hand_Triple,			// 三个
    Hand_Triple_Single,		// 三带一
    Hand_Triple_Pair,		// 三带二

    Hand_Plane,				// 飞机，555_666
    Hand_Plane_Two_Single,	// 飞机带单，555_666_3_4
    Hand_Plane_Two_Pair,	// 飞机带双，555_666_33_44

    Hand_Seq_Pair,			// 连对，33_44_55(_66...)
    Hand_Seq_Single,		// 顺子，34567(8...)

    Hand_Bomb,				// 炸弹
    Hand_Bomb_Single,		// 炸弹带一个
    Hand_Bomb_Pair,			// 炸弹带一对
    Hand_Bomb_Two_Single,	// 炸弹带两单

    Hand_Bomb_Jokers,			// 王炸
    Hand_Bomb_Jokers_Single,	// 王炸带一个
    Hand_Bomb_Jokers_Pair,		// 王炸带一对
    Hand_Bomb_Jokers_Two_Single	// 王炸带两单

};

struct Card
{
    CardPoint point;
    CardSuit suit;
};

inline bool operator ==(const Card& left, const Card& right)
{
    return (left.point == right.point && left.suit == right.suit);
}

inline bool operator <(const Card& left, const Card& right)
{
    if (left.point == right.point)
    {
        return left.suit < right.suit;
    }
    else
    {
        return left.point < right.point;
    }
}


inline uint qHash(const Card& card)
{
    return card.point * 100 + card.suit;
}

typedef QVector<Card> CardList;

class Cards
{
public:
    Cards();
    ~Cards();

public:
    enum SortType
    {
        NoSort,
        Asc,
        Desc
    };

    void Add(const Cards& cards);
    void Add(const Card& card);
    void Add(const QVector<Cards>& cardsArray);

    void Remove(const Cards& cards);
    void Remove(const Card& card);
    void Remove(const QVector<Cards>& cardsArray);

    bool Contains(const Cards& cards) const;
    bool Contains(const Card& card) const;

    Cards& operator <<(const Cards& cards);
    Cards& operator <<(const Card& card);
    Cards& operator <<(const QVector<Cards>& cardsArray);

    CardList ToCardList(SortType sortType = Asc) const;

    int Count();
    int PointCount(CardPoint point);
    CardPoint MinPoint();
    CardPoint MaxPoint();

    Card TakeRandomCard();

    bool IsEmpty() const;
    void Clear();

protected:
    QSet<Card> m_cards;
};

#endif // CARDS_H

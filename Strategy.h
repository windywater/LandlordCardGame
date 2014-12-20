#ifndef STRATEGY_H
#define STRATEGY_H

#include <QVector>

class Cards;
class Player;

class Strategy
{
public:
    Strategy(Player* player, const Cards& cards);

    Cards MakeStrategy();

public:
    Cards FindSamePointCards(CardPoint point, int count);	// 找出count张点数为point的牌
    QVector<Cards> FindCardsByCount(int count);		// 找出所有张数为count的所有牌数组
    Cards GetRangeCards(CardPoint beginPoint, CardPoint endPoint);	// 根据点数范围找牌
    Cards GetFirstSeqSingleRange();		// 找到第一个能构成顺子的牌集合

    // 在cards中挑出一个顺子，seqInherited记录逐步拨除顺子，allSeqRecord记录所能分离出的顺子
    void PickSeqSingles(QVector<QVector<Cards> >& allSeqRecord, const QVector<Cards>& seqInherited, Cards cards);
    QVector<Cards> PickOptimalSeqSingles();

    // 按牌型找到若干手牌，beat为true表示要大过hand
    QVector<Cards> FindHand(Hand hand, bool beat);

    Cards PlayFirst();		// 主动出牌
    Cards PlayBeatHand(Hand hand);		// 大过指定牌型

    bool WhetherToBeat(const Cards& myCards);	// 能大过时，判断是打还是放行

protected:
    Player* m_player;
    Cards m_cards;
};

#endif // STRATEGY_H

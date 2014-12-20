
#include "Cards.h"
#include "Hand.h"
#include "Player.h"
#include "Strategy.h"

Strategy::Strategy(Player* player, const Cards& cards)
{
    m_player = player;
    m_cards = cards;
}

QVector<Cards> Strategy::FindHand(Hand hand, bool beat)
{
    HandType handType = hand.GetType();
    CardPoint basePoint = hand.GetBasePoint();
    int extra = hand.GetExtra();

    if (handType == Hand_Pass)
    {
    }
    else if (handType == Hand_Single)
    {
        QVector<Cards> findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point < Card_End; point = CardPoint(point + 1))
        {
            Cards findCards = FindSamePointCards(point, 1);
            if (!findCards.IsEmpty())
            {
                findCardsArray << findCards;
            }
        }

        return findCardsArray;
    }
    else if (handType == Hand_Pair)
    {
        QVector<Cards> findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point < Card_End; point = CardPoint(point + 1))
        {
            Cards findCards = FindSamePointCards(point, 2);
            if (!findCards.IsEmpty())
            {
                findCardsArray << findCards;
            }
        }

        return findCardsArray;
    }
    else if (handType == Hand_Triple)
    {
        QVector<Cards> findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point < Card_End; point = CardPoint(point + 1))
        {
            Cards findCards = FindSamePointCards(point, 3);
            if (!findCards.IsEmpty())
            {
                findCardsArray << findCards;
            }
        }

        return findCardsArray;
    }
    else if (handType == Hand_Triple_Single)
    {
        QVector<Cards> findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point < Card_End; point = CardPoint(point + 1))
        {
            Cards findCards = FindSamePointCards(point, 3);
            if (!findCards.IsEmpty())
            {
                findCardsArray << findCards;
            }
        }

        if (!findCardsArray.isEmpty())
        {
            Cards remainCards = m_cards;
            remainCards.Remove(findCardsArray);

            Strategy st(m_player, remainCards);
            QVector<Cards> oneCardsArray = st.FindHand(Hand(Hand_Single, Card_Begin, 0), false);
            if (!oneCardsArray.isEmpty())
            {
                for (int i = 0; i < findCardsArray.size(); i++)
                {
                    findCardsArray[i] << oneCardsArray[0];
                }
            }
            else
            {
                findCardsArray.clear();
            }
        }

        return findCardsArray;
    }
    else if (handType == Hand_Triple_Pair)
    {
        QVector<Cards> findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point < Card_End; point = CardPoint(point + 1))
        {
            Cards findCards = FindSamePointCards(point, 3);
            if (!findCards.IsEmpty())
            {
                findCardsArray << findCards;
            }
        }

        if (!findCardsArray.isEmpty())
        {
            Cards remainCards = m_cards;
            remainCards.Remove(findCardsArray);

            Strategy st(m_player, remainCards);
            QVector<Cards> pairCardsArray = st.FindHand(Hand(Hand_Pair, Card_Begin, 0), false);
            if (!pairCardsArray.isEmpty())
            {
                for (int i = 0; i < findCardsArray.size(); i++)
                {
                    findCardsArray[i] << pairCardsArray[0];
                }
            }
            else
            {
                findCardsArray.clear();
            }
        }

        return findCardsArray;
    }
    else if (handType == Hand_Plane)
    {
        QVector<Cards> findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point <= Card_K; point = CardPoint(point + 1))
        {
            Cards prevCards = FindSamePointCards(point, 3);
            Cards nextCards = FindSamePointCards(CardPoint(point+1), 3);
            if (!prevCards.IsEmpty() && !nextCards.IsEmpty())
            {
                findCardsArray << prevCards << nextCards;
            }
        }
    }
    else if (handType == Hand_Plane_Two_Single)
    {
        QVector<Cards> findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point <= Card_K; point = CardPoint(point + 1))
        {
            Cards prevCards = FindSamePointCards(point, 3);
            Cards nextCards = FindSamePointCards(CardPoint(point+1), 3);
            if (!prevCards.IsEmpty() && !nextCards.IsEmpty())
            {
                Cards findCards;
                findCards << prevCards << nextCards;
                findCardsArray << findCards;
            }
        }

        if (!findCardsArray.isEmpty())
        {
            Cards remainCards = m_cards;
            remainCards.Remove(findCardsArray);

            Strategy st(m_player, remainCards);
            QVector<Cards> oneCardsArray = st.FindHand(Hand(Hand_Single, Card_Begin, 0), false);
            if (oneCardsArray.size() >= 2)
            {
                for (int i = 0; i < findCardsArray.size(); i++)
                {
                    Cards oneCards;
                    oneCards << oneCardsArray[0] << oneCardsArray[1];
                    findCardsArray[i] << oneCards;
                }
            }
            else
            {
                findCardsArray.clear();
            }
        }

        return findCardsArray;
    }
    else if (handType == Hand_Plane_Two_Pair)
    {
        QVector<Cards> findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point <= Card_K; point = CardPoint(point + 1))
        {
            Cards prevCards = FindSamePointCards(point, 3);
            Cards nextCards = FindSamePointCards(CardPoint(point+1), 3);
            if (!prevCards.IsEmpty() && !nextCards.IsEmpty())
            {
                Cards findCards;
                findCards << prevCards << nextCards;
                findCardsArray << findCards;
            }
        }

        if (!findCardsArray.isEmpty())
        {
            Cards remainCards = m_cards;
            remainCards.Remove(findCardsArray);

            Strategy st(m_player, remainCards);
            QVector<Cards> pairCardsArray = st.FindHand(Hand(Hand_Pair, Card_Begin, 0), false);
            if (pairCardsArray.size() >= 2)
            {
                for (int i = 0; i < findCardsArray.size(); i++)
                {
                    Cards pairCards;
                    pairCards << pairCardsArray[0] << pairCardsArray[1];
                    findCardsArray[i] << pairCards;
                }
            }
            else
            {
                findCardsArray.clear();
            }
        }

        return findCardsArray;
    }
    else if (handType == Hand_Seq_Pair)
    {
        if (beat)
        {
            QVector<Cards> findCardsArray;
            for (CardPoint point = CardPoint(basePoint + 1); point <= Card_Q; point = CardPoint(point + 1))
            {
                bool seqPairFound = true;
                Cards seqPair;

                for (int i = 0; i < extra; i++)
                {
                    Cards cards = FindSamePointCards(CardPoint(point + i), 2);
                    if (cards.IsEmpty() || (point + i >= Card_2))	// 连对中断，或顶到2了
                    {
                        seqPairFound = false;
                        seqPair.Clear();
                        break;
                    }
                    else
                    {
                        seqPair << cards;
                    }
                }

                if (seqPairFound)
                {
                    findCardsArray << seqPair;
                    return findCardsArray;
                }
            }

            return findCardsArray;
        }
        else
        {
            QVector<Cards> findCardsArray;

            for (CardPoint point = Card_3; point <= Card_Q; point = CardPoint(point + 1))
            {
                Cards cards0 = FindSamePointCards(point, 2);
                Cards cards1 = FindSamePointCards(CardPoint(point + 1), 2);
                Cards cards2 = FindSamePointCards(CardPoint(point + 2), 2);

                if (cards0.IsEmpty() || cards1.IsEmpty() || cards2.IsEmpty()) continue;

                Cards baseSeq;
                baseSeq << cards0 << cards1 << cards2;
                findCardsArray << baseSeq;

                int followed = 3;
                Cards alreadyFollowedCards;

                while (true)
                {
                    CardPoint followedPoint = CardPoint(point + followed);
                    if (followedPoint >= Card_2)
                    {
                        break;
                    }

                    Cards followedCards = FindSamePointCards(followedPoint, 2);
                    if (followedCards.IsEmpty())
                    {
                        break;
                    }
                    else
                    {
                        alreadyFollowedCards << followedCards;
                        Cards newSeq = baseSeq;
                        newSeq << alreadyFollowedCards;

                        findCardsArray << newSeq;
                        followed++;
                    }
                }
            }

            return findCardsArray;
        }
    }
    else if (handType == Hand_Seq_Single)
    {
        if (beat)
        {
            QVector<Cards> findCardsArray;
            for (CardPoint point = CardPoint(basePoint + 1); point <= Card_10; point = CardPoint(point + 1))
            {
                bool seqSingleFound = true;
                Cards seqSingle;

                for (int i = 0; i < extra; i++)
                {
                    Cards cards = FindSamePointCards(CardPoint(point + i), 1);
                    if (cards.IsEmpty() || (point + extra >= Card_2))
                    {
                        seqSingleFound = false;
                        seqSingle.Clear();
                        break;
                    }
                    else
                    {
                        seqSingle << cards;
                    }
                }

                if (seqSingleFound)
                {
                    findCardsArray << seqSingle;
                    return findCardsArray;
                }
            }
        }
        else
        {
            QVector<Cards> findCardsArray;

            for (CardPoint point = Card_3; point <= Card_10; point = CardPoint(point + 1))
            {
                Cards cards0 = FindSamePointCards(point, 1);
                Cards cards1 = FindSamePointCards(CardPoint(point + 1), 1);
                Cards cards2 = FindSamePointCards(CardPoint(point + 2), 1);
                Cards cards3 = FindSamePointCards(CardPoint(point + 3), 1);
                Cards cards4 = FindSamePointCards(CardPoint(point + 4), 1);

                if (cards0.IsEmpty() || cards1.IsEmpty() || cards2.IsEmpty()
                    || cards3.IsEmpty() || cards4.IsEmpty())
                {
                    continue;
                }

                Cards baseSeq;
                baseSeq << cards0 << cards1 << cards2 << cards3 << cards4;
                findCardsArray << baseSeq;

                int followed = 5;
                Cards alreadyFollowedCards;

                while (true)
                {
                    CardPoint followedPoint = CardPoint(point + followed);
                    if (followedPoint >= Card_2)
                    {
                        break;
                    }

                    Cards followedCards = FindSamePointCards(followedPoint, 1);
                    if (followedCards.IsEmpty())
                    {
                        break;
                    }
                    else
                    {
                        alreadyFollowedCards << followedCards;
                        Cards newSeq = baseSeq;
                        newSeq << alreadyFollowedCards;

                        findCardsArray << newSeq;
                        followed++;
                    }
                }
            }

            return findCardsArray;
        }
    }
    else if (handType == Hand_Bomb)
    {
        QVector<Cards> findCardsArray;

        CardPoint beginPoint = beat ? CardPoint(basePoint + 1) : CardPoint(Card_Begin + 1);
        for (CardPoint point = beginPoint; point < Card_End; point = CardPoint(point + 1))
        {
            Cards findCards = FindSamePointCards(point, 4);
            if (!findCards.IsEmpty())
            {
                findCardsArray << findCards;
            }
        }

        return findCardsArray;
    }
    else if (handType == Hand_Bomb_Single)
    {

    }
    else if (handType == Hand_Bomb_Pair)
    {

    }
    else if (handType == Hand_Bomb_Two_Single)
    {

    }

    return QVector<Cards>();
}

Cards Strategy::FindSamePointCards(CardPoint point, int count)
{
    if (point == Card_SJ || point == Card_BJ)
    {
        if (count > 1) return Cards();

        Card oneCard;
        oneCard.point = point;
        oneCard.suit = Suit_Begin;
        if (m_cards.Contains(oneCard))
        {
            Cards cards;
            cards.Add(oneCard);
            return cards;
        }

        return Cards();
    }

    Cards findCards;
    int findCount = 0;
    for (int suit = Suit_Begin + 1; suit < Suit_End; suit++)
    {
        Card oneCard;
        oneCard.point = point;
        oneCard.suit = (CardSuit)suit;

        if (m_cards.Contains(oneCard))
        {
            findCount++;
            findCards << oneCard;

            if (findCount == count)
            {
                return findCards;
            }
        }
    }

    return Cards();
}

QVector<Cards> Strategy::FindCardsByCount(int count)
{
    QVector<Cards> cardsArray;
    if (count < 1 || count > 4) return cardsArray;

    for (CardPoint point = Card_3; point < Card_End; point = CardPoint(point + 1))
    {
        if (m_cards.PointCount(point) == count)
        {
            Cards cards;
            cards << FindSamePointCards(point, count);
            cardsArray << cards;
        }
    }

    return cardsArray;
}

Cards Strategy::GetRangeCards(CardPoint beginPoint, CardPoint endPoint)
{
    Cards rangeCards;

    for (CardPoint point = beginPoint; point <= endPoint; point = CardPoint(point + 1))
    {
        int count = m_cards.PointCount(point);
        Cards cards = FindSamePointCards(point, count);
        rangeCards << cards;
    }

    return rangeCards;
}

Cards Strategy::GetFirstSeqSingleRange()
{
    int seqCount = 0;
    CardPoint beginPoint, endPoint;
    beginPoint = endPoint = Card_Begin;

    for (CardPoint point = Card_3; point <= Card_10; point = CardPoint(point + 1))
    {
        while (true)
        {
            CardPoint findPoint = CardPoint(point + seqCount);
            Cards oneCard = FindSamePointCards(findPoint, 1);
            if (oneCard.IsEmpty() || findPoint > Card_A)
            {
                if (seqCount >= 5)
                {
                    endPoint = CardPoint(point + seqCount - 1);
                    return GetRangeCards(beginPoint, endPoint);
                }

                point = findPoint;
                beginPoint = endPoint = Card_Begin;
                seqCount = 0;

                break;
            }
            else
            {
                if (seqCount == 0)
                {
                    beginPoint = point;
                }

                seqCount++;
            }
        }
    }

    return Cards();
}

void Strategy::PickSeqSingles(QVector<QVector<Cards> >& allSeqRecord, const QVector<Cards>& seqInherited, Cards cards)
{
    QVector<Cards> allSeqScheme = Strategy(m_player, cards).FindHand(Hand(Hand_Seq_Single, Card_Begin, 0), false);
    if (allSeqScheme.isEmpty())
    {
        allSeqRecord << seqInherited;
    }
    else
    {
        Cards savedCards = cards;
        for (int i = 0; i < allSeqScheme.size(); i++)
        {
            Cards aScheme = allSeqScheme[i];
            Cards leftCards = savedCards;
            leftCards.Remove(aScheme);

            QVector<Cards> seqArray = seqInherited;
            seqArray << aScheme;

            PickSeqSingles(allSeqRecord, seqArray, leftCards);
        }
    }
}

QVector<Cards> Strategy::PickOptimalSeqSingles()
{
    QVector<QVector<Cards> > seqRecord;
    QVector<Cards> seqInherited;
    Strategy(m_player, m_cards).PickSeqSingles(seqRecord, seqInherited, m_cards);
    if (seqRecord.isEmpty()) return QVector<Cards>();

    QMap<int, int> seqMarks;
    for (int i = 0; i < seqRecord.size(); i++)
    {
        Cards backupCards = m_cards;
        QVector<Cards> seqArray = seqRecord[i];
        backupCards.Remove(seqArray);

        QVector<Cards> singleArray = Strategy(m_player, backupCards).FindCardsByCount(1);

        CardList cardList;
        for (int j = 0; j < singleArray.size(); j++)
        {
            cardList << singleArray[j].ToCardList();
        }

        int mark = 0;
        for (int j = 0; j < cardList.size(); j++)
        {
            mark += cardList[j].point + 15;
        }
        seqMarks.insert(i, mark);
    }

    int index = 0;
    int compMark = 1000000;
    QMap<int, int>::ConstIterator it = seqMarks.constBegin();
    for (; it != seqMarks.constEnd(); it++)
    {
        if (it.value() < compMark)
        {
            compMark = it.value();
            index = it.key();
        }
    }

    return seqRecord[index];
}

Cards Strategy::PlayFirst()
{
    Hand hand(m_cards);
    if (hand.GetType() != Hand_Unknown)		// 只剩一手牌，直接出完
    {
        return m_cards;
    }

    Cards seqSingleRange = GetFirstSeqSingleRange();
    if (!seqSingleRange.IsEmpty())
    {
        Cards left = seqSingleRange;
        left.Remove(Strategy(m_player, left).FindCardsByCount(4));
        left.Remove(Strategy(m_player, left).FindCardsByCount(3));
        QVector<Cards> optimalSeq = Strategy(m_player, left).PickOptimalSeqSingles();
        if (!optimalSeq.isEmpty())
        {
            int oriSingleCount = Strategy(m_player, left).FindCardsByCount(1).size();
            left.Remove(optimalSeq);
            int leftSingleCount = Strategy(m_player, left).FindCardsByCount(1).size();

            if (leftSingleCount < oriSingleCount)
            {
                return optimalSeq[0];
            }
        }
    }

    bool hasPlane, hasTriple, hasSeqPair;
    hasPlane = hasTriple = hasSeqPair = false;
    Cards leftCards = m_cards;

    QVector<Cards> bombArray = Strategy(m_player, leftCards).FindHand(Hand(Hand_Bomb, Card_Begin, 0), false);
    leftCards.Remove(bombArray);

    QVector<Cards> planeArray = Strategy(m_player, leftCards).FindHand(Hand(Hand_Plane, Card_Begin, 0), false);
    if (!planeArray.isEmpty())
    {
        hasPlane = true;
        leftCards.Remove(planeArray);
    }

    QVector<Cards> tripleArray = Strategy(m_player, leftCards).FindHand(Hand(Hand_Triple, Card_Begin, 0), false);
    if (!tripleArray.isEmpty())
    {
        hasTriple = true;
        leftCards.Remove(tripleArray);
    }

    QVector<Cards> seqPairArray = Strategy(m_player, leftCards).FindHand(Hand(Hand_Seq_Pair, Card_Begin, 0), false);
    if (!seqPairArray.isEmpty())
    {
        hasSeqPair = true;
        leftCards.Remove(seqPairArray);
    }

    if (hasPlane)
    {
        bool twoPairFound = false;
        QVector<Cards> pairArray;
        for (CardPoint point = Card_3; point <= Card_A; point = CardPoint(point + 1))
        {
            Cards pair = Strategy(m_player, leftCards).FindSamePointCards(point, 2);
            if (!pair.IsEmpty())
            {
                pairArray << pair;
                if (pairArray.size() == 2)
                {
                    twoPairFound = true;
                    break;
                }
            }
        }

        if (twoPairFound)
        {
            Cards playCards = planeArray[0];
            playCards.Add(pairArray);

            return playCards;
        }
        else
        {
            bool twoSingleFound = false;
            QVector<Cards> singleArray;
            for (CardPoint point = Card_3; point <= Card_A; point = CardPoint(point + 1))
            {
                if (leftCards.PointCount(point) == 1)
                {
                    Cards single = Strategy(m_player, leftCards).FindSamePointCards(point, 1);
                    if (!single.IsEmpty())
                    {
                        singleArray << single;
                        if (singleArray.size() == 2)
                        {
                            twoSingleFound = true;
                            break;
                        }
                    }
                }
            }

            if (twoSingleFound)
            {
                Cards playCards = planeArray[0];
                playCards.Add(singleArray);

                return playCards;
            }
            else
            {
                return planeArray[0];
            }
        }
    }

    if (hasTriple)
    {
        if (Hand(tripleArray[0]).GetBasePoint() < Card_A)
        {
            for (CardPoint point = Card_3; point <= Card_A; point = CardPoint(point + 1))
            {
                int pointCount = leftCards.PointCount(point);
                if (pointCount == 1)
                {
                    Cards single = Strategy(m_player, leftCards).FindSamePointCards(point, 1);
                    if (!single.IsEmpty())
                    {
                        Cards playCards = tripleArray[0];
                        playCards.Add(single);

                        return playCards;
                    }
                }
                else if (pointCount == 2)
                {
                    Cards pair = Strategy(m_player, leftCards).FindSamePointCards(point, 2);
                    if (!pair.IsEmpty())
                    {
                        Cards playCards = tripleArray[0];
                        playCards.Add(pair);

                        return playCards;
                    }
                }

            }

            return tripleArray[0];		// 找不到合适的带牌，直接出3个
        }
    }

    if (hasSeqPair)		// 打出最长的连对
    {
        Cards maxSeqPair;
        for (int i = 0; i < seqPairArray.size(); i++)
        {
            if (seqPairArray[i].Count() > maxSeqPair.Count())
            {
                maxSeqPair = seqPairArray[i];
            }
        }

        return maxSeqPair;
    }

    Player* nextPlayer = m_player->GetNextPlayer();

    if (m_player->GetRole() != nextPlayer->GetRole() &&
        nextPlayer->GetCards().Count() == 1)
    {
        for (CardPoint point = CardPoint(Card_End - 1); point >= Card_3; point = CardPoint(point - 1))
        {
            int pointCount = leftCards.PointCount(point);
            if (pointCount == 1)
            {
                Cards single = Strategy(m_player, leftCards).FindSamePointCards(point, 1);
                return single;
            }
            else if (pointCount == 2)
            {
                Cards pair = Strategy(m_player, leftCards).FindSamePointCards(point, 2);
                return pair;
            }
        }
    }
    else
    {
        for (CardPoint point = Card_3; point < Card_End; point = CardPoint(point + 1))
        {
            int pointCount = leftCards.PointCount(point);
            if (pointCount == 1)
            {
                Cards single = Strategy(m_player, leftCards).FindSamePointCards(point, 1);
                return single;
            }
            else if (pointCount == 2)
            {
                Cards pair = Strategy(m_player, leftCards).FindSamePointCards(point, 2);
                return pair;
            }
        }
    }

    return Cards();
}

Cards Strategy::PlayBeatHand(Hand hand)
{
    // 先固定住最优顺子，从余下牌中打出
    Cards left = m_cards;
    left.Remove(Strategy(m_player, left).PickOptimalSeqSingles());

    if (hand.GetType() == Hand_Single)	// 如果压单牌，尽量从单张牌中挑
    {
        QVector<Cards> singleArray = Strategy(m_player, left).FindCardsByCount(1);
        for (int i = 0; i < singleArray.size(); i++)
        {
            if (Hand(singleArray[i]).CanBeat(hand))
            {
                return singleArray[i];
            }
        }
    }
    else if (hand.GetType() == Hand_Pair)	// 如果压双牌，尽量从双牌中挑
    {
        QVector<Cards> pairArray = Strategy(m_player, left).FindCardsByCount(2);
        for (int i = 0; i < pairArray.size(); i++)
        {
            if (Hand(pairArray[i]).CanBeat(hand))
            {
                return pairArray[i];
            }
        }
    }

    Player* nextPlayer = m_player->GetNextPlayer();
    QVector<Cards> beatCardsArray = Strategy(m_player, left).FindHand(hand, true);
    if (!beatCardsArray.isEmpty())
    {
        if (m_player->GetRole() != nextPlayer->GetRole() &&
            nextPlayer->GetCards().Count() <= 2)
        {
            return beatCardsArray.back();
        }
        else
        {
            return beatCardsArray.front();
        }
    }
    else	// 余下牌没法打时，只好从顺子中挑牌
    {
        beatCardsArray = Strategy(m_player, m_cards).FindHand(hand, true);
        if (!beatCardsArray.isEmpty())
        {
            if (m_player->GetRole() != nextPlayer->GetRole() &&
                nextPlayer->GetCards().Count() <= 2)
            {
                return beatCardsArray.back();
            }
            else
            {
                return beatCardsArray.front();
            }
        }
    }

    // 对家剩牌小于3张，有炸则炸
    Player* punchPlayer = m_player->GetPunchPlayer();
    if (m_player->GetRole() != punchPlayer->GetRole())
    {
        if (punchPlayer->GetCards().Count() <= 3)
        {
            QVector<Cards> bombs = FindCardsByCount(4);
            if (!bombs.isEmpty())
            {
                return bombs[0];
            }
        }
    }

    return Cards();
}

bool Strategy::WhetherToBeat(const Cards& myCards)
{
    if (myCards.IsEmpty()) return true;

    Player* punchPlayer = m_player->GetPunchPlayer();
    Cards punchCards = m_player->GetPunchCards();

    if (m_player->GetRole() == punchPlayer->GetRole())		// punch的是同家
    {
        Cards left = m_cards;
        left.Remove(myCards);
        if (Hand(left).GetType() != Hand_Unknown) return true;

        CardPoint basePoint = Hand(myCards).GetBasePoint();
        if (basePoint == Card_2 || basePoint == Card_SJ || basePoint == Card_BJ)
        {
            return false;
        }
    }
    else	// punch的是对家
    {
        Hand myHand(myCards);

        if ( (myHand.GetType() == Hand_Triple_Single || myHand.GetType() == Hand_Triple_Pair) &&
             (myHand.GetBasePoint() == Card_2) )	// 三个2就不打出去了
        {
            return false;
        }

        if (myHand.GetType() == Hand_Pair && myHand.GetBasePoint() == Card_2 &&
            punchPlayer->GetCards().Count() >= 10 && m_player->GetCards().Count() >= 5)
        {
            return false;
        }
    }

    return true;
}

Cards Strategy::MakeStrategy()
{
    Player* punchPlayer = m_player->GetPunchPlayer();
    Cards punchCards = m_player->GetPunchCards();

    if (punchPlayer == m_player || punchPlayer == NULL)
    {
        return PlayFirst();
    }
    else
    {
        Hand punchHand(punchCards);
        Cards beatCards = PlayBeatHand(punchHand);
        bool shouldBeat = WhetherToBeat(beatCards);
        if (shouldBeat)
        {
            return beatCards;
        }
        else
        {
            return Cards();
        }
    }

    return Cards();
}

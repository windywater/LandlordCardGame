#include "GameControl.h"
#include <QMetaType>
#include "Hand.h"
#include <QMessageBox>

GameControl::GameControl(QObject *parent) :
    QObject(parent)
{
    qRegisterMetaType<Hand>("Hand");
    qRegisterMetaType<Card>("Card");
    qRegisterMetaType<Cards>("Cards");

    m_punchPlayer = NULL;
    m_punchCards = Cards();

    m_curBet = 0;
}

void GameControl::Init()
{
    m_robotLeft = new Robot(this);
    m_robotRight = new Robot(this);
    m_user = new UserPlayer(this);

    m_robotLeft->SetName(tr("left robot"));
    m_robotRight->SetName(tr("right robot"));
    m_user->SetName(tr("me"));

    // 与三个玩家对接
    connect(m_robotLeft, &Robot::NotifyCallLord, this, &GameControl::OnPlayerCalledLord);
    connect(m_robotRight,  &Robot::NotifyCallLord, this, &GameControl::OnPlayerCalledLord);
    connect(m_user, &Robot::NotifyCallLord, this, &GameControl::OnPlayerCalledLord);

    connect(m_robotLeft, &Robot::NotifyPlayHand, this, &GameControl::OnPlayerPlayedHand);
    connect(m_robotRight, &Robot::NotifyPlayHand, this, &GameControl::OnPlayerPlayedHand);
    connect(m_user, &Robot::NotifyPlayHand, this, &GameControl::OnPlayerPlayedHand);

    connect(m_robotLeft, &Robot::NotifyPickCards, this, &GameControl::OnPlayerPickCards);
    connect(m_robotRight, &Robot::NotifyPickCards, this, &GameControl::OnPlayerPickCards);
    connect(m_user, &Robot::NotifyPickCards, this, &GameControl::OnPlayerPickCards);

    connect(this, &GameControl::NotifyPlayerPunch, m_robotLeft, &Robot::OnPlayerPunch);
    connect(this, &GameControl::NotifyPlayerPunch, m_robotRight, &Robot::OnPlayerPunch);
    connect(this, &GameControl::NotifyPlayerPunch, m_user, &Robot::OnPlayerPunch);

    m_robotLeft->SetPrevPlayer(m_robotRight);
    m_robotLeft->SetNextPlayer(m_user);
    m_robotRight->SetPrevPlayer(m_user);
    m_robotRight->SetNextPlayer(m_robotLeft);
    m_user->SetPrevPlayer(m_robotLeft);
    m_user->SetNextPlayer(m_robotRight);

    m_curPlayer = m_user;
}

void GameControl::AddCard(CardSuit suit, CardPoint point)
{
    Card card;
    card.suit = suit;
    card.point = point;

    m_allCards.Add(card);
}

void GameControl::InitCards()
{
    m_allCards.Clear();

    for (int p = Card_Begin + 1; p < Card_SJ; p++)
    {
        for (int s = Suit_Begin + 1; s < Suit_End; s++)
        {
            AddCard((CardSuit)s, (CardPoint)p);
        }
    }

    AddCard(Suit_Begin, Card_SJ);
    AddCard(Suit_Begin, Card_BJ);
}

void GameControl::ShuffleCards()
{

}

void GameControl::StartCallLord()
{
    m_betList.clear();

    emit NotifyPlayerStatus(m_curPlayer, GameControl::ThinkingForCallLordStatus);
    m_curPlayer->StartCallLord();
}

void GameControl::OnPlayerCalledLord(Player* player, int bet)
{
    NotifyPlayerCalledLord(player, bet);

    if (bet == 3)	// 叫3分，直接当地主
    {
        m_curBet = 3;

        player->SetRole(Player::Lord);
        player->GetPrevPlayer()->SetRole(Player::Farmer);
        player->GetNextPlayer()->SetRole(Player::Farmer);

        m_curPlayer = player;
        player->PickCards(m_allCards);
        m_allCards.Clear();

        // 延迟一下，开始出牌过程
        QTimer::singleShot(1000, this, SLOT(StartPlayHand()));

        return;
    }

    BetRecrod record;
    record.player = player;
    record.bet = bet;
    m_betList.push_back(record);

    // 根据叫分情况划分地主农民角色
    if (m_betList.size() == 3)	// 三人都叫了一遍
    {
        if (m_betList[0].bet == m_betList[1].bet &&
            m_betList[1].bet == m_betList[2].bet)		// 三人叫分一样，重新发牌
        {
            emit NotifyGameStatus(PickingCardStatus);
        }
        else
        {
            BetRecrod record;
            if (m_betList[0].bet >= m_betList[1].bet)
            {
                record = m_betList[0];
            }
            else
            {
                record = m_betList[1];
            }

            if (record.bet < m_betList[2].bet)
            {
                record = m_betList[2];
            }

            record.player->SetRole(Player::Lord);
            record.player->GetPrevPlayer()->SetRole(Player::Farmer);
            record.player->GetNextPlayer()->SetRole(Player::Farmer);
            m_curPlayer = record.player;

            m_curBet = record.bet;

            m_curPlayer->PickCards(m_allCards);
            m_allCards.Clear();

            QTimer::singleShot(1000, this, SLOT(StartPlayHand()));
        }

        return;
    }

    // 让下一个玩家叫分
    Player* nextPlayer = player->GetNextPlayer();
    m_curPlayer = nextPlayer;
    emit NotifyPlayerStatus(m_curPlayer, GameControl::ThinkingForCallLordStatus);
    m_curPlayer->StartCallLord();
}

void GameControl::StartPlayHand()
{
    emit NotifyGameStatus(PlayingHandStatus);

    emit NotifyPlayerStatus(m_curPlayer, GameControl::ThinkingForPlayHandStatus);
    m_curPlayer->StartPlayHand();
}

void GameControl::OnPlayerPlayedHand(Player* player, const Cards& cards)
{
    if (!cards.IsEmpty())
    {
        m_punchPlayer = player;
        m_punchCards = cards;

        NotifyPlayerPunch(m_punchPlayer, m_punchCards);
    }

    // 有炸，底分翻倍
    HandType handType = Hand(cards).GetType();
    if (handType == Hand_Bomb || handType == Hand_Bomb_Jokers)
    {
        m_curBet = m_curBet * 2;
    }

    emit NotifyPlayerPlayHand(m_curPlayer, cards);

    // player已把牌都出完，计算三方得分
    if (player->GetCards().IsEmpty())
    {
        Player* prev = player->GetPrevPlayer();
        Player* next = player->GetNextPlayer();

        if (player->GetRole() == Player::Lord)
        {
            player->SetMark(player->GetMark() + 2 * m_curBet);
            prev->SetMark(prev->GetMark() - m_curBet);
            next->SetMark(next->GetMark() - m_curBet);
        }
        else
        {
            player->SetMark(player->GetMark() + m_curBet);

            if (prev->GetRole() == Player::Lord)
            {
                prev->SetMark(prev->GetMark() - 2 * m_curBet);
                next->SetMark(next->GetMark() + m_curBet);
            }
            else
            {
                prev->SetMark(prev->GetMark() + m_curBet);
                next->SetMark(next->GetMark() - 2 * m_curBet);
            }
        }

        emit NotifyPlayerStatus(player, GameControl::WinningStatus);
        return;
    }

    // 出完牌，轮到下一个玩家
    Player* nextPlayer = player->GetNextPlayer();
    m_curPlayer = nextPlayer;
    emit NotifyPlayerStatus(m_curPlayer, GameControl::ThinkingForPlayHandStatus);
    m_curPlayer->StartPlayHand();
}

void GameControl::OnPlayerPickCards(Player* player, const Cards& cards)
{
    emit NotityPlayerPickCards(player, cards);
}

void GameControl::Clear()
{
    InitCards();

    m_robotLeft->ClearCards();
    m_robotRight->ClearCards();
    m_user->ClearCards();

    m_punchPlayer = NULL;
    m_punchCards.Clear();
    NotifyPlayerPunch(m_punchPlayer, m_punchCards);

    m_betList.clear();
}

Player* GameControl::GetUserPlayer()
{
    return m_user;
}

Player* GameControl::GetLeftRobot()
{
    return m_robotLeft;
}

Player* GameControl::GetRightRobot()
{
    return m_robotRight;
}

Player* GameControl::GetCurrentPlayer()
{
    return m_curPlayer;
}

void GameControl::SetCurrentPlayer(Player* curPlayer)
{
    m_curPlayer = curPlayer;
}

Cards GameControl::GetRestCards()
{
    return m_allCards;
}

Card GameControl::PickOneCard()
{
    Card card = m_allCards.TakeRandomCard();
    return card;
}

Player* GameControl::GetPunchPlayer()
{
    return m_punchPlayer;
}

Cards GameControl::GetPunchCards()
{
    return m_punchCards;
}

int GameControl::GetCurBet()
{
    return m_curBet;
}

void GameControl::SetCurBet(int curBet)
{
    m_curBet = curBet;
}

void GameControl::ClearPlayerMarks()
{
    m_robotLeft->SetMark(0);
    m_robotRight->SetMark(0);
    m_user->SetMark(0);
}

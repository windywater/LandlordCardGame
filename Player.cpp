#include "Player.h"

Player::Player(QObject *parent) :
    QObject(parent)
{
    m_type = Robot;
    m_role = Farmer;
    m_punchPlayer = NULL;
    m_mark = 0;
}

void Player::SetType(Player::Type type)
{
    m_type = type;
}

Player::Type Player::GetType()
{
    return m_type;
}

void Player::SetRole(Player::Role role)
{
    m_role = role;
}

Player::Role Player::GetRole()
{
    return m_role;
}

void Player::SetName(const QString& name)
{
    m_name = name;
}

QString Player::GetName()
{
    return m_name;
}

int Player::GetMark()
{
    return m_mark;
}

void Player::SetMark(int mark)
{
    m_mark = mark;
}

void Player::SetPrevPlayer(Player* player)
{
    m_prevPlayer = player;
}

Player* Player::GetPrevPlayer()
{
    return m_prevPlayer;
}

void Player::SetNextPlayer(Player* player)
{
    m_nextPlayer = player;
}

Player* Player::GetNextPlayer()
{
    return m_nextPlayer;
}

void Player::ClearCards()
{
    m_cards.Clear();
}

void Player::PickCards(const Cards& cards)
{
    m_cards.Add(cards);

    emit NotifyPickCards(this, cards);
}

void Player::PickCard(const Card& card)
{
    Cards cards;
    cards << card;

    PickCards(cards);
}

void Player::StartCallLord()
{

}

void Player::StartPlayHand()
{

}

void Player::ThinkForCallLord()
{
}

void Player::ThinkForPlayHand()
{
}

void Player::CallLord(int bet)
{
    emit NotifyCallLord(this, bet);
}

void Player::PlayHand(const Cards& cards)
{
    m_cards.Remove(cards);

    emit NotifyPlayHand(this, cards);
}

Cards Player::GetCards()
{
    return m_cards;
}

void Player::OnPlayerPunch(Player* player, const Cards& cards)
{
    m_punchPlayer = player;
    m_punchCards = cards;
}

Player* Player::GetPunchPlayer()
{
    return m_punchPlayer;
}

Cards Player::GetPunchCards()
{
    return m_punchCards;
}

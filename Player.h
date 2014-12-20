#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "Cards.h"

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);

public:
    enum Role
    {
        Lord,
        Farmer
    };

    enum Type
    {
        Unknow,
        User,
        Robot
    };

    void CallLord(int bet);
    void PlayHand(const Cards& cards);

signals:
    void NotifyCallLord(Player*, int);
    void NotifyPlayHand(Player*, const Cards&);
    void NotifyPickCards(Player*, const Cards&);

public slots:
    void OnPlayerPunch(Player* player, const Cards& cards);

public:
    void SetType(Type type);
    Type GetType();

    void SetRole(Role role);
    Role GetRole();

    void SetName(const QString& name);
    QString GetName();

    int GetMark();
    void SetMark(int mark);

    void SetPrevPlayer(Player* player);
    Player* GetPrevPlayer();
    void SetNextPlayer(Player* player);
    Player* GetNextPlayer();

    void ClearCards();
    void PickCards(const Cards& cards);
    void PickCard(const Card& card);

    virtual void StartCallLord();
    virtual void StartPlayHand();

    virtual void ThinkForCallLord();
    virtual void ThinkForPlayHand();

    Cards GetCards();

    Player* GetPunchPlayer();
    Cards GetPunchCards();

protected:
    QString m_name;

    Cards m_cards;
    Role m_role;
    Type m_type;
    int m_mark;

    Player* m_punchPlayer;
    Cards m_punchCards;

    Player* m_nextPlayer;
    Player* m_prevPlayer;
};

#endif // PLAYER_H

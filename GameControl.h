#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QObject>
#include "Robot.h"
#include "UserPlayer.h"
#include <QTimer>
#include <QVector>

class GameControl : public QObject
{
    Q_OBJECT
public:
    explicit GameControl(QObject *parent = 0);

public:
    enum GameStatus
    {
        PickingCardStatus,
        CallingLordStatus,
        PlayingHandStatus,
    };

    enum PlayerStatus
    {
        ThinkingForCallLordStatus,
        ThinkingForPlayHandStatus,
        WinningStatus
    };

    void InitCards();		// 初始化所有牌，填充到m_allCards
    void AddCard(CardSuit suit, CardPoint point);
    void ShuffleCards();	// 洗牌
    void Init();		// 初始化玩家，信号槽

    void Clear();

    Player* GetUserPlayer();
    Player* GetLeftRobot();
    Player* GetRightRobot();
    Player* GetCurrentPlayer();
    void SetCurrentPlayer(Player* curPlayer);

    Cards GetRestCards();
    Card PickOneCard();

    Player* GetPunchPlayer();
    Cards GetPunchCards();

    int GetCurBet();
    void SetCurBet(int curBet);

    void ClearPlayerMarks();

signals:
    // 下面信号通知到GamePanel
    void NotifyPlayerCalledLord(Player*, int);	// 玩家叫分
    void NotifyPlayerPlayHand(Player*, const Cards& cards);
    void NotityPlayerPickCards(Player*, const Cards& cards);
    void NotifyPlayerPunch(Player*, const Cards& cards);

    void NotifyGameStatus(GameControl::GameStatus);
    void NotifyPlayerStatus(Player*, GameControl::PlayerStatus);

public slots:
    void OnPlayerCalledLord(Player* player, int bet);
    void OnPlayerPlayedHand(Player* player, const Cards& cards);
    void OnPlayerPickCards(Player* player, const Cards& cards);

    void StartCallLord();	// 开始叫分
    void StartPlayHand();	// 开始出牌

protected:
    struct BetRecrod
    {
        Player* player;
        int bet;
    };

protected:
    Robot* m_robotLeft;
    Robot* m_robotRight;
    UserPlayer* m_user;

    Player* m_curPlayer;
    int m_curBet;

    Cards m_allCards;

    // 当前出有效牌的玩家和牌
    Player* m_punchPlayer;
    Cards m_punchCards;

    QVector<BetRecrod> m_betList;
};

#endif // GAMECONTROL_H

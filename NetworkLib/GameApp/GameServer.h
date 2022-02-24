#pragma once
#include "Utility/TypeDef.h"
#include "Server/BaseServer.h"
#include "../Objects/Player.h"

class GameServer : public _network::BaseServer
{
    enum class GameServerState
    {
        WaitingPlayer,
        GameStart,
    };
    struct PlayerData
    {
        s32 id          = 0;
        s32 playerChara = 0;
    };

public:
    void SendStartPkg();

    void SetGameStart();
    bool IsStarted();

    void HandleConnected(_network::BaseConnection* connection, s32 size);

    void Update();

private:
    bool            _isStarted       = false;
    GameServerState _gameServerState = GameServerState::WaitingPlayer;

    std::array<PlayerData, 2> _playerData;

    uni_ptr<_network::BaseConnection> CreateConnection() override;
};
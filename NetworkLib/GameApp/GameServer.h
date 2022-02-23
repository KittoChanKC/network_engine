#pragma once
#include "Utility/TypeDef.h"
#include "Server/BaseServer.h"
#include "../Objects/Player.h"

class GameServer : public _network::BaseServer
{
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

private:
    bool _isStarted = false;

    uni_ptr<_network::BaseConnection> CreateConnection() override;
};
#pragma once
#include "Utility/TypeDef.h"
#include "Server/BaseServer.h"
#include "../Objects/Player.h"

class GameServer : public _network::BaseServer
{
public:
    void SendStartPkg();

    void SetGameStart();
    bool IsStarted();
private:
    bool _isStarted = false;

    uni_ptr<_network::BaseConnection> CreateConnection() override;
};
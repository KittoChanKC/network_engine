#pragma once
#include "Server/BaseServer.h"
#include "../Objects/Player.h"

class GameServer : public _network::BaseServer
{
public:
    void SendStartPkg();

    Player* GetMyPlayer() { return _pPlayer; };

    void Draw(ImDrawList* drawlist);

    bool gameStart = false;

private:
    uni_ptr<_network::BaseClient> CreateClient() override;

    std::vector<Player> _players;
    Player*             _pPlayer;
};
#pragma once
#include <string>
#include <sstream>
#include "Client/BaseClient.h"
#include "../Objects/Player.h"

class GameClient : public _network::BaseClient
{
public:
    void HandleCmd(const std::string& recvMsg) override;

    void SendPos();

    void Draw(ImDrawList* drawlist);

    Player* GetMyPlayer() { return _pPlayer; };

    bool IsStarted() { return _gameStart; };
private:
    std::vector<Player> _players;
    Player* _pPlayer;

    bool _gameStart = false;
};
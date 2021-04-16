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

    //void Draw(ImDrawList* drawlist);
private:
};
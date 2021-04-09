#pragma once
#include <string>
#include <sstream>
#include "Client/BaseClient.h"

class GameClient : public _network::BaseClient 
{
public: 
    void HandleCmd(const std::string& recvMsg) override;
};

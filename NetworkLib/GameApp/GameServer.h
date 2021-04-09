#pragma once
#include "Server/BaseServer.h"

class GameServer : public _network::BaseServer
{
    uni_ptr<_network::BaseClient> SetClient() override;
};
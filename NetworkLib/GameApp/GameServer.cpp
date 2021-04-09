#include "GameServer.h"
#include "GameClient.h"
uni_ptr<_network::BaseClient> GameServer::SetClient()
{
    return std::make_unique<GameClient>();
}

#include "ServerConnection.h"
#include "GameServer.h"

namespace _network {
ServerConnection::ServerConnection()
{
}
ServerConnection::~ServerConnection()
{
}
void ServerConnection::OnConnected()
{
    BaseConnection::OnConnected();
    _server->SendToAll("Accepted");
}
void ServerConnection::HandleCmd(const std::string& recvMsg)
{

}
}   // namespace _network
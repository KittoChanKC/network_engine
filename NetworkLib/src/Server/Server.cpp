//---------------------------------------------------------------------------
//!	@file	Server.h
//!	@brief	鯖クラス
//---------------------------------------------------------------------------
#include "Server\Server.h"

namespace _network {
Server::Server()
{
}
Server::~Server()
{
}
void Server::Run()
{
    _listenSocket.CreateTCP();

    _network::SocketAddress addr;
    addr.SetIPv4(0, 0, 0, 0);
    addr.SetPortNum(3000);
    
    _listenSocket.Bind(addr);
    _listenSocket.Listen();
    _listenSocket.Accept(_clientSocket);

    _clientSocket.Send(fmt::format("Connected"));
}
_network::Socket& Server::GetSocket()
{
    return _clientSocket;
}
}   // namespace _network
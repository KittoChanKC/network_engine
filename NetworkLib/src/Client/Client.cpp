//---------------------------------------------------------------------------
//!	@file	Client.cpp
//!	@brief	クライアントクラス
//---------------------------------------------------------------------------
#include "Client\Client.h"
namespace _network {
Client::Client()
{
}
Client::~Client()
{
}
void Client::Run()
{
    _socket.CreateTCP();
    
    _network::SocketAddress addr;
    addr.SetIPv4(127, 0, 0, 1);
    addr.SetPortNum(3000);
    _socket.Connect(addr);
    
    _socket.Send("authCode: {}");
}
_network::Socket& Client::GetSocket()
{
    return _socket;
}
}   // namespace _network
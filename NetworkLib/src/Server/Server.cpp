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

    std::vector<char> buf;
    
    for(;;) {
        size_t n = client.AvailableBytesToRead();
    
        if(n == 0) {
            Sleep(0);
            continue;
        }
    
        client.Recv(buf, n);
        buf.push_back(0);
        printf_s("recv %d : %s \n", (int)n, buf.data());
    
        client.Send(buf);
    }
}
}   // namespace _network
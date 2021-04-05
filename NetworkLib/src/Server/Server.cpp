﻿//---------------------------------------------------------------------------
//!	@file	Server.h
//!	@brief	鯖クラス
//---------------------------------------------------------------------------
#include "Server\Server.h"
namespace _network {
Server::Server()
: _quit(false)
{
}
Server::~Server()
{
}
void Server::Run()
{
    _listenSocket.CreateTCP();
    _listenSocket.SetNonBlocking(true);

    _network::SocketAddress addr;
    addr.SetIPv4(0, 0, 0, 0);
    addr.SetPortNum(3000);

    _listenSocket.Bind(addr);
    _listenSocket.Listen();
}
void Server::UpdatePollFD()
{
    if(!_quit) {
        auto n = _clients.size();
        _pollfds.resize(n + 1);
        {
            for(size_t i = 0; i < _clients.size(); i++) {
                auto& client = _clients[i];
                if(!client->IsValid()) {
                    if(_clients.size() > 1) {
                        std::swap(client, _clients.back());
                    }
                    _clients.resize(_clients.size() - 1);
                    i--;
                    continue;
                }
                client->GetPollFD(_pollfds[i]);
            }
        }

        _pollfds[n].Reset(_listenSocket, true, false);
        int ret = _PollFD(_pollfds.data(), _pollfds.size(), 0);
        {
            int i = 0;
            for(auto& client : _clients) {
                try {
                    client->CheckPoll(_pollfds[i]);
                }
                catch(...) {
                    client->Close();
                }
                i++;
            }
        }

        if(_pollfds[n].CanRead()) {
            _clients.emplace_back(new BaseClient);
            auto& newClient = _clients.back();
            newClient->SetServer(this);
            newClient->AcceptFromListenSocket(_listenSocket);
            printf_s("Accepted\n");
        }
    }
}
_network::Socket& Server::GetSocket()
{
    return _clientSocket;
}
void Server::RemoveCloseClients()
{
    for(size_t i = 0; i < _clients.size();) {
        auto& client = _clients[i];
        if(client && client->GetSocket().IsVaild()) {
            i++;
            continue;
        }

        // 当前と最後の交換して 削除します
        try {
            if(_clients.size() > 1) {
                std::swap(client, _clients.back());
            }
            _clients.resize(_clients.size() - 1);
        }
        catch(...) {
            printf("remove closed client fail");
        }
    }
}
}   // namespace _network
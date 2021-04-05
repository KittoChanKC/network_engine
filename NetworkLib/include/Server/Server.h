//---------------------------------------------------------------------------
//!	@file	Server.h
//!	@brief	鯖クラス
//---------------------------------------------------------------------------
#pragma once
#include "Core/Socket.h"
#include "Client/BaseClient.h"
namespace _network {
class Server
{
public:
    Server();
    ~Server();

    // コピー禁止/ムーブ禁止
    Server(const Server&) = delete;
    Server(Server&&)      = delete;
    Server& operator=(const Server&) = delete;
    Server& operator=(Server&&) = delete;

    //---------------------------------------------------------------------------
    // 関数
    //---------------------------------------------------------------------------
    void Run();
    void UpdatePollFD();

    _network::Socket& GetSocket();

    //　切断したクライアントはクライアントリストから削除
    void RemoveCloseClients();

private:
    const size_t _MAX_CLIENT = 16;

    _network::Socket _listenSocket;
    _network::Socket _clientSocket;

    std::vector<uni_ptr<BaseClient>> _clients;
    std::vector<PollFD>          _pollfds;

    bool _quit;
};
}   // namespace _network
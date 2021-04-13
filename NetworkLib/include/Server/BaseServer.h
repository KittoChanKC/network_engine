//---------------------------------------------------------------------------
//!	@file	BaseServer.h
//!	@brief	鯖クラス
//---------------------------------------------------------------------------
#pragma once
#include "Core/Socket.h"
#include "BaseConnection.h"

namespace _network {
class BaseServer
{
public:
    BaseServer();
    ~BaseServer();

    // コピー禁止/ムーブ禁止
    BaseServer(const BaseServer&) = delete;
    BaseServer(BaseServer&&)      = delete;
    BaseServer& operator=(const BaseServer&) = delete;
    BaseServer& operator=(BaseServer&&) = delete;

    //---------------------------------------------------------------------------
    // 関数
    //---------------------------------------------------------------------------
    void Listen();
    void UpdatePollFD();

    _network::Socket& GetSocket();

    //　切断したクライアントはクライアントリストから削除
    void RemoveCloseClients();

    void SendToAll(std::string sendMsg);
    void SendToAllWithoutID(std::string sendMsg, int id);

    virtual uni_ptr<BaseConnection> CreateConnection();

    size_t GetConnectedNum();

protected:
    const size_t _MAX_CLIENT = 3;

    _network::Socket _listenSocket;
    _network::Socket _clientSocket;

    std::vector<uni_ptr<BaseConnection>> _connections;
    std::vector<PollFD>                  _pollfds;

    bool _quit;
};
}   // namespace _network
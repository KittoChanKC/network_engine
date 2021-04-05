﻿//---------------------------------------------------------------------------
//!	@file	Client.h
//!	@brief	クライアントクラス
//---------------------------------------------------------------------------
#pragma once
#include "Core\Socket.h"
namespace _network {

class Server;

class BaseClient
{
public:
    BaseClient();
    ~BaseClient();

    // コピー禁止/ムーブ禁止
    BaseClient(const BaseClient&) = delete;
    BaseClient(BaseClient&&)  = delete;
    BaseClient& operator=(const BaseClient&) = delete;
    BaseClient& operator=(BaseClient&&) = delete;

    enum class Status
    {
        None,
        Connecting,
        Connected,
        Closed
    };

    //---------------------------------------------------------------------------
    // 関数
    //---------------------------------------------------------------------------
    void Run();
    void UpdatePollFD();
    void Close();

    bool NeedSend() const;
    bool NeedRecv() const;

    void OnRecv();
    void OnSend();

    void Connected();

    void CheckPoll(PollFD& fd);

    _network::Socket& GetSocket();
    void              GetPollFD(PollFD& pf);

    bool IsValid();
    void SetServer(Server* server);
    void AcceptFromListenSocket(Socket& listenSocket);

private:
    _network::Socket _socket;
    Server*          _server = nullptr;
    PollFD           _pollfd;

    std::string _sendBuffer;
    size_t      _sendBufferOffset = 0;

    std::string _recvBuffer;

    Status _status = Status::None;
};
}   // namespace _network
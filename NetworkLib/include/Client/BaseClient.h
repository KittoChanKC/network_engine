//---------------------------------------------------------------------------
//!	@file	Client.h
//!	@brief	クライアントクラス
//---------------------------------------------------------------------------
#pragma once
#include "Core\Socket.h"
namespace _network {

class BaseServer;

class BaseClient
{
public:
    BaseClient();
    ~BaseClient();

    // コピー禁止/ムーブ禁止
    BaseClient(const BaseClient&) = delete;
    BaseClient(BaseClient&&)      = delete;
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
    bool IsConnected();

    void SetServer(BaseServer* server);
    void AcceptFromListenSocket(Socket& listenSocket);

    void SetSendBuffer(const std::string& sendMsg);

    virtual void HandleCmd(const std::string& recvMsg){};
protected:
    _network::Socket _socket;
    BaseServer*      _server = nullptr;
    PollFD           _pollfd;

    std::string _sendBuffer;
    size_t      _sendBufferOffset = 0;

    std::string _recvBuffer;

    Status _status = Status::None;
};
}   // namespace _network
//---------------------------------------------------------------------------
//!	@file	BaseConnection.h
//!	@brief	鯖につながるコンネクション
//---------------------------------------------------------------------------
#pragma once
#include "Core/Socket.h"
#include <string>
namespace _network {
class BaseServer;

class BaseConnection
{
public:
    BaseConnection();
    virtual ~BaseConnection();

    // コピー禁止/ムーブ禁止
    BaseConnection(const BaseConnection&) = delete;
    BaseConnection(BaseConnection&&)      = delete;
    BaseConnection& operator=(const BaseConnection&) = delete;
    BaseConnection& operator=(BaseConnection&&) = delete;

    // 列挙型
    enum class Status
    {
        None,
        Accepted,
        Rejected,
        Connecting,
        Connected,
        Closed
    };

    //---------------------------------------------------------------------------
    // 関数
    //---------------------------------------------------------------------------
    void AcceptFromListenSocket(Socket& listenSocket);

    void CheckPoll(PollFD& fd);
    void OnRecv();
    void OnSend();
    void Close();

    bool IsValid();

    _network::Socket& GetSocket();
    void              GetPollFD(PollFD& pf);

    void SetServer(BaseServer* server);
    
    void SetSendBuffer(const std::string& sendMsg);

    virtual void HandleCmd(const std::string& recvMsg){};
    virtual void OnConnected();
protected:
    _network::Socket _socket;
    PollFD           _pollfd;

    BaseServer* _server = nullptr;

    std::string _sendBuffer;
    size_t      _sendBufferOffset = 0;

    std::string _recvBuffer;

    Status _status = Status::None;
};
}   // namespace _network
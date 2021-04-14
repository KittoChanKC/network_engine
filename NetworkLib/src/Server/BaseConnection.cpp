//---------------------------------------------------------------------------
//!	@file	BaseConnection.h
//!	@brief	鯖につながるコンネクション
//---------------------------------------------------------------------------
#include "Server\BaseConnection.h"
namespace _network {
BaseConnection::BaseConnection()
{
}

BaseConnection::~BaseConnection()
{
}

void BaseConnection::AcceptFromListenSocket(Socket& listenSocket)
{
    listenSocket.Accept(_socket);
    _pollfd.fd = _socket.GetSocket();
    OnConnected();
}

void BaseConnection::OnConnected()
{
    _status = Status::Connected;
    printf_s("connected\n");
}

void BaseConnection::CheckPoll(PollFD& fd)
{
    if(fd.CanRead()) {
        OnRecv();
    }

    if(fd.CanWrite()) {
        OnSend();
    }
}

void BaseConnection::OnRecv()
{
    size_t n = _socket.AvailableBytesToRead();
    if(!n) {
        Close();
        return;
    }
    _recvBuffer.resize(n);
    auto* p   = &*(_recvBuffer.begin());
    int   ret = _socket.Recv(p, n);
    if(ret <= 0) {
        Close();
        return;
    }

    _recvBuffer.push_back(0);
    
    HandleCmd(_recvBuffer);
    _recvBuffer.clear();
}

void BaseConnection::OnSend()
{
    if(_status == Status::Connecting) {
        _status = Status::Connected;
    }

    if(_sendBuffer.size() <= 0) {
        return;
    }
    size_t ret = _socket.Send(_sendBuffer.data(), _sendBuffer.size());
    if(ret <= 0) {
        Close();
        return;
    }
    printf_s("Send: %s\n", _sendBuffer.c_str());
    _sendBuffer.clear();
}

void BaseConnection::Close()
{
    _status = Status::Closed;
    printf_s("> client %p: close\n", this);
    _socket.Close();
}

bool BaseConnection::IsValid()
{
    return _socket.IsVaild();
}
_network::Socket& BaseConnection::GetSocket()
{
    return _socket;
}
void BaseConnection::GetPollFD(PollFD& pf)
{
    bool write = false;
    if(_status == Status::Connecting) {
        write = true;
    }
    if(_status == Status::Connected && _sendBuffer.size())
        write = true;

    pf.Reset(_socket, true, write);
}
void BaseConnection::SetServer(BaseServer* server)
{
    _server = server;
}
void BaseConnection::SetSendBuffer(const std::string& sendMsg)
{
    _sendBuffer.append(sendMsg);
}
void BaseConnection::PrintSendBuffer()
{
    printf_s("%s", _sendBuffer.c_str());
}
}   // namespace _network

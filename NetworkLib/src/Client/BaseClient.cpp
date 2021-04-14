//---------------------------------------------------------------------------
//!	@file	Client.cpp
//!	@brief	クライアントクラス
//---------------------------------------------------------------------------
#include "Client/BaseClient.h"
#include "Server/BaseServer.h"

#include <sstream>

namespace _network {
BaseClient::BaseClient()
{
}
BaseClient::~BaseClient()
{
}
void BaseClient::Connect()
{
    _socket.CreateTCP();

    _network::SocketAddress addr;
    addr.SetIPv4(127, 0, 0, 1);
    addr.SetPortNum(3000);
    _socket.Connect(addr);
    _status = Status::Connecting;
}
void BaseClient::UpdatePollFD()
{
    PollFD pf;
    GetPollFD(pf);

    if(_PollFD(&pf, 1, 0)) {
        CheckPoll(pf);
    }
}

void BaseClient::Close()
{
    _status = Status::Closed;
    printf_s("> client %p: close\n", this);
    _socket.Close();
}
bool BaseClient::NeedSend() const
{
    return _sendBufferOffset < _sendBuffer.size();
}
bool BaseClient::NeedRecv() const
{
    return !NeedSend();
}
void BaseClient::OnRecv()
{
    size_t n = _socket.AvailableBytesToRead();
    if(!n) {
        Close();
        return;
    }
#if 0
    //auto oldSize = _recvBuffer.size();
    //auto newSize = oldSize + n;

    ///* if(newSize > kHeaderSizeLimit) {
    //    throw ErrorHandler("Excess header size limit");
    //}*/

    //_recvBuffer.resize(newSize);
    //auto* p   = &*(_recvBuffer.begin() + oldSize);
    //int   ret = _socket.Recv(p, n);
    //if(ret <= 0) {
    //    Close();
    //    //isConnected = false;
    //    return;
    //}
#else
    //std::vector<char> buf;
    _recvBuffer.resize(n);
    auto* p   = &*(_recvBuffer.begin());
    int   ret = _socket.Recv(p, n);
    if(ret <= 0) {
        Close();
        return;
    }
#endif
    
    _recvBuffer.push_back(0);
   
    HandleCmd(_recvBuffer);
    _recvBuffer.clear();
}
void BaseClient::OnSend()
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
    //_sendBufferOffset += ret;
}
void BaseClient::Connected()
{
    _status = Status::Connected;
    printf_s("connected\n");
}
void BaseClient::CheckPoll(PollFD& fd)
{
    if(fd.CanRead()) {
        OnRecv();
    }

    if(fd.CanWrite()) {
        OnSend();
    }
}
_network::Socket& BaseClient::GetSocket()
{
    return _socket;
}
void BaseClient::GetPollFD(PollFD& pf)
{
    bool write = false;
    if(_status == Status::Connecting) {
        write = true;
    }
    if(_status == Status::Connected && _sendBuffer.size())
        write = true;

    pf.Reset(_socket, true, write);
}
bool BaseClient::IsValid()
{
    return _socket.IsVaild();
}
bool BaseClient::IsConnected()
{
    return _status == Status::Connected;
}
void BaseClient::AcceptFromListenSocket(Socket& listenSocket)
{
    listenSocket.Accept(_socket);
    _pollfd.fd = _socket.GetSocket();
    Connected();
}
void BaseClient::SetSendBuffer(const std::string& sendMsg)
{
    _sendBuffer.append(sendMsg);
}
}   // namespace _network
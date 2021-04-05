//---------------------------------------------------------------------------
//!	@file	Client.cpp
//!	@brief	クライアントクラス
//---------------------------------------------------------------------------
#include "Client/BaseClient.h"
#include "Server/BaseServer.h"

namespace _network {
BaseClient::BaseClient()
{
}
BaseClient::~BaseClient()
{
}
void BaseClient::Run()
{
    _socket.CreateTCP();
    
    _network::SocketAddress addr;
    addr.SetIPv4(127, 0, 0, 1);
    addr.SetPortNum(3000);
    _socket.Connect(addr);
    
    _socket.Send("authCode: {}");
}
void BaseClient::UpdatePollFD()
{
    PollFD pf;
    GetPollFD(pf);

    if(_PollFD(&pf, 1, 0)) {
        CheckPoll(pf);
    }
    int ret = _socket.Send(fmt::format("POS {} {}\n", 1, 2).c_str());
    if(ret <= 0) {
        throw ErrorHandler("s");
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

    auto oldSize = _recvBuffer.size();
    auto newSize = oldSize + n;

   /* if(newSize > kHeaderSizeLimit) {
        throw ErrorHandler("Excess header size limit");
    }*/

    _recvBuffer.resize(newSize);
    auto* p = &*(_recvBuffer.begin() + oldSize);
    int ret = _socket.Recv(p, n);
    if(ret <= 0) {
        Close();
       // isConnected = false;
        return;
    }

    _recvBuffer.push_back(0);
   // HandleCmd(buf.data());
    printf("recv %d: %s\n", (int)n, _recvBuffer.data());
}
void BaseClient::OnSend()
{
    if(_sendBufferOffset < _sendBuffer.size()) {
        size_t n = _sendBuffer.size() - _sendBufferOffset;
        size_t ret = _socket.Send(_sendBuffer.data() + _sendBufferOffset, n);
    }

    if(_sendBufferOffset < _sendBuffer.size())
        return;

    _sendBuffer.clear();
    _sendBufferOffset = 0;
}
void BaseClient::Connected()
{
    _status = Status::Connected;
    printf_s("connected\n");
    //onConnected();
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
void BaseClient::SetServer(BaseServer* server)
{
    _server = server;
}
void BaseClient::AcceptFromListenSocket(Socket& listenSocket)
{
    listenSocket.Accept(_socket);
    _pollfd.fd = _socket.GetSocket();
    Connected();
}
}   // namespace _network
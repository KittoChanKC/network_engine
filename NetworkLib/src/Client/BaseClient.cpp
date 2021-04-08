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
void BaseClient::Run()
{
    _socket.CreateTCP();

    _network::SocketAddress addr;
    addr.SetIPv4(127, 0, 0, 1);
    addr.SetPortNum(3000);
    _socket.Connect(addr);
    _status = Status::Connecting;

    //_socket.Send("authCode: {}");
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
    printf("recv%s\n", _recvBuffer.c_str());
    HandleCmd(_recvBuffer);
    //printf("client recv %d: %s\n", (int)n, _recvBuffer.data());
    _recvBuffer.clear();
}
void BaseClient::OnSend()
{
    if(_status == Status::Connecting) {
        _status = Status::Connected;
    }

    //if(_sendBufferOffset >= _sendBuffer.size()) {
    //    _sendBufferOffset = 0;
    //    _sendBuffer.clear();
    //    return;
    //}

    //size_t n = _sendBuffer.size() - _sendBufferOffset;
    //size_t ret = _socket.Send(&_sendBuffer[_sendBufferOffset], n);
    size_t ret = _socket.Send(_sendBuffer.data(), _sendBuffer.size());
    //printf_s("Send: %s\n===End===\n", _sendBuffer.c_str());
    if(ret <= 0) {
        Close();
        return;
    }
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
void BaseClient::SetSendBuffer(std::string sendMsg)
{
    _sendBuffer.append(sendMsg);
}
void BaseClient::HandleCmd(std::string recvMsg)
{
 /*   std::stringstream sstr(recvMsg);

    std::string cmd;
    sstr >> cmd;
    if(cmd == "POS") {
        _server->SendToAll("sssssssss");
    }*/
    //while(std::getline(sstr, cmd, '\n')) {
    //    //printf_s("%s\n",cmd.c_str());
    //    if(cmd == "POS") {
    //        _server->SendToAll("sssssssss");
    //    }
    //}
}
}   // namespace _network
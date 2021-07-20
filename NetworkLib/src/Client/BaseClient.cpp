//---------------------------------------------------------------------------
//!	@file	Client.cpp
//!	@brief	クライアントクラス
//---------------------------------------------------------------------------
#include "Client/BaseClient.h"
#include "Server/BaseServer.h"

#include <sstream>

namespace _network {
//---------------------------------------------------------------------------
//!	コンストラクタ
//---------------------------------------------------------------------------
BaseClient::BaseClient()
{
}
//---------------------------------------------------------------------------
//! デストラクタ
//---------------------------------------------------------------------------
BaseClient::~BaseClient()
{
}
//---------------------------------------------------------------------------
//! 繋がる
//---------------------------------------------------------------------------
void BaseClient::Connect()
{
    _socket.CreateTCP();

    _network::SocketAddress addr;
    addr.SetIPv4(127, 0, 0, 1);
    addr.SetPortNum(3000);
    _socket.Connect(addr);
    _status = Status::Connecting;
}
//---------------------------------------------------------------------------
//!	POLL更新 -> CheckPoll()
//---------------------------------------------------------------------------
void BaseClient::UpdatePollFD()
{
    PollFD pf;
    GetPollFD(pf);

    if(_PollFD(&pf, 1, 0)) {
        CheckPoll(pf);
    }
}

//---------------------------------------------------------------------------
//!	ネットワーク中断する
//---------------------------------------------------------------------------
void BaseClient::Close()
{
    _status = Status::Closed;
    printf_s("> client %p: close\n", this);
    _socket.Close();
}
//---------------------------------------------------------------------------
//!	送信の判定
//---------------------------------------------------------------------------
bool BaseClient::NeedSend() const
{
    return _sendBufferOffset < _sendBuffer.size();
}
//---------------------------------------------------------------------------
//! 受信の判定
//---------------------------------------------------------------------------
bool BaseClient::NeedRecv() const
{
    return !NeedSend();
}
//---------------------------------------------------------------------------
//!	受信
//---------------------------------------------------------------------------
void BaseClient::OnRecv()
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
//---------------------------------------------------------------------------
//!	送信
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
//!	繋がっている
//---------------------------------------------------------------------------
void BaseClient::Connected()
{
    _status = Status::Connected;
    printf_s("connected\n");
}
//---------------------------------------------------------------------------
//!	ネットワークパケットの収発 (recv / Send)
//---------------------------------------------------------------------------
void BaseClient::CheckPoll(PollFD& fd)
{
    if(fd.CanRead()) {
        OnRecv();
    }

    if(fd.CanWrite()) {
        OnSend();
    }
}
//---------------------------------------------------------------------------
//!	ソケット取得
//---------------------------------------------------------------------------
_network::Socket& BaseClient::GetSocket()
{
    return _socket;
}
//---------------------------------------------------------------------------
//!	PollFD取得
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
//!	ソケット有効か
//---------------------------------------------------------------------------
bool BaseClient::IsValid()
{
    return _socket.IsVaild();
}
//---------------------------------------------------------------------------
//!	サーバーと繋がっているか
//---------------------------------------------------------------------------
bool BaseClient::IsConnected()
{
    return _status == Status::Connected;
}
//---------------------------------------------------------------------------
//!	サーバーがクライアントの通信を許可する
//---------------------------------------------------------------------------
void BaseClient::AcceptFromListenSocket(Socket& listenSocket)
{
    listenSocket.Accept(_socket);
    _pollfd.fd = _socket.GetSocket();
    Connected();
}
//---------------------------------------------------------------------------
//!	送信バッファ
//---------------------------------------------------------------------------
void BaseClient::SetSendBuffer(const std::string& sendMsg)
{
    _sendBuffer.append(sendMsg);
}
//---------------------------------------------------------------------------
//!	Send Bufferの中身をプリント
//---------------------------------------------------------------------------
void BaseClient::PrintSendBuffer()
{
    printf_s("%s", _sendBuffer.c_str());
}
}   // namespace _network
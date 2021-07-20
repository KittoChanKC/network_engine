//---------------------------------------------------------------------------
//!	@file	BaseConnection.h
//!	@brief	鯖につながるコンネクション
//---------------------------------------------------------------------------
#include "Server\BaseConnection.h"
namespace _network {
//---------------------------------------------------------------------------
//! コンストラクタ
//---------------------------------------------------------------------------
BaseConnection::BaseConnection()
{
}
//---------------------------------------------------------------------------
//! デストラクタ
//---------------------------------------------------------------------------
BaseConnection::~BaseConnection()
{
}
//---------------------------------------------------------------------------
//! 繋がる許可
//---------------------------------------------------------------------------

void BaseConnection::AcceptFromListenSocket(Socket& listenSocket)
{
    listenSocket.Accept(_socket);
    _pollfd.fd = _socket.GetSocket();
    OnConnected();
}
//---------------------------------------------------------------------------
//! コンストラクタ
//---------------------------------------------------------------------------

void BaseConnection::OnConnected()
{
    _status = Status::Connected;
    printf_s("connected\n");
}
//---------------------------------------------------------------------------
//! 接続の処理（Receive/Send）
//---------------------------------------------------------------------------
void BaseConnection::CheckPoll(PollFD& fd)
{
    if(fd.CanRead()) {
        OnRecv();
    }

    if(fd.CanWrite()) {
        OnSend();
    }
}
//---------------------------------------------------------------------------
//! 受信処理
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
//! 送信処理
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
//! 切断
//---------------------------------------------------------------------------
void BaseConnection::Close()
{
    _status = Status::Closed;
    printf_s("> client %p: close\n", this);
    _socket.Close();
}
//---------------------------------------------------------------------------
//! 有効かどうか
//---------------------------------------------------------------------------
bool BaseConnection::IsValid()
{
    return _socket.IsVaild();
}
//---------------------------------------------------------------------------
//! ソケット取得
//---------------------------------------------------------------------------
_network::Socket& BaseConnection::GetSocket()
{
    return _socket;
}
//---------------------------------------------------------------------------
//! PollFD取得
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
//! サーバーセッター設定
//---------------------------------------------------------------------------
void BaseConnection::SetServer(BaseServer* server)
{
    _server = server;
}
//---------------------------------------------------------------------------
//! 送信バッファ設置
//---------------------------------------------------------------------------
void BaseConnection::SetSendBuffer(const std::string& sendMsg)
{
    _sendBuffer.append(sendMsg);
}
//---------------------------------------------------------------------------
//! PrintSendBuffer
//---------------------------------------------------------------------------
void BaseConnection::PrintSendBuffer()
{
    printf_s("%s", _sendBuffer.c_str());
}
}   // namespace _network

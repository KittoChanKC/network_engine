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
    BaseConnection();            //!< コンストラクタ
    virtual ~BaseConnection();   //!< デストラクタ

    // コピー禁止/ムーブ禁止
    BaseConnection(const BaseConnection&) = delete;
    BaseConnection(BaseConnection&&)      = delete;
    BaseConnection& operator=(const BaseConnection&) = delete;
    BaseConnection& operator=(BaseConnection&&) = delete;

    // 列挙型
    //現在の状態
    enum class Status
    {
        None,         //!< 無し
        Accepted,     //!< 許可
        Rejected,     //!< 拒否
        Connecting,   //!< 接続している
        Connected,    //!< 接続した
        Closed        //!< 閉じてる
    };

    //---------------------------------------------------------------------------
    // 関数
    //---------------------------------------------------------------------------
    void AcceptFromListenSocket(Socket& listenSocket);   //!< 繋がる許可
    void CheckPoll(PollFD& fd);                          //!< 接続の処理（Receive/Send）

    void OnRecv();   //!< 受信処理
    void OnSend();   //!< 送信処理
    void Close();    //!< 切断

    bool IsValid();   //!< 有効かどうか

    _network::Socket& GetSocket();             //< ソケット取得
    void              GetPollFD(PollFD& pf);   //< PollFD取得

    void SetServer(BaseServer* server);   //!< サーバーセッター

    void SetSendBuffer(const std::string& sendMsg);   //!< 送信バッファ設置

    void PrintSendBuffer(); //!< SendBuffer中の中身プリント

    virtual void HandleCmd(const std::string& recvMsg){};   //!< コマンドの処理
    virtual void OnConnected();                             //!< 繋がっている時の処理

protected:
    _network::Socket _socket;   //!< ソケット
    PollFD           _pollfd;   //!< POLLFD (監視)

    BaseServer* _server = nullptr;   //!< サーバー

    std::string _sendBuffer;             //!< 発信用バッファ
    size_t      _sendBufferOffset = 0;   //!< 発信用バッファのサイズ

    std::string _recvBuffer;   //!< 受信用バッファ

    Status _status = Status::None;   //!< 通信状態
};
}   // namespace _network
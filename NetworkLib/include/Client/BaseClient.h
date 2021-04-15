//---------------------------------------------------------------------------
//!	@file	Client.h
//!	@brief	クライアントクラス
//---------------------------------------------------------------------------
#pragma once
#include "Core/Socket.h"
namespace _network {

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

    // ネットワークの状態
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
    void Connect();               //! 繋がる
    void UpdatePollFD();          //! POLL更新 -> CheckPoll()
    void CheckPoll(PollFD& fd);   //! ネットワークパケットの収発 (recv / Send)
    void Close();                 //! ネットワーク中断する

    bool NeedSend() const;   //! 送信の判定
    bool NeedRecv() const;   //! 受信の判定

    void OnSend();   //! 送信
    void OnRecv();   //! 受信

    void Connected();   //! 繋がっている

    _network::Socket& GetSocket();             //ソケット取得
    void              GetPollFD(PollFD& pf);   // PollFD取得

    bool IsValid();       //! ソケット有効か
    bool IsConnected();   //! サーバーと繋がっているか

    void AcceptFromListenSocket(Socket& listenSocket);   //! サーバーがクライアントの通信を許可する

    void SetSendBuffer(const std::string& sendMsg);   //! 送信バッファ

    // 仮想関数
    virtual void HandleCmd(const std::string& recvMsg){};   //! コマンドの処理

    void PrintSendBuffer();

protected:
    _network::Socket _socket;   //! ソケット
    PollFD           _pollfd;   //! POLLFD (監視)

    std::string _sendBuffer;             //! 発信用バッファ
    size_t      _sendBufferOffset = 0;   //! 発信用バッファのサイズ

    std::string _recvBuffer;   //! 受信用バッファ

    Status _status = Status::None;   //! 通信状態
};
}   // namespace _network
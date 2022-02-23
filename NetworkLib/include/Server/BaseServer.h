//---------------------------------------------------------------------------
//!	@file	BaseServer.h
//!	@brief	鯖クラス
//---------------------------------------------------------------------------
#pragma once
#include "Core/Socket.h"
#include "BaseConnection.h"

namespace _network {
class BaseServer
{
public:
    BaseServer();
    ~BaseServer();

    // コピー禁止/ムーブ禁止
    BaseServer(const BaseServer&) = delete;
    BaseServer(BaseServer&&)      = delete;
    BaseServer& operator=(const BaseServer&) = delete;
    BaseServer& operator=(BaseServer&&) = delete;

    //---------------------------------------------------------------------------
    // 関数
    //---------------------------------------------------------------------------
    void Listen();         //!< クライアントのソケット接続準備
    void UpdatePollFD();   //!< POLL更新

    //　切断したクライアントはクライアントリストから削除
    void RemoveCloseClients();

    void SendToAll(std::string sendMsg);                    //!< 繋がっているクライアントに送信する
    void SendToAllWithoutID(std::string sendMsg, int id);   //!< 指定IDに送信しない

    size_t                          GetConnectedNum();    //!< 繋がっているクライアントの数
    virtual uni_ptr<BaseConnection> CreateConnection();   //!< クライアントのコンネックション

    virtual void HandleConnected(_network::BaseConnection* connection, s32 size) = 0;

protected:
    const size_t _MAX_CLIENT = 3;   //!< 最大接続数

    _network::Socket _listenSocket;   //!< 接続待ちソケット

    std::vector<uni_ptr<BaseConnection>> _connections;   //!< コンネックション
    std::vector<PollFD>                  _pollfds;       //!< POLLFD

    bool _quit = false;   //!< サーバーを閉じる
};
}   // namespace _network
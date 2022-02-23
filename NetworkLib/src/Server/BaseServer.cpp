//---------------------------------------------------------------------------
//!	@file	BaseServer.cpp
//!	@brief	鯖クラス
//---------------------------------------------------------------------------
#include "Server/BaseServer.h"

namespace _network {
//---------------------------------------------------------------------------
//! コンストラクタ
//---------------------------------------------------------------------------
BaseServer::BaseServer()
: _quit(false)
{
}
//---------------------------------------------------------------------------
//! デストラクタ
//---------------------------------------------------------------------------
BaseServer::~BaseServer()
{
}
//---------------------------------------------------------------------------
//! クライアントのソケット接続準備
//---------------------------------------------------------------------------
void BaseServer::Listen()
{
    _listenSocket.CreateTCP();
    _listenSocket.SetNonBlocking(true);

    _network::SocketAddress addr;
    addr.SetIPv4(0, 0, 0, 0);
    addr.SetPortNum(3000);

    _listenSocket.Bind(addr);
    _listenSocket.Listen();
}
//---------------------------------------------------------------------------
//! POLL更新
//---------------------------------------------------------------------------
void BaseServer::UpdatePollFD()
{
    if(!_quit) {
        auto n = _connections.size();
        _pollfds.resize(n + 1);
        {
            for(size_t i = 0; i < _connections.size(); i++) {
                auto& connection = _connections[i];
                if(!connection->IsValid()) {
                    if(_connections.size() > 1) {
                        std::swap(connection, _connections.back());
                    }
                    _connections.resize(_connections.size() - 1);
                    i--;
                    continue;
                }
                connection->GetPollFD(_pollfds[i]);
            }
        }

        _pollfds[n].Reset(_listenSocket, true, false);
        int ret = _PollFD(_pollfds.data(), _pollfds.size(), 0);
        {
            int i = 0;
            for(auto& connection : _connections) {
                try {
                    connection->CheckPoll(_pollfds[i]);
                }
                catch(...) {
                    connection->Close();
                }
                i++;
            }
        }

        if(_pollfds[n].CanRead()) {
            if(_connections.size() < _MAX_CLIENT) {
                _connections.emplace_back(std::move(CreateConnection()));
                auto& newConnection = _connections.back();
                newConnection->SetServer(this);
                newConnection->AcceptFromListenSocket(_listenSocket);

                //newConnection->SetSendBuffer(fmt::format("Accept {}", _connections.size()));

                HandleConnected(newConnection.get(), _connections.size());
            }
            else {
                printf_s("Full\n");
                // ...
            }
        }
    }
}

//---------------------------------------------------------------------------
//!　切断したクライアントはクライアントリストから削除
//---------------------------------------------------------------------------
void BaseServer::RemoveCloseClients()
{
    for(size_t i = 0; i < _connections.size();) {
        auto& connection = _connections[i];
        if(connection && connection->GetSocket().IsVaild()) {
            i++;
            continue;
        }

        // 当前と最後の交換して 削除します
        try {
            if(_connections.size() > 1) {
                std::swap(connection, _connections.back());
            }
            _connections.resize(_connections.size() - 1);
        }
        catch(...) {
            printf("remove closed client fail");
        }
    }
}
//---------------------------------------------------------------------------
//! 繋がっているクライアントに送信する
//---------------------------------------------------------------------------
void BaseServer::SendToAll(std::string sendMsg)
{
    int i = 0;
    for(auto& c : _connections) {
        c->SetSendBuffer(fmt::format("{} {}", sendMsg, i));
        i++;
    }
}
//---------------------------------------------------------------------------
//! 指定IDに送信しない
//---------------------------------------------------------------------------
void BaseServer::SendToAllWithoutID(std::string sendMsg, int id)
{
    for(int i = 0; i < _connections.size(); i++) {
        if(i == id) continue;
        _connections[i]->SetSendBuffer(fmt::format("{}", sendMsg));
    }
}
//---------------------------------------------------------------------------
//! クライアントのコンネックションを生成
//---------------------------------------------------------------------------
uni_ptr<BaseConnection> BaseServer::CreateConnection()
{
    return std::make_unique<BaseConnection>();
}
//---------------------------------------------------------------------------
//! 繋がっているクライアントの数
//---------------------------------------------------------------------------
size_t BaseServer::GetConnectedNum()
{
    return _connections.size();
}
}   // namespace _network
//---------------------------------------------------------------------------
//!	@file	Server.h
//!	@brief	鯖クラス
//---------------------------------------------------------------------------
#include "Core/Socket.h"

namespace _network {
class Server
{
public:
    Server();
    ~Server();

    // コピー禁止/ムーブ禁止
    Server(const Server&) = delete;
    Server(Server&&)      = delete;
    Server& operator=(const Server&) = delete;
    Server& operator=(Server&&) = delete;

    //---------------------------------------------------------------------------
    // 関数
    //---------------------------------------------------------------------------
    void Run();

private:
    _network::Socket _listenSocket;
};
}   // namespace _network
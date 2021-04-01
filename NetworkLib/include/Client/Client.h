//---------------------------------------------------------------------------
//!	@file	Client.h
//!	@brief	クライアントクラス
//---------------------------------------------------------------------------
#include "Core\Socket.h"
namespace _network {
class Client
{
public:
    Client();
    ~Client();

    // コピー禁止/ムーブ禁止
    Client(const Client&) = delete;
    Client(Client&&)      = delete;
    Client& operator=(const Client&) = delete;
    Client& operator=(Client&&) = delete;

    //---------------------------------------------------------------------------
    // 関数
    //---------------------------------------------------------------------------
    void Run();

     _network::Socket& GetSocket();

private:
    _network::Socket _socket;
};
}   // namespace _network
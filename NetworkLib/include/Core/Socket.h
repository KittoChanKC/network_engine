//---------------------------------------------------------------------------
//!	@file	Socket.h
//!	@brief	ネットワークソケットクラス
//!
//!           はじめ
//!             ↓
//! socket()(1) ソケット生成
//!             ↓
//! bind()  (2) ソケット登録
//!             ↓
//! listen()(3) ソケット接続準備
//!             ↓
//! accept()(4) ソケット接続待機	←接続要求
//!             ↓
//! read() / write()(5) 受信 / 送信	<- データ -> クライアント側プログラム
//!             ↓
//! close() (6) ソケット切断
//!             ↓
//!           終わり
//---------------------------------------------------------------------------
#pragma once
#include "SocketAddress.h"
namespace _network {
class Socket
{
public:
    Socket();
    ~Socket();

    // コピー禁止/ムーブ禁止
    Socket(const Socket&) = delete;
    Socket(Socket&&)      = delete;
    Socket& operator=(const Socket&) = delete;
    Socket& operator=(Socket&&) = delete;

    //---------------------------------------------------------------------------
    // 関数
    //---------------------------------------------------------------------------

    //　鯖に関して関数
    void CreateTCP();                          //! TCPソケット生成
    void Bind(const SocketAddress& addr);      //! ソケット登録
    void Listen(s32 backLog = 64);             //! ソケット接続準備
    void Connect(const SocketAddress& addr);   //! 接続
    bool Accept(Socket& acceptedSocket);       //! ソケット接続待機	<- 接続要求
    void Close();                              //! ソケット切断

    //! メッセージを送る(アドレスを指定する)
    int SendTo(const SocketAddress& addr, const char* data, size_t dataSize);
    int SendTo(const SocketAddress& addr, const char* data);

    //! 送信
    int Send(const char* data, size_t dataSize);
    int Send(const std::vector<char>& data);
    int Send(const char* data);
    int Send(const std::string& s);

    //! 受信
    int Recv(std::vector<char>& buf, size_t bytesToRecv);
    int Recv(char* buf, size_t bytesToRecv);

    bool IsVaild(); //! ソケット有効か

    SOCKET GetSocket(); //! ソケット取得

    void SetNonBlocking(bool b); // ノンブロッキング設定 非同期的に実行されます。

    //! 受けたパケットのバイト
    size_t AvailableBytesToRead();

private:
    SOCKET _socket = INVALID_SOCKET;
};

//---------------------------------------------------------------------------
// POLL
//---------------------------------------------------------------------------
#ifdef _WIN32
typedef WSAPOLLFD PollFD_Base;
#else
#error todo impl
typedef struct pollfd MyPollFD_Base;
#endif

struct PollFD : PollFD_Base
{
    PollFD()
    {
        fd      = INVALID_SOCKET;
        events  = 0;
        revents = 0;
    }

    void Reset(Socket& socket, bool read, bool write)
    {
        fd      = socket.GetSocket();
        events  = 0;
        revents = 0;

        if(read)
            events |= POLLIN;
        if(write)
            events |= POLLOUT;
    }

    bool CanRead() { return revents & POLLIN; }
    bool CanWrite() { return revents & POLLOUT; }
};
#ifdef _WIN32
inline int _PollFD(PollFD* pollfd, size_t pollfdCount, int timeoutMilliSecond)
{
    int ret = ::WSAPoll(pollfd, (ULONG)pollfdCount, timeoutMilliSecond);
    if(ret < 0) {
        //throw ErrorHandler("Poll Fail");
        printf_s("fail");
    }

    return ret;
}
#else
#TODO
#endif

}   // namespace _network
//---------------------------------------------------------------------------
//!	@file	Socket.h
//!	@brief	ネットワークソケットクラス
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
    void CreateTCP();
    void Close();

    //　鯖に関して関数
    void Bind(const SocketAddress& addr);
    void Listen(s32 backLog = 64);
    bool Accept(Socket& acceptedSocket);

    // 接続
    void Connect(const SocketAddress& addr);

    // メッセージを送る(アドレスを指定する)
    int SendTo(const SocketAddress& addr, const char* data, size_t dataSize);
    int SendTo(const SocketAddress& addr, const char* data);

    int Send(const char* data, size_t dataSize);
    int Send(const std::vector<char>& data);
    int Send(const char* data);
    int Send(const std::string& s);
    // メッセージを受ける
    int Recv(std::vector<char>& buf, size_t bytesToRecv);
    int Recv(char* buf, size_t bytesToRecv);

    bool IsVaild();

    SOCKET GetSocket();

    void SetNonBlocking(bool b);

    //　受けたメッセージのバイト
    size_t AvailableBytesToRead();

private:
    SOCKET _socket = INVALID_SOCKET;
};

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
inline int _PollFD(PollFD* pollfd, ULONG pollfdCount, int timeoutMilliSecond)
{
    int ret = ::WSAPoll(pollfd, pollfdCount, timeoutMilliSecond);
    if(ret < 0) {
        throw ErrorHandler("Poll Fail");
    }

    return ret;
}
#else
#TODO
#endif

}   // namespace _network
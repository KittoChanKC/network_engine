#include "Core\Socket.h"
//---------------------------------------------------------------------------
//!	@file	Socket.cpp
//!	@brief	ネットワークソケットクラス
//---------------------------------------------------------------------------
namespace _network {
Socket::Socket()
{
}
Socket::~Socket()
{
}
void Socket::CreateTCP()
{
    Close();

    // 初期化
    WSADATA data;
    if(0 != WSAStartup(MAKEWORD(2, 2), &data)) {
        throw ErrorHandler("WSA StartUp Fail");
    }

    _socket = ::socket(AF_INET, SOCK_STREAM, 0);
    if(_socket == INVALID_SOCKET) {
        throw ErrorHandler("Create TCP Fail");
    }
}
void Socket::Close()
{
    if(_socket != INVALID_SOCKET) {
#ifdef _WIN32
        ::closesocket(_socket);
#endif
        // TODO: unix プラットフォーム
        //::close(_sock);
    }
}
void Socket::Bind(const SocketAddress& addr)
{
    int ret = ::bind(_socket, &addr._addr, sizeof(addr._addr));
    if(0 != ret) {
        throw ErrorHandler("Bind Fail");
    }

    printf_s("bind %u\n", addr.GetPort());
}
void Socket::Listen(s32 backLog)
{
    int ret = ::listen(_socket, backLog);

    if(ret != 0) {
        throw ErrorHandler("Listen Fail");
    }

    printf_s("Listen\n");
}
bool Socket::Accept(Socket& acceptedSocket)
{
    acceptedSocket.Close();

    auto c = ::accept(_socket, nullptr, nullptr);
    if(c == INVALID_SOCKET) {
        return false;
    }

    printf_s("accept\n");
    acceptedSocket._socket = c;

    return true;
}
void Socket::Connect(const SocketAddress& addr)
{
    int ret = ::connect(_socket, &addr._addr, sizeof(addr._addr));
    if(ret < 0) {
        throw ErrorHandler("Connect Fail");
    }
    printf_s("connecting\n");
}
//void Socket::ConnectIPv4(const char* hostName, u16 port)
//{
//    SocketAddress addr;
//    addr.SetIPv4(hostName, nullptr);
//}
int Socket::SendTo(const SocketAddress& addr, const char* data, size_t dataSize)
{
    if(dataSize > INT_MAX) {
        throw ErrorHandler("Send Data Size IS Too Big");
    }

    return ::sendto(_socket, data, (int)dataSize, 0, &addr._addr, sizeof(addr._addr));
}
int Socket::SendTo(const SocketAddress& addr, const char* data)
{
    return SendTo(addr, data, strlen(data));
}
int Socket::Send(const char* data, size_t dataSize)
{
    if(dataSize > INT_MAX) {
        throw ErrorHandler("Send Data Size IS Too Big");
    }

    return ::send(_socket, data, (int)dataSize, 0);
}
int Socket::Send(const std::vector<char>& data)
{
    return Send(data.data(), data.size());
}
int Socket::Send(const char* data)
{
    return Send(data, strlen(data));
}
int Socket::Send(const std::string& s)
{
    return Send(s.data(), s.size());
}
int Socket::Recv(std::vector<char>& buf, size_t bytesToRecv)
{
    buf.clear();

    if(bytesToRecv > INT_MAX) {
        throw ErrorHandler("Recv BytesToRecv is Too Big");
    }

    buf.resize(bytesToRecv);

    return ::recv(_socket, buf.data(), (int)bytesToRecv, 0);
}
int Socket::Recv(char* buf, size_t bytesToRecv)
{
    if(bytesToRecv > INT_MAX) {
        throw ErrorHandler("Recv BytesToRecv is Too Big");
    }
    //printf_s("recv%s\n", buf);
    return ::recv(_socket, buf, (int)bytesToRecv, 0);
}
bool Socket::IsVaild()
{
    return _socket != INVALID_SOCKET;
}
size_t Socket::AvailableBytesToRead()
{
#ifdef _WIN32
    u_long n = 0;
    if(0 != ::ioctlsocket(_socket, FIONREAD, &n)) {
        throw ErrorHandler("AvailableBytesToRead");
    }

    return static_cast<size_t>(n);
#endif   // _WIN32
}
SOCKET Socket::GetSocket()
{
    return _socket;
}
void Socket::SetNonBlocking(bool b)
{
#ifdef _WIN32
    u_long v = b ? 1 : 0;
    if(0 != ::ioctlsocket(_socket, FIONBIO, &v)) {
        //throw ErrorHandler("SetNonBlocking Faile");
        printf_s("no-bk fail");
    }
#else
# ERROR Not implemented
#endif   //  _WIN32
}
}   // namespace _network
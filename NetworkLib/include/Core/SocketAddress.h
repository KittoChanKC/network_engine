//---------------------------------------------------------------------------
//!	@file	SocketAddress.cpp
//!	@brief	ソケットのアドレス
//---------------------------------------------------------------------------
#pragma once

namespace _network {
class SocketAddress
{
public:
    SocketAddress();
    ~SocketAddress(){};

    void SetPortNum(u16 port);
    u16  GetPort() const;

    void SetIPv4(u8 a, u8 b, u8 c, u8 d);

    struct sockaddr _addr;
};
}   // namespace _network
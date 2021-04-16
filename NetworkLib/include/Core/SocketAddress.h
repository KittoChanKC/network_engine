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

    void SetPortNum(u16 port);   //! ポット
    u16  GetPort() const;        //! ポット取得

    void SetIPv4(u8 a, u8 b, u8 c, u8 d); //! IPv4

    struct sockaddr _addr;
};
}   // namespace _network
//---------------------------------------------------------------------------
//!	@file	SocketAddress.cpp
//!	@brief	ソケットのアドレス
//---------------------------------------------------------------------------
#include "Core/SocketAddress.h"
namespace _network {
SocketAddress::SocketAddress()
{
    memset(&_addr, 0, sizeof(_addr));
}
void SocketAddress::SetPortNum(u16 port)
{
    // htons = host to net
    *reinterpret_cast<u16*>(_addr.sa_data) = htons(port);
}
u16 SocketAddress::GetPort() const
{
    return ntohs(*reinterpret_cast<const u16*>(_addr.sa_data));
}
void SocketAddress::SetIPv4(u8 a, u8 b, u8 c, u8 d)
{
    _addr.sa_family = AF_INET;

    //先の２バイトはポットを使ってるので 2から始めます。
    _addr.sa_data[2] = a;
    _addr.sa_data[3] = b;
    _addr.sa_data[4] = c;
    _addr.sa_data[5] = d;
}

}   // namespace _network
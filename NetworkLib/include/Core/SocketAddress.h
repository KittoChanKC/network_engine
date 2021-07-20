//---------------------------------------------------------------------------
//!	@file	SocketAddress.cpp
//!	@brief	ソケットのアドレス
//---------------------------------------------------------------------------
#pragma once
#include "Utility/Common.h"

namespace _network {
class SocketAddress
{
public:
    SocketAddress();              //!< コンストラクタ
    ~SocketAddress() = default;   //!< デストラクタ

    void SetPortNum(u16 port);   //!< ポットを設定
    u16  GetPort() const;        //!< ポット取得

    void SetIPv4(u8 a, u8 b, u8 c, u8 d);   //!< IPv4を設定

    struct sockaddr _addr; //!< ソケアドレス
};
}   // namespace _network
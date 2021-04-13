//---------------------------------------------------------------------------
//!	@file	BaseConnection.h
//!	@brief	鯖につながるコンネクション
//---------------------------------------------------------------------------
#pragma once
#include "Core/Socket.h"
namespace _network {
class BaseConnection
{
    BaseConnection();
    ~BaseConnection();

    // コピー禁止/ムーブ禁止
    BaseConnection(const BaseConnection&) = delete;
    BaseConnection(BaseConnection&&)  = delete;
    BaseConnection& operator=(const BaseConnection&) = delete;
    BaseConnection& operator=(BaseConnection&&) = delete;

    // 列挙型
    enum class Status
    {
        None,
        Accepted,
        Rejected,
        Connecting,
        Connected,
        Closed
    };

    //---------------------------------------------------------------------------
    // 関数
    //---------------------------------------------------------------------------


};
}   // namespace _network
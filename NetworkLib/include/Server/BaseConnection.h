//---------------------------------------------------------------------------
//!	@file	BaseConnection.h
//!	@brief	�I�ɂȂ���R���l�N�V����
//---------------------------------------------------------------------------
#pragma once
#include "Core/Socket.h"
namespace _network {
class BaseConnection
{
    BaseConnection();
    ~BaseConnection();

    // �R�s�[�֎~/���[�u�֎~
    BaseConnection(const BaseConnection&) = delete;
    BaseConnection(BaseConnection&&)  = delete;
    BaseConnection& operator=(const BaseConnection&) = delete;
    BaseConnection& operator=(BaseConnection&&) = delete;

    // �񋓌^
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
    // �֐�
    //---------------------------------------------------------------------------


};
}   // namespace _network
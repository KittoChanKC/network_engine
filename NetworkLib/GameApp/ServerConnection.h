#pragma once
#include "Server/BaseConnection.h"

namespace _network {

class ServerConnection : public BaseConnection
{
public:
    ServerConnection();
    ~ServerConnection();

public:
    //---------------------------------------------------------------------------
    // �p��
    //---------------------------------------------------------------------------
    void OnConnected() override;
    void HandleCmd(const std::string& recvMsg) override;
};

}   // namespace _network
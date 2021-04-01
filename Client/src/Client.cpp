//---------------------------------------------------------------------------
//!	@file	Client.cpp
//!	@brief	クライアント側
//---------------------------------------------------------------------------
#include "../../Client/include/ClientBase.h"

bool g_quit = false;

class ClientImpl : public ClientBase
{
public:
    void Update() {

    }
};

void SingalHandler(int sig)
{
    printf("my_singal_handler %d\n", sig);
    switch(sig) {
        case SIGINT:
        case SIGTERM:
        {
            g_quit = true;
        } break;
    }
}

int main(int argv, const char* argc[])
{
    signal(SIGTERM, SingalHandler);
    signal(SIGINT, SingalHandler);

    if(argv < 2) {
        printf("client.exe <hostname>");
        return -1;
    }
    return 0;
}
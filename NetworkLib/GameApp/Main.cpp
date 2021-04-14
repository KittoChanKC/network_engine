//---------------------------------------------------------------------------
//!	@file	Main.cpp
//!	@brief	TestProgram, GameApp.h Game.cpp Copied from SimpleTalkCpp_Tutorial
//! @ref https://github.com/SimpleTalkCpp/SimpleTalkCpp_Tutorial
//---------------------------------------------------------------------------
//#include <sstream>
//
//#include "GameApp.h"
//#include "GameClient.h"
//#include "GameServer.h"
//#include "Core/Socket.h"
//
//#include "../Objects/Player.h"
//
//static const ImVec2 WINDOW_SIZE{ 1280.f, 720.f };
//
//class MyApp : public GameApp
//{
//public:
//    enum class Type
//    {
//        NONE,
//        SERVER,
//        CLIENT
//    };
//
//    enum class GameState
//    {
//        NONE,
//        START,
//        END
//    };
//
//    //TODO Multi
//    //Player p1;   //　自分
//    //Player p2;   //　他
//
//    //_network::BaseServer _server;
//    //_network::BaseClient _client;
//    GameServer _server;
//    GameClient _client;
//
//    //std::vector<Player> players;
//
//    Type _type = Type::NONE;
//
//    bool isConnected = false;
//
//   
//};
#include "MyApp.h"
int main()
{
    MyApp::Instance()->run();
    //app;
    //app.run();
    return 0;
}
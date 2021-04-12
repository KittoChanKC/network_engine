//---------------------------------------------------------------------------
//!	@file	Main.cpp
//!	@brief	TestProgram, GameApp.h Game.cpp Copied from SimpleTalkCpp_Tutorial
//! @ref https://github.com/SimpleTalkCpp/SimpleTalkCpp_Tutorial
//---------------------------------------------------------------------------
#include <sstream>

#include "GameApp.h"
#include "GameClient.h"
#include "GameServer.h"
#include "Core/Socket.h"

#include "../Objects/Player.h"

static const ImVec2 WINDOW_SIZE{ 1280.f, 720.f };

class MyApp : public GameApp
{
public:
    enum class Type
    {
        NONE,
        SERVER,
        CLIENT
    };

    enum class GameState
    {
        NONE,
        START,
        END
    };

    //TODO Multi
    //Player p1;   //　自分
    //Player p2;   //　他

    //_network::BaseServer _server;
    //_network::BaseClient _client;
    GameServer _server;
    GameClient _client;

    std::vector<Player> players;

    Type _type = Type::NONE;

    bool isConnected = false;

    void onUpdate(float deltaTime) override
    {
        if(_type == Type::SERVER && _server.gameStart) {
            auto* drawList = ImGui::GetBackgroundDrawList();
            _server.Draw(drawList);
        }

        if(!_client.IsStarted())
            return;

        ImVec2 dir{ 0, 0 };
        float  speed = 200;

        if(getInputKey(SDLK_w))
            dir.y -= 1;
        if(getInputKey(SDLK_s))
            dir.y += 1;
        if(getInputKey(SDLK_a))
            dir.x -= 1;
        if(getInputKey(SDLK_d))
            dir.x += 1;

        Player* _pPlayer = _type == Type::CLIENT ? _client.GetMyPlayer() : _server.GetMyPlayer();

        _pPlayer->MoveX(dir.x * deltaTime * speed);
        _pPlayer->MoveY(dir.y * deltaTime * speed);

        auto* drawList = ImGui::GetBackgroundDrawList();

        _client.Draw(drawList);
    }

    void onNetWork() override
    {
        if(_type == Type::SERVER) {
            _server.UpdatePollFD();
            return;
        }
        else if(_type == Type::CLIENT) {
            //Handle GameLogic
            //_client.SetSendBuffer("");
            //_client.SetSendBuffer(fmt::format("POS {} {} {}\n", p1.GetId(), p1.GetPos().x, p1.GetPos().y).c_str());
            if(_client.IsStarted())
                _client.SendPos();

            _client.UpdatePollFD();
            return;
        }
    }
    void onImGui() override
    {
        ImGui::Begin("Info", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);   // Create a window called "Hello, world!" and append into it.
        if(!_client.IsConnected()) {
            //ImGui::ShowDemoWindow();
            ImGui::SetWindowSize({ WINDOW_SIZE.x * 0.3f, WINDOW_SIZE.y });
            ImGui::SetWindowPos({ WINDOW_SIZE.x * 0.7f, 0.f });

            if(ImGui::Button("Server")) {
                _server.Listen();
                _type       = Type::SERVER;
                isConnected = true;
            }

            if(ImGui::Button("Client")) {
                _client.Connect();
                _type       = Type::CLIENT;
                isConnected = true;
            }
        }

        if(_type == Type::SERVER) {
            if(_server.GetConnectedClientNum() > 0 && ImGui ::Button("Start")) {
                //_server.SendToAll(fmt::format("Start"));
                _server.SendStartPkg();
                _server.gameStart = true;
            }
        }

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }
};

int main()
{
    MyApp app;
    app.run();
    return 0;
}
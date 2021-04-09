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

    //TODO Multi
    Player p1;   //　自分
    Player p2;   //　他

    //_network::BaseServer _server;
    //_network::BaseClient _client;
    GameServer _server;
    GameClient _client;

    Type type = Type::NONE;

    bool isConnected = false;

    void onUpdate(float deltaTime) override
    {
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

        p1.MoveX(dir.x * deltaTime * speed);
        p1.MoveY(dir.y * deltaTime * speed);

        auto* drawList = ImGui::GetBackgroundDrawList();

        drawList->AddTriangleFilled(ImVec2(p1.GetPos().x, p1.GetPos().y - 12),
                                    ImVec2(p1.GetPos().x - 12, p1.GetPos().y + 12),
                                    ImVec2(p1.GetPos().x + 12, p1.GetPos().y + 12),
                                    ImColor(255, 0, 0));

        if(p2.IsEnable()) {
            drawList->AddTriangleFilled(ImVec2(p2.GetPos().x, p2.GetPos().y - 12),
                                        ImVec2(p2.GetPos().x - 12, p2.GetPos().y + 12),
                                        ImVec2(p2.GetPos().x + 12, p2.GetPos().y + 12),
                                        ImColor(255, 0, 0));
        }
    }

    void onNetWork() override
    {
        if(type == Type::SERVER) {
            _server.UpdatePollFD();
            return;
        }
        else if(type == Type::CLIENT) {
            //Handle GameLogic
            _client.SetSendBuffer(fmt::format("POS {} {}\n", p1.GetPos().x, p1.GetPos().y).c_str());

            _client.UpdatePollFD();
            return;
        }

        //_network::Socket& socket = type == Type::SERVER ? _server.GetSocket() : _client.GetSocket();

        //if(!socket.IsVaild()) {
        //    p2.Disable();
        //    return;
        //};
        //p2.Enable();

        //// TODO: multiSocket
        ////
        //// send my player
        //{
        //    int ret = socket.Send(fmt::format("POS {} {}\n", p1.GetPos().x, p1.GetPos().y).c_str());
        //    if(ret <= 0) {
        //        socket.Close();
        //        isConnected = false;
        //        p2.Disable();
        //        return;
        //    }
        //}

        //// recv another player
        //{
        //    size_t n = socket.AvailableBytesToRead();
        //    if(n <= 0)
        //        return;

        //    std::vector<char> buf;
        //    int               ret = socket.Recv(buf, n);
        //    if(ret <= 0) {
        //        socket.Close();
        //        isConnected = false;
        //        return;
        //    }
        //    buf.push_back(0);
        //    HandleCmd(buf.data());
        //    printf("recv %d: %s\n", (int)n, buf.data());
        //}
    }
    void onImGui() override
    {
        ImGui::Begin("Info", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);   // Create a window called "Hello, world!" and append into it.
        if(!_client.IsConnected()) {
            //ImGui::ShowDemoWindow();
            ImGui::SetWindowSize({ WINDOW_SIZE.x * 0.3f, WINDOW_SIZE.y });
            ImGui::SetWindowPos({ WINDOW_SIZE.x * 0.7f, 0.f });

            if(ImGui::Button("Server")) {
                _server.Run();
                type        = Type::SERVER;
                isConnected = true;
            }

            if(ImGui::Button("Client")) {
                _client.Run();
                type        = Type::CLIENT;
                isConnected = true;
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
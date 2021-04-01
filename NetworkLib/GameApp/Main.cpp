//---------------------------------------------------------------------------
//!	@file	Main.cpp
//!	@brief	TestProgram, GameApp.h Game.cpp Copied from SimpleTalkCpp_Tutorial
//! @ref https://github.com/SimpleTalkCpp/SimpleTalkCpp_Tutorial
//---------------------------------------------------------------------------
#include "GameApp.h"
#include "Core/Socket.h"
#include "Server/Server.h"
#include "Client/Client.h"
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

    ImVec2 playerPos{ 400, 300 };

    _network::Server _server;
    _network::Client _client;

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

        playerPos.x += dir.x * deltaTime * speed;
        playerPos.y += dir.y * deltaTime * speed;

        //		auto* drawList = ImGui::GetWindowDrawList();
        //		auto* drawList = ImGui::GetForegroundDrawList();
        auto* drawList = ImGui::GetBackgroundDrawList();

        drawList->AddTriangleFilled(ImVec2(playerPos.x, playerPos.y - 12),
                                    ImVec2(playerPos.x - 12, playerPos.y + 12),
                                    ImVec2(playerPos.x + 12, playerPos.y + 12),
                                    ImColor(255, 0, 0));
    }

    void onNetWork() override
    {
        _network::Socket& socket = type == Type::SERVER ? _server.GetSocket() : _client.GetSocket();
      
        if(!socket.IsVaild()) {
            return;
        };

        // send my player
        {
            int ret = socket.Send(fmt::format("Test {}\n").c_str());
            if(ret <= 0) {
                socket.Close();
                isConnected = false;
            }
        }

        {
            // recv another player
            size_t n = socket.AvailableBytesToRead();
            if(n <= 0)
                return;

            std::vector<char> buf;
            int               ret = socket.Recv(buf, n);
            if(ret <= 0) {
                socket.Close();
                isConnected = false;
            }
            buf.push_back(0);
            printf("recv %d: %s\n", (int)n, buf.data());
        }
    }
    void onImGui() override
    {
        ImGui::Begin("Info", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);   // Create a window called "Hello, world!" and append into it.
        if(!isConnected) {
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

    void onEvent(SDL_Event& ev) override{
        /*
		switch (ev.type) 
		{
			case SDL_KEYDOWN: {
				auto key = ev.key.keysym.sym;
				switch (key) {
					case SDLK_w: playerPos.y -= 10; break;
					case SDLK_a: playerPos.x -= 10; break;
					case SDLK_s: playerPos.y += 10; break;
					case SDLK_d: playerPos.x += 10; break;
				}
			} break;
		}
		*/
    };
};

int main()
{
    MyApp app;
    app.run();
    return 0;
}
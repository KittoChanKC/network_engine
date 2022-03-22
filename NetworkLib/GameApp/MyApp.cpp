#include "MyApp.h"

void MyApp::onUpdate(float deltaTime)
{
    if(_type == Type::SERVER && _server.IsStarted()) {
        auto* drawList = ImGui::GetBackgroundDrawList();

        int i = 0;
        for(auto player : MyApp::Instance()->_players) {
            ImColor color = (i % 2 == 0) ? ImColor(255, 0, 0) : ImColor(255, 255, 0);
            drawList->AddTriangleFilled(ImVec2(player.GetPos().x, player.GetPos().y - 12),
                                        ImVec2(player.GetPos().x - 12, player.GetPos().y + 12),
                                        ImVec2(player.GetPos().x + 12, player.GetPos().y + 12),
                                        color);
            i++;
        }
        return;
    }

    if(!_isStarted)
        return;

    ImVec2 dir{ 0, 0 };
    float  speed = 200;

    if(ImGui::IsKeyDown(ImGuiKey_W))
        dir.y -= 1;
    if(ImGui::IsKeyDown(ImGuiKey_S))
        dir.y += 1;
    if(ImGui::IsKeyDown(ImGuiKey_A))
        dir.x -= 1;
    if(ImGui::IsKeyDown(ImGuiKey_D))
        dir.x += 1;

    _pPlayer->MoveX(dir.x * deltaTime * speed);
    _pPlayer->MoveY(dir.y * deltaTime * speed);

    auto* drawList = ImGui::GetBackgroundDrawList();

    int i = 0;
    for(auto player : _players) {
        ImColor color = (i % 2 == 0) ? ImColor(255, 0, 0) : ImColor(255, 255, 0);
        drawList->AddTriangleFilled(ImVec2(player.GetPos().x, player.GetPos().y - 12),
                                    ImVec2(player.GetPos().x - 12, player.GetPos().y + 12),
                                    ImVec2(player.GetPos().x + 12, player.GetPos().y + 12),
                                    color);
        i++;
    }
}
void MyApp::onNetWork()
{
    if(_type == Type::SERVER) {
        _server.UpdatePollFD();
        return;
    }
    else if(_type == Type::CLIENT) {
        //Handle GameLogic
        //_client.SetSendBuffer("");
        //_client.SetSendBuffer(fmt::format("POS {} {} {}\n", p1.GetId(), p1.GetPos().x, p1.GetPos().y).c_str());
        if(_isStarted)
            _client.SendPos();

        _client.UpdatePollFD();
        return;
    }
}
void MyApp::onImGui()
{
    ImGui::Begin("Info", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);   // Create a window called "Hello, world!" and append into it.
    if(!_client.IsConnected()) {
        //ImGui::ShowDemoWindow();
        //if(_type == Type::SERVER) {
        //    ImGui::SetWindowSize({ WINDOW_SIZE.x * 0.4f, WINDOW_SIZE.y });
        //    ImGui::SetWindowPos({ 0.f, 0.f });
        //}
        //else {
        //    ImGui::SetWindowSize({ WINDOW_SIZE.x * 0.4f, WINDOW_SIZE.y });
        //    ImGui::SetWindowPos({ WINDOW_SIZE.x * 0.7f, 0.f });
        //}
        ImGui::SetWindowSize({ WINDOW_SIZE.x * 0.4f, WINDOW_SIZE.y });
        ImGui::SetWindowPos({ WINDOW_SIZE.x * 0.7f, 0.f });

        if(ImGui::Button("Server")) {
            _server.Listen();
            _type        = Type::SERVER;
            _isConnected = true;
            SDL_SetWindowTitle(app::GetWindow(), "NetworkEngine Test (Server)");
        }

        if(ImGui::Button("Client")) {
            _client.Connect();
            _type        = Type::CLIENT;
            _isConnected = true;
            SDL_SetWindowTitle(app::GetWindow(), "NetworkEngine Test (Client)");
        }
    }

    if(_type == Type::SERVER) {
        ImGui::Text("ConnectedNum: %d", _server.GetConnectedNum());
        if(_server.IsStarted()) {
            ImGui::Text("Status: Observe Mode");
        }
        if(_server.GetConnectedNum() > 0 && ImGui ::Button("Start")) {
            //_server.SendToAll(fmt::format("Start"));
            _server.SendStartPkg();
            _server.SetGameStart();
        }
    }

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}

MyApp* MyApp::Instance()
{
    static MyApp instance;   // gpu::Render‚ÌƒVƒ“ƒOƒ‹ƒgƒ“ŽÀ‘Ì
    return &instance;
}

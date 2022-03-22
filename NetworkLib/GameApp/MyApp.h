#pragma once
#include <sstream>
#include <vector>

#include "GameApp.h"
#include "GameClient.h"
#include "GameServer.h"
#include "Core/Socket.h"
#include "../Objects/Player.h"
static const ImVec2 WINDOW_SIZE{ 640.f, 360.f };
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

    GameServer _server;
    GameClient _client;

    std::vector<Player> _players;
    Player*             _pPlayer = nullptr;

    Type _type = Type::NONE;

    bool _isConnected = false;
    bool _isStarted   = false;

    void onUpdate(float deltaTime) override;
    void onNetWork() override;
    void onImGui() override;

    //! ŽÀ‘Ì‚ðŽæ“¾
    static MyApp* Instance();
};
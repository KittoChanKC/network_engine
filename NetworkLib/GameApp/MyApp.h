#include <sstream>
#include <vector>

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

    GameServer _server;
    GameClient _client;

    std::vector<Player> players;
    Player*             _pPlayer;

    Type _type = Type::NONE;

    bool isConnected = false;

    void onUpdate(float deltaTime) override;
    void onNetWork() override;
    void onImGui() override;
};
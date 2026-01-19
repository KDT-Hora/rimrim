#include "IScene.h"
#include "../../Game/GameSession.h"

IScene::IScene(game::GameSession* session)
{
	gameSession = session;
}

IScene::~IScene() = default;
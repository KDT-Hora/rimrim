#include "SceneManager.h"
#include <cassert>
#include "../../Game/GameSession.h"

SceneManager::SceneManager() = default;
SceneManager::~SceneManager() = default;

void SceneManager::SetGameSession(game::GameSession* session)
{
	this->gameSession = session;
}

void SceneManager::Init()
{
	//	シーン交換処理
	if (nextSceneFactory)
	{
		currentScene = nullptr;
		currentScene = nextSceneFactory();
		nextSceneFactory = nullptr;

		//	GameSessionにシーン変更を通知
		gameSession->SceneChanged();
	}
}

void SceneManager::Update()
{
	assert(currentScene && "[errer] This Scene Is None");
	
	currentScene->Update();

	//	シーン交換メソッド
	if (nextSceneFactory)
	{
		currentScene = nullptr;
		currentScene = nextSceneFactory();
		nextSceneFactory = nullptr;

		//	GameSessionにシーン変更を通知
		gameSession->SceneChanged();
	}

}

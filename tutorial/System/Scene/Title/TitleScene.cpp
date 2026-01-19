#include "TitleScene.h"
#include <iostream>
#include "../../../Game/GameSession.h"
#include "../../../ECS/QueueManager.h"

TitleScene::TitleScene(game::GameSession* session)
	:IScene(session)
{
	//	シーンの生成ログ
	std::cout << "TitleScene Create" << std::endl;

	//	画面上にエンティティ生成
	auto cmd = []()
		{

		};
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{

}

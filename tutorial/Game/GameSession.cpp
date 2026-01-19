#include "GameSession.h"
#include <iostream>

//	システムのコンテキスト
#include "../Context/SystemContext.h"

//	ECS
#include "../ECS/ECSManager.h"
#include "../ECS/ECSRegister.h"

//	マップ関係
#include "Map/MapManager.h"
#include "Map/TerrainRenderSystem.h"

game::GameSession::GameSession()
{
	//	マップの初期化
	mapManager = std::make_unique<map::MapManager>(50, 50);
	terrainRenderer = std::make_unique<map::TerrainRenderSystem>();

	//	テスト用　特定タイルの地形を変更
	mapManager->SetTerrain(5, 5, map::TerrainType::Stone);
	mapManager->SetTerrain(6, 5, map::TerrainType::Grass);
	mapManager->SetTerrain(7, 5, map::TerrainType::Water);

	std::cout << "GameSession Create" << std::endl;
}

//	デストラクタでクラスの完全図が必要なため、CPPのほうにデストラクタが来るように定義
//	デフォルトで定義しておけば、勝手に生成される
game::GameSession::~GameSession() = default;

//	コンテキストの引き渡し
//	ECSの初期化
void game::GameSession::Init(engine::SystemContext& sysContext)
{
	systemContext = &sysContext;
	this->ecsInit();

	std::cout << "GameSession Init Complete" << std::endl;
}

//	ゲーム更新処理
void game::GameSession::Update()
{
	//	ウィンドウ
	sf::RenderWindow& window = systemContext->window;

	//	地形描画システム
	this->terrainRenderer->Render(window,*mapManager);

	//	ECS更新
	this->ecsManager->Update(systemContext->fixedDeltaTime);

}

//	エンティティをマップに追加
void game::GameSession::DebugAddEntityToMap(ECS::EntityID entity, int x, int y)
{
	mapManager->RegisterEntity(entity, sf::Vector2i(x,y));
}

//	シーン切り替わり時のリセット
void game::GameSession::SceneChanged()
{
	ecsManager.reset();
	//	ECSの再初期化
	this->ecsInit();

	std::cout << "GameSession Scene Changed and ECS ReInit" << std::endl;
}

//	ECSの初期化
void game::GameSession::ecsInit()
{
	//	ECSManager作成
	ecsManager = std::make_unique<ECS::ECSManager>(*systemContext);
	//	システムとコンポーネントの登録
	ECS::ECSRegister().ECSInit(*ecsManager);

	std::cout << "ECS Init Complete" << std::endl;
}

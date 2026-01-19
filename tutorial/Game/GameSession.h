#pragma once

#include <memory>
#include "../ECS/ECSConfig.h"

namespace ECS
{
	class ECSManager;
	class DebugAPI;
}

namespace map
{
	class MapManager;
	class TerrainRenderSystem;
}

namespace engine
{
	struct SystemContext;
}

namespace game
{

	class GameSession
	{
	private:

		engine::SystemContext* systemContext = nullptr;
		//	ECS
		std::unique_ptr<ECS::ECSManager> ecsManager;
		//	マップ
		std::unique_ptr<map::MapManager> mapManager;
		std::unique_ptr<map::TerrainRenderSystem> terrainRenderer;


	public:

		GameSession();
		virtual ~GameSession();

		//	初期化
		void Init(engine::SystemContext& sysContext);
		//	更新
		void Update();
		//	マップにエンティティの登録
		void DebugAddEntityToMap(ECS::EntityID entity,int x,int y);

		//	シーン切り替わり時のリセット
		void SceneChanged();

	private:

		//	ECSのイニシャライズ
		void ecsInit();

	};

}



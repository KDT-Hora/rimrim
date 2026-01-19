#include "ECSRegister.h"
#include <iostream>

//	コンポーネント
#include "Component/Components.h"

//	システム
#include "Systems/RenderSystem.h"
#include "Systems/PlayerMoveSystem.h"
#include "Systems/EntityRenderSystem.h"


void ECS::ECSRegister::ECSInit(ECSManager& ecsMG)
{
	//	コンポーネントの初期化
	componentInit(ecsMG);
	//	システムの登録
	systemInit(ecsMG);
}

void ECS::ECSRegister::componentInit(ECSManager& ecs)
{
	ecs.RegisterComponent<TransformComponent>();
	ecs.RegisterComponent<CircleShapeComponent>();
	ecs.RegisterComponent<MoveValueComponent>();
	ecs.RegisterComponent<GridPositionComponent>();
	ecs.RegisterComponent<DebugRendererComponent>();

	std::cout << "ECS Components Registered" << std::endl;
}

void ECS::ECSRegister::systemInit(ECSManager& ecs)
{
	//	レンダーシステム
	auto renderSys = ecs.RegisterSystem<RenderSystem>();
	ecs.SetSystemSignature<RenderSystem>(renderSys->Init());

	//	ムーブシステム
	auto moveSys = ecs.RegisterSystem<PlayerMoveSystem>();
	ecs.SetSystemSignature<PlayerMoveSystem>(moveSys->Init());

	//	デバッグ用Entity描画システム
	auto debugRenderSys = ecs.RegisterSystem<EntityRenderSystem>();
	ecs.SetSystemSignature<EntityRenderSystem>(debugRenderSys->Init());

	std::cout << "ECS Systems Registered" << std::endl;
}

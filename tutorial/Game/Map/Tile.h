#pragma once
#include <vector>

#include "../../ECS/ECSConfig.h"

namespace map
{
	//	タイルタイプ
	enum class TerrainType
	{
		Dirt,
		Stone,
		Grass,
		Water,
	};

	//	タイル
	struct Tile
	{
		TerrainType terrain = TerrainType::Dirt;

		//	タイルに存在するエンティティ
		//	１タイルに複数存在することができる設計
		std::vector<ECS::EntityID> entitiesOnTile;

		//	後に追加
		//	今は変数だけ
		//	機能追加はまた今度
		float temperature;
		bool hasRoof;
		int roomID;

	};

}
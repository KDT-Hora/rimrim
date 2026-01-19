#include "MapManager.h"
#include <algorithm>

map::MapManager::MapManager(int width, int height)
	:width(width),height(height)
{
	tiles.resize(width * height);
}

map::Tile* map::MapManager::GetTile(int x, int y)
{
	if (!IsInBounds(x, y))return nullptr;
	return &tiles[y * width + x];
}

bool map::MapManager::IsInBounds(int x, int y) const
{
	return (x >= 0 && x < width && y >= 0 && y < height);
}

void map::MapManager::UpdateEntityPos(ECS::EntityID entity, sf::Vector2i oldPos, sf::Vector2i nextPos)
{
	//	移動していない時はそのまま返す
	//	そもそも移動してないなら呼ぶなよ
	if (oldPos == nextPos) { return; }

	//	削除を行ってもいいのは、何番を持っているかだけで
	//	実体を持っているわけではないのでモーマンタイ
	UnregisterEntity(entity, oldPos);
	RegisterEntity(entity, nextPos);
}

void map::MapManager::RegisterEntity(ECS::EntityID entity, sf::Vector2i pos)
{
	Tile* t = GetTile(pos);
	if (t)
	{
		t->entitiesOnTile.push_back(entity);
	}
}

void map::MapManager::UnregisterEntity(ECS::EntityID entity, sf::Vector2i pos)
{
	Tile* t = GetTile(pos);
	if (t)
	{
		auto& list = t->entitiesOnTile;
		//	コレクションから削除
		list.erase(std::remove(list.begin(), list.end(), entity), list.end());
	}
}

void map::MapManager::SetTerrain(int x, int y, TerrainType type)
{
	Tile* t = GetTile(x, y);
	if (t)
	{
		t->terrain = type;
	}
}

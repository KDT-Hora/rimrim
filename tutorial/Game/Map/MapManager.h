#pragma once

#include <vector>
#include <iostream>
#include "Tile.h"
#include <SFML/System/Vector2.hpp>

namespace map
{

	class MapManager
	{
	private:

		std::vector<Tile> tiles;

		int width;
		int height;


	public:

		MapManager(int width, int height);
		~MapManager() = default;

		Tile* GetTile(int x, int y);
		Tile* GetTile(sf::Vector2i pos) 
		{ 
			return GetTile(pos.x, pos.y); 
		}

		int GetWidth()const 
		{ 
			return width;
		}
		int Getheight()const 
		{ 
			return height; 
		}

		//	マップ内か確認
		bool IsInBounds(int x, int y)const;

		//	Entityが移動したとき古い座標から新しい座標へ
		void UpdateEntityPos(ECS::EntityID entity, sf::Vector2i oldPos, sf::Vector2i nextPos);

		//	Entityの生成時登録
		void RegisterEntity(ECS::EntityID entity, sf::Vector2i pos);
		//	Entityの削除時解除
		void UnregisterEntity(ECS::EntityID entity, sf::Vector2i pos);

		//	地形操作
		void SetTerrain(int x, int y, TerrainType type);

	};

}

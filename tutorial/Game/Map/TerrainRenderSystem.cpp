#include "TerrainRenderSystem.h"

#include "MapManager.h"
#include "../Constants.h"


void map::TerrainRenderSystem::Render(sf::RenderWindow& window, map::MapManager& map)
{
	const int width = map.GetWidth();
	const int height = map.Getheight();

	//	１タイル分の図形
	sf::RectangleShape tileShape(sf::Vector2f{ TILE_SIZE,TILE_SIZE });

	//	グリッド線
	tileShape.setOutlineThickness(1.0f);
	tileShape.setOutlineColor(sf::Color(50, 50, 50));

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Tile* tile = map.GetTile(x, y);
			if (tile == nullptr) 
			{
				continue;
			}

			switch (tile->terrain)
			{
			case TerrainType::Dirt:
				tileShape.setFillColor(sf::Color(139, 69, 19));		// 茶色
				break;
			case TerrainType::Stone:
				tileShape.setFillColor(sf::Color(128, 128, 128));	// グレー
				break;
			case TerrainType::Grass:
				tileShape.setFillColor(sf::Color(34, 139, 34));		// 緑
				break;
			case TerrainType::Water:
				tileShape.setFillColor(sf::Color(0, 0, 255));		// 青
				break;
			default:
				tileShape.setFillColor(sf::Color::Magenta); // エラー色は派手に
				break;
			}

			//	描画位置更新
			sf::Vector2f pos(x * TILE_SIZE, y * TILE_SIZE);
			tileShape.setPosition(pos);

			//	描画
			window.draw(tileShape);

		}
	}
}
/*

いったんこの描画方法でおｋ（イミディエイトモード）
マップが大きくなったら、この方法だと重たいので、別方法に差し替え



*/
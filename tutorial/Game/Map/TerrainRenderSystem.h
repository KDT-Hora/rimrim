#pragma once
#include <SFML/Graphics.hpp>

namespace map
{
	class MapManager;

	//	地形描画システム
	//	マップマネージャーに
	class TerrainRenderSystem
	{
	public:

		void Render(sf::RenderWindow& window, map::MapManager& map);

	};

}
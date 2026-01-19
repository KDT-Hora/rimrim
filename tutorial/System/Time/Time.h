#pragma once

#include "SFML/System/Time.hpp"

//	時間管理クラス
namespace engine
{

	class Time
	{
		sf::Time cureentTime;
		sf::Time deltaTime;

	public:

		//	コンストラクタ
		Time();

		//	初期化
		void Init();

		//	時間経過メソッド
		void Update();

		//	デルタタイム取得
		sf::Time GetDeltaTime();


	};

}
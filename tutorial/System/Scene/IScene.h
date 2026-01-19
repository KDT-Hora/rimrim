#pragma once

namespace game
{
	class GameSession;
}

class IScene
{
protected:

	//	ゲーム
	game::GameSession* gameSession;
	//	ポインタをシーンからアクセスする
	//　ほんとはインターフェース切ってアクセスしたほうがいいとは思っているけど許して

public:

	IScene(game::GameSession* session);
	//	デストラクタ
	virtual ~IScene() = 0;
	//	更新メソッド
	virtual void Update() = 0;
};
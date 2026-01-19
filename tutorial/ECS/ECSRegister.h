#pragma once

#include "ECSConfig.h"

namespace ECS
{

	class ECSManager;

	//	ECSの設定クラス
	class ECSRegister
	{
	public:

		static void ECSInit(ECSManager& ecsMG);

	private:

		//	コンポーネントの登録
		static void componentInit(ECSManager& ecsMG);
		//	システムの登録
		static void systemInit(ECSManager& ecsMG);

	};
}

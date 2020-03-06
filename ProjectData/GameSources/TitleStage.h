#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------

	class TitleStage : public Stage {
		//ビューの作成
		void CreateViewLight();
	public:

		//構築と破棄
		TitleStage() :Stage() {}
		virtual ~TitleStage() {}

		//初期化
		virtual void OnCreate()override;
	};
}
//end basecross

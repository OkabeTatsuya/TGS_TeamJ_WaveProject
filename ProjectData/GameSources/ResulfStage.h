/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class ResulfStage : public Stage {
		//ビューの作成
		void CreateViewLight();

	public:
		//構築と破棄
		ResulfStage() :Stage() {}
		virtual ~ResulfStage() {}
		//初期化
		virtual void OnCreate()override;
	};


}
//end basecross


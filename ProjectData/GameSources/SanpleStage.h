/*!
@file SanpleStage.h
@brief オブジェクト紹介ステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------

	class SanpleStage : public Stage {
		//BGM
		shared_ptr<SoundItem>m_BGM;

		//ビューの作成
		void CreateViewLight();
	public:

		//構築と破棄
		SanpleStage() :Stage() {}
		virtual ~SanpleStage() {}

		//初期化
		virtual void OnCreate()override;

		//別のステージに移った時など、このシーンが破棄される時に呼ばれる関数
		virtual void OnDestroy()override;

		virtual void OnUpdate()override;

		//UIを作る関数
		void CreateUI();

		//BGMを再生させる関数
		void PlayBGM(wstring soundName, float vol);

		//シーンをロードする関数
		void LoadStage(wstring stageName);
	};
}
//end basecross

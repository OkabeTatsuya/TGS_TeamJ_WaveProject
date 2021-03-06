#pragma once
#include "stdafx.h"

//コントローラー
namespace basecross {
	//--------------------------------------------------------------------------------------
	//	タイトルステージクラス
	//--------------------------------------------------------------------------------------

	class TitleStage : public Stage {
		//BGM
		shared_ptr<SoundItem>m_BGM;
		//SE
		shared_ptr<SoundItem>m_SE;
		//時間
		float m_time;
		//Aボタン
		bool m_isPushA;


		//ビューの作成
		void CreateViewLight();
	public:

		//構築と破棄
		TitleStage() :Stage() {}
		virtual ~TitleStage() {}

		//初期化
		virtual void OnCreate()override;

		virtual void OnDestroy()override;

		virtual void OnUpdate()override;
	};
}
//end basecross

#pragma once
#include "stdafx.h"

//コントローラー
namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------

	class CopywriterStage : public Stage {
		//フェードインするUI
		shared_ptr<UIBase> m_fadeInUI;
		//SE
		shared_ptr<SoundItem>m_SE;
		//ロードする時間
		float m_loadTimeCount;
		//タイトルステージに移る時間
		float m_maxLoadTime;
		//次のステージをロードするフラグ
		bool m_isLoadStage;


		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		CopywriterStage() :Stage() {
			m_isLoadStage = false;
			m_maxLoadTime = 2.0f;
			m_loadTimeCount = 0.0f;
		}

		virtual ~CopywriterStage() {}

		//初期化
		virtual void OnCreate()override;

		virtual void OnDestroy()override;

		virtual void OnUpdate()override;

		//UIを作成
		void CreateUI();
		//ステージのロード
		void LoadTitleStage();
		//コントローラーの入力受付
		void Hundler();
		//Aボタンが押された時
		void PushAButton();
	};
}
//end basecross

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
	class SelectStage : public Stage {
		//ビューの作成
		void CreateViewLight();

		//ステージが選ばれた時
		bool m_isSelectStage;


		bool m_isChengeStage;

		int m_stageNum;

		float m_stickDelta;
		float m_stickTime;


		Vec2 m_pos[3];

		wstring m_stageName;
		vector<wstring> m_stageImageName;

		shared_ptr<SoundItem> m_SE;
		shared_ptr<SoundItem> m_BGM;

		shared_ptr<ImageUI> m_stageImageUI;

	public:
		//構築と破棄
		SelectStage() :Stage() {
			m_stageName = L"ToGameStage";
			m_stageNum = 0;

			m_stickDelta = 0.5f;
			m_stickTime = 0.0f;
			m_stageImageName = { L"cloud2.png",
				L"Gaol_Pattern2.png", L"Seagull.png", L"Island.png"};
		}
		virtual ~SelectStage() {}
		//初期化
		virtual void OnCreate()override;

		virtual void OnUpdate()override;

		virtual void OnDestroy()override;

		//時間を決めて、シーンを遷移する
		void Sceneloader();

		//コントローラーを押す
		void Handler();

		int LoadBinaryData();

		int CreateBinaryData();

		//UIを作る関数
		void CreateUI();

		void PushA();

		void StickL();

		void ChengeStegeNum();

		//BGMを再生させる関数
		void PlayBGM(wstring soundName, float vol);

		//SEを再生させる関数
		void PlaySE(wstring soundName, float vol);

	};
}
//end basecross


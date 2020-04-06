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
	class GameStage : public Stage {
		//ビューの作成
		void CreateViewLight();

		//BGMの再生
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<SoundItem> m_SE;

		bool m_isPause;

		//ゲームを始める前の硬直時間
		float m_startTimeCount;
		float m_maxStartTime;
		bool m_isFrastStop;

		//ゲームをクリアした時に使う
		float m_loadStageTimeCount;
		float m_maxLoadStageTime;
		bool m_isFadeIn;

	public:
		//構築と破棄
		GameStage() :Stage()
		{
			m_isPause = false;
			m_startTimeCount = 0.0f;
			m_maxStartTime = 3.0f;
			m_isFrastStop = true;

			m_startTimeCount = 0.0f;
			m_maxStartTime = 3.0f;
			m_isFrastStop = false;

		}

		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;

		virtual void OnUpdate()override;

		//消除時
		virtual void OnDestroy()override;

		void LoadResultStage();

		int SaveGameData();

		int ReadGameData();

		void FrastTimeCount();

		void GameClear();

	};


}
//end basecross


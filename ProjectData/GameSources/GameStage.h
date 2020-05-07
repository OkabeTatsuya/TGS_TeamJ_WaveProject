/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"
#include "UIBase.h"
#include "AnimationUI.h"

namespace basecross {
	struct Bit_SpawnFlag
	{
		const unsigned int wave = (1 << 0);
		const unsigned int item = (1 << 1);
	};


	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//ビューの作成
		void CreateViewLight();

		Bit_SpawnFlag m_spawnBitFlag;

		//BGMの再生
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<SoundItem> m_SE;

		vector<shared_ptr<AnimationUI>> m_startUI;
		shared_ptr<AnimationUI> m_goalUI;
		
		vector<int> m_gameClearScore;

		Vec3 m_textScale;

		//ゲームを停止させるフラグ
		bool m_isPause;

		//ゲームを始める前の硬直時間
		float m_startTimeCount;
		float m_maxStartTime;
		bool m_isFrastStop;

		//ゲームをクリアした時に使う
		float m_loadStageTimeCount;
		float m_maxLoadStageTime;
		float m_gameClearSpeed;
		bool m_isLoadStage;
		bool m_isCreateGoalUI;

		//スポナーの生成終了フラグ
		unsigned int m_spawnFlag;

	public:
		//構築と破棄
		GameStage() :Stage()
		{
			m_textScale = Vec3(400.0f, 200.0f, 1.0f);

			m_isPause = false;
			m_startTimeCount = 0.0f;
			m_maxStartTime = 3.0f;
			m_isFrastStop = true;

			m_startTimeCount = 0.0f;
			m_maxStartTime = 3.0f;


			m_maxLoadStageTime = 3.0f;

			m_gameClearSpeed = 0.2f;
			m_spawnFlag = 0;

			m_gameClearScore = { 100,200,300,400 };
		}

		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;

		virtual void OnUpdate()override;

		//消除時
		virtual void OnDestroy()override;

		//ゲッター、セッター

		void CreateAnimUI();

		void CreateGoalUI();

		void CreateGenerator();

		void LoadResultStage();

		int SaveGameData();

		int ReadGameData();

		void FrastTimeCount();

		void GameClear();
		
		//ビットフラグを上げる
		void TrueSpawnFlag(unsigned int bit_flag);

		//ビットフラグを下げる
		void FalseSpawnFlag(unsigned int bit_flag);

		//フラグの状態を確認する
		bool ConfirmSpawnFlag(unsigned int bit_flag);

	};


}
//end basecross


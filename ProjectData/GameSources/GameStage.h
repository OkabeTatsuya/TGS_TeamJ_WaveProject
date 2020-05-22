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

	struct EffectNames 
	{
		vector<wstring> EffectName{
			L"Good2.efk",
			L"MoveOn.efk"
		};
	};

	enum EN_EffectName {
		en_GoodEffect,
		en_PerfectEffect,
		en_MoveEffect
	};

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//ビューの作成
		void CreateViewLight();

		Bit_SpawnFlag m_spawnBitFlag;
		EffectNames m_effectNames;

		//BGMの再生
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<SoundItem> m_SE;

		//アニメーションUI
		vector<shared_ptr<AnimationUI>> m_startUI;
		shared_ptr<AnimationUI> m_goalUI;
		
		//エフェクトインターフェイス
		shared_ptr<EfkInterface> m_efkInterface;
		vector<shared_ptr<EfkEffect>> m_efkEffect;

		vector<shared_ptr<EfkPlay>> m_efkPlay;

		shared_ptr<GameObject> m_playerObj;

		vector<int> m_gameClearScore;

		Vec3 m_textScale;	

		//ゲームを停止させるフラグ
		bool m_isPause;

		//スペシャルジャンプ時のゲームスピード減少処理で使用
		float m_saveGameSpeed;
		float m_SpecialJumpSpeed;
		float m_specialJumpTimer;
		int m_specialJumpCount;
		int m_maxSpecialJumpCount;

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
			m_textScale = Vec3(512.0f, 256.0f, 1.0f);

			m_isPause = false;
			m_startTimeCount = 0.0f;
			m_maxStartTime = 3.0f;
			m_isFrastStop = true;

			m_startTimeCount = 0.0f;
			m_maxStartTime = 3.0f;

			m_SpecialJumpSpeed = 1.0f;
			m_specialJumpTimer = 0.0f;
			m_specialJumpCount = 0;
			m_maxSpecialJumpCount = 3;

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

		//エフェクト、テキスト描画
		virtual void OnDraw()override;

		//ゲッター、セッター
		shared_ptr<EfkInterface> GetEfkInterface()const { return m_efkInterface; }

		vector<shared_ptr<EfkEffect>> GetEfkEffect()const { return m_efkEffect; }

		vector<shared_ptr<EfkPlay>> GetEfkPlay()const { return m_efkPlay; }

		void SetEfkPlay(vector<shared_ptr<EfkPlay>> set, int efkNum) { m_efkPlay = set; }

		//アニメーションUIを作成
		void CreateAnimUI();

		//ゴール時のUIを作成
		void CreateGoalUI();

		//オブジェクトを生成するジェネレーターを作成
		void CreateGenerator();

		//エフェクトを作成
		void CreateEfkEffect();

		//リザルトステージに移動
		void LoadResultStage();

		//ゲームデータを保存
		int SaveGameData();

		//ゲームデータの読み込み
		int ReadGameData();

		//最初のゲーム停止時のカウント
		void FrastTimeCount();

		//ゲームクリア時の処理
		void GameClear();
		
		//スペシャルジャンプに入った時
		void SpecialJumpController();

		//ビットフラグを上げる
		void TrueSpawnFlag(unsigned int bit_flag);

		//ビットフラグを下げる
		void FalseSpawnFlag(unsigned int bit_flag);

		//フラグの状態を確認する
		bool ConfirmSpawnFlag(unsigned int bit_flag);

	};


}
//end basecross


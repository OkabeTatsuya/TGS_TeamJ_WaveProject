/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"
#include "UIBase.h"
#include "ObjectBase.h"
#include "SpawnerBase.h"
#include "MoveSpriteBase.h"

#include "AnimationUI.h"
#include "ScoreUI.h"
#include "ScoreUIPanel.h"
#include "Wave.h"
#include "WaveSpawner.h"
#include "ImageUI.h"
#include "CutInUI.h"

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

	enum EN_MapIcon {
		en_var,
		en_goal,
		en_player
	};

	enum EN_SE {
		en_SpecialTimeSE,
		en_GameClearSE,
		en_GameOverSE,
		en_GameClearVoice,
		en_GameOverVoice,
		en_SpecialTImeVoice1,
	};

	enum EN_SoundTypeSE {
		en_SystemSE,
		en_VoiceSE
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
		vector<shared_ptr<SoundItem>> m_SE;
		vector<wstring> m_seStr;
		vector<wstring> m_voiceSEStr;

		//アニメーションUI
		vector<shared_ptr<AnimationUI>> m_startUI;
		shared_ptr<AnimationUI> m_goalUI;
		
		//エフェクトインターフェイス
		shared_ptr<EfkInterface> m_efkInterface;
		vector<shared_ptr<EfkEffect>> m_efkEffect;

		vector<shared_ptr<EfkPlay>> m_efkPlay;

		shared_ptr<GameObject> m_playerObj;
		shared_ptr<Transform> m_playerObjTrans;

		shared_ptr<UIBase> m_fadeInUI;

		//プレイヤーアイコン
		shared_ptr<UIBase> m_playerIconUI;
		shared_ptr<Transform> m_playerIconTrans;

		shared_ptr<ScoreUIPanel> m_itemCountUI;
		shared_ptr<ScoreUIPanel> m_scoreCountUI;

		shared_ptr<WaveSpawner> m_waveSpawner;

		shared_ptr<CutInUI> m_cutInUI;


		vector<int> m_gameClearScore;
		
		Vec2 m_baseMapUIPos;
		vector<Vec2> m_mapUIPos;
		Vec3 m_textScale;	

		//ゲームを停止させるフラグ
		bool m_isPause;

		//スペシャルジャンプ時のゲームスピード減少処理で使用
		float m_saveGameSpeed;
		float m_SpecialJumpSpeed;
		float m_specialJumpTimer;
		int m_specialJumpCount;
		int m_maxSpecialJumpCount;
		bool m_playSpecialSE;

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

		bool m_gameOver;
		float m_gameOverPos;

		//スポナーの生成終了フラグ
		unsigned int m_spawnFlag;
		bool m_isReset;

	public:
		//構築と破棄
		GameStage() :Stage()
		{
			m_textScale = Vec3(512.0f, 256.0f, 1.0f);

			m_isPause = false;
			m_startTimeCount = 0.0f;
			m_maxStartTime = 3.0f;
			m_isFrastStop = true;

			m_playSpecialSE = false;

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

			m_seStr = { L"decision16.wav", L"se_GameClear.wav", L"se_GameOver.wav", L"Voice2_13.wav", L"Voice2_15.wav", L"Voice1_11.wav" };
			m_gameOverPos = -5.0f;
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

		//ゲームUIを作成
		void CreateGameUI();

		//アニメーションUIを作成
		void CreateAnimUI();

		//ゴール時のUIを作成
		void CreateGoalUI();

		//オブジェクトを生成するジェネレーターを作成
		void CreateGenerator();

		//エフェクトを作成
		void CreateEfkEffect();
		//スコアUIの描画する数字を入れ替える
		void UpdateScoreUI();

		void Hundler();

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
		
		//ゲームオーバー時の処理
		void GameEnd();

		//スペシャルジャンプに入った時
		void SpecialJumpController();

		//マップのアイコンを動かす
		void MovePlayerIcon();

		//SEを再生する
		void PlaySE(EN_SoundTypeSE soundType, wstring seName, float vol);

		//ビットフラグを上げる
		void TrueSpawnFlag(unsigned int bit_flag);

		//ビットフラグを下げる
		void FalseSpawnFlag(unsigned int bit_flag);

		//フラグの状態を確認する
		bool ConfirmSpawnFlag(unsigned int bit_flag);

	};


}
//end basecross


/*!
@file GameStage.h
@brief ƒQ[ƒ€ƒXƒe[ƒW
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
	//	ƒQ[ƒ€ƒXƒe[ƒWƒNƒ‰ƒX
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//ƒrƒ…[‚Ìì¬
		void CreateViewLight();

		Bit_SpawnFlag m_spawnBitFlag;
		EffectNames m_effectNames;

		//BGM‚ÌÄ¶
		shared_ptr<SoundItem> m_BGM;
		vector<shared_ptr<SoundItem>> m_SE;
		vector<wstring> m_seStr;
		vector<wstring> m_voiceSEStr;

		//ƒAƒjƒ[ƒVƒ‡ƒ“UI
		vector<shared_ptr<AnimationUI>> m_startUI;
		shared_ptr<AnimationUI> m_goalUI;
		
		//ƒGƒtƒFƒNƒgƒCƒ“ƒ^[ƒtƒFƒCƒX
		shared_ptr<EfkInterface> m_efkInterface;
		vector<shared_ptr<EfkEffect>> m_efkEffect;

		vector<shared_ptr<EfkPlay>> m_efkPlay;

		shared_ptr<GameObject> m_playerObj;
		shared_ptr<Transform> m_playerObjTrans;

		shared_ptr<UIBase> m_fadeInUI;

		//ƒvƒŒƒCƒ„[ƒAƒCƒRƒ“
		shared_ptr<UIBase> m_playerIconUI;
		shared_ptr<Transform> m_playerIconTrans;

		//ï¿½Xï¿½Rï¿½AUI
		shared_ptr<ScoreUIPanel> m_itemCountUI;
		shared_ptr<ScoreUIPanel> m_scoreCountUI;
		shared_ptr<ScoreUIPanel> m_maxItemCountUI;


		shared_ptr<WaveSpawner> m_waveSpawner;

		shared_ptr<CutInUI> m_cutInUI;


		vector<int> m_gameClearScore;
		
		Vec2 m_baseMapUIPos;
		vector<Vec2> m_mapUIPos;
		Vec3 m_textScale;	

		//ƒQ[ƒ€‚ğ’â~‚³‚¹‚éƒtƒ‰ƒO
		bool m_isPause;

		//ƒXƒyƒVƒƒƒ‹ƒWƒƒƒ“ƒv‚ÌƒQ[ƒ€ƒXƒs[ƒhŒ¸­ˆ—‚Åg—p
		float m_saveGameSpeed;
		float m_SpecialJumpSpeed;
		float m_specialJumpTimer;
		int m_specialJumpCount;
		int m_maxSpecialJumpCount;
		bool m_playSpecialSE;
		bool m_isVisibleBigWaveScore;
		vector<int> m_maxSpecialCount;

		//ƒQ[ƒ€‚ğn‚ß‚é‘O‚Ìd’¼ŠÔ
		float m_startTimeCount;
		float m_maxStartTime;
		bool m_isFrastStop;

		//ƒQ[ƒ€‚ğƒNƒŠƒA‚µ‚½‚Ég‚¤
		float m_loadStageTimeCount;
		float m_maxLoadStageTime;
		float m_gameClearSpeed;
		bool m_isLoadStage;
		bool m_isCreateGoalUI;

		bool m_gameOver;
		float m_gameOverPos;

		//ƒXƒ|ƒi[‚Ì¶¬I—¹ƒtƒ‰ƒO
		unsigned int m_spawnFlag;
		bool m_isReset;

	public:
		//\’z‚Æ”jŠü
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
			m_maxSpecialCount = {5, 8, 10};

			m_maxLoadStageTime = 3.0f;

			m_gameClearSpeed = 0.2f;
			m_spawnFlag = 0;

			m_gameClearScore = { 100,200,300,400 };

			m_seStr = { L"decision16.wav", L"se_GameClear.wav", L"se_GameOver.wav", L"Voice2_13.wav", L"Voice2_15.wav", L"Voice1_11.wav" };
			m_gameOverPos = -5.0f;
		}

		virtual ~GameStage() {}
		//‰Šú‰»
		virtual void OnCreate()override;

		virtual void OnUpdate()override;

		//Áœ
		virtual void OnDestroy()override;

		//ƒGƒtƒFƒNƒgAƒeƒLƒXƒg•`‰æ
		virtual void OnDraw()override;

		//ƒQƒbƒ^[AƒZƒbƒ^[
		shared_ptr<EfkInterface> GetEfkInterface()const { return m_efkInterface; }

		vector<shared_ptr<EfkEffect>> GetEfkEffect()const { return m_efkEffect; }

		vector<shared_ptr<EfkPlay>> GetEfkPlay()const { return m_efkPlay; }

		void SetEfkPlay(vector<shared_ptr<EfkPlay>> set, int efkNum) { m_efkPlay = set; }

		//ƒQ[ƒ€UI‚ğì¬
		void CreateGameUI();

		//ƒAƒjƒ[ƒVƒ‡ƒ“UI‚ğì¬
		void CreateAnimUI();

		//ƒS[ƒ‹‚ÌUI‚ğì¬
		void CreateGoalUI();

		//ƒIƒuƒWƒFƒNƒg‚ğ¶¬‚·‚éƒWƒFƒlƒŒ[ƒ^[‚ğì¬
		void CreateGenerator();

		//ƒGƒtƒFƒNƒg‚ğì¬
		void CreateEfkEffect();
		//ƒXƒRƒAUI‚Ì•`‰æ‚·‚é”š‚ğ“ü‚ê‘Ö‚¦‚é
		void UpdateScoreUI();

		void Hundler();

		//ƒŠƒUƒ‹ƒgƒXƒe[ƒW‚ÉˆÚ“®
		void LoadResultStage();

		//ƒQ[ƒ€ƒf[ƒ^‚ğ•Û‘¶
		int SaveGameData();

		//ƒQ[ƒ€ƒf[ƒ^‚Ì“Ç‚İ‚İ
		int ReadGameData();

		//Å‰‚ÌƒQ[ƒ€’â~‚ÌƒJƒEƒ“ƒg
		void FrastTimeCount();

		//ƒQ[ƒ€ƒNƒŠƒA‚Ìˆ—
		void GameClear();
		
		//ƒQ[ƒ€ƒI[ƒo[‚Ìˆ—
		void GameEnd();

		//ƒXƒyƒVƒƒƒ‹ƒWƒƒƒ“ƒv‚É“ü‚Á‚½
		void SpecialJumpController();

		//ƒ}ƒbƒv‚ÌƒAƒCƒRƒ“‚ğ“®‚©‚·
		void MovePlayerIcon();

		//SE‚ğÄ¶‚·‚é
		void PlaySE(EN_SoundTypeSE soundType, wstring seName, float vol);

		//ƒrƒbƒgƒtƒ‰ƒO‚ğã‚°‚é
		void TrueSpawnFlag(unsigned int bit_flag);

		//ƒrƒbƒgƒtƒ‰ƒO‚ğ‰º‚°‚é
		void FalseSpawnFlag(unsigned int bit_flag);

		//ƒtƒ‰ƒO‚Ìó‘Ô‚ğŠm”F‚·‚é
		bool ConfirmSpawnFlag(unsigned int bit_flag);

	};


}
//end basecross


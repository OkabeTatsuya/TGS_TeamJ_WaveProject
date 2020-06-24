/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
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
#include "BigWaveScoreUI.h"

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
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();

		Bit_SpawnFlag m_spawnBitFlag;
		EffectNames m_effectNames;

		//BGM�̍Đ�
		shared_ptr<SoundItem> m_BGM;
		vector<shared_ptr<SoundItem>> m_SE;
		vector<wstring> m_seStr;
		vector<wstring> m_voiceSEStr;

		//�X�e�[�W�̃e�N�X�`��
		vector<wstring> m_noonTexName;
		vector<wstring> m_eveningTexName;
		vector<wstring> m_sunsetTexName;

		//�A�j���[�V����UI
		vector<shared_ptr<AnimationUI>> m_startUI;
		shared_ptr<AnimationUI> m_goalUI;
		shared_ptr<AnimationUI> m_failedUI;

		//�G�t�F�N�g�C���^�[�t�F�C�X
		shared_ptr<EfkInterface> m_efkInterface;
		vector<shared_ptr<EfkEffect>> m_efkEffect;

		//�G�t�F�N�g���Đ�����I�u�W�F�N�g
		vector<shared_ptr<EfkPlay>> m_efkPlay;

		//�v���C���[�I�u�W�F�N�g
		shared_ptr<GameObject> m_playerObj;
		shared_ptr<Transform> m_playerObjTrans;

		shared_ptr<UIBase> m_fadeInUI;

		//�v���C���[�A�C�R��
		shared_ptr<UIBase> m_playerIconUI;
		shared_ptr<Transform> m_playerIconTrans;

		//�X�R�AUI
		shared_ptr<ScoreUIPanel> m_itemCountUI;
		shared_ptr<ScoreUIPanel> m_scoreCountUI;
		shared_ptr<ScoreUIPanel> m_maxItemCountUI;

		//�r�b�O�E�F�[�u�Ŏ擾�����X�R�A��\������UI
		shared_ptr<BigWaveScoreUI> m_bigWaveScoreUI;

		//�E�F�[�u�X�|�i�[
		shared_ptr<WaveSpawner> m_waveSpawner;

		//�J�b�g�C��UI�I�u�W�F�N�g
		shared_ptr<CutInUI> m_cutInUI;
		
		//�}�b�vUI�̃x�[�X�ɂȂ�I�u�W�F�N�g
		Vec2 m_baseMapUIPos;
		vector<Vec2> m_mapUIPos;
		Vec3 m_textScale;	

		//�Q�[�����~������t���O
		bool m_isPause;

		//�X�y�V�����W�����v���̃Q�[���X�s�[�h���������Ŏg�p
		float m_saveGameSpeed;
		float m_SpecialJumpSpeed;
		float m_specialJumpTimer;
		int m_specialJumpCount;
		int m_maxSpecialJumpCount;
		bool m_playSpecialSE;
		bool m_isVisibleBigWaveScore;
		vector<int> m_maxSpecialCount;

		//�Q�[�����n�߂�O�̍d������
		float m_startTimeCount;
		float m_maxStartTime;
		bool m_isFrastStop;

		//�Q�[�����N���A�������Ɏg��
		float m_loadStageTimeCount;
		float m_maxLoadStageTime;
		float m_gameClearSpeed;
		bool m_isLoadStage;

		bool m_gameOver;
		float m_gameOverPos;

		//�X�|�i�[�̐����I���t���O
		unsigned int m_spawnFlag;
		bool m_isReset;

	public:
		//�\�z�Ɣj��
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

			m_maxLoadStageTime = 2.0f;

			m_gameClearSpeed = 0.2f;
			m_spawnFlag = 0;

			m_seStr = { L"decision16.wav", L"se_GameClear.wav", L"se_GameOver.wav", L"Voice2_13.wav", L"Voice2_15.wav", L"Voice1_11.wav" };

			m_noonTexName = { L"Sky.png" ,L"Ocean.png" ,L"Sea.png" ,L"cloud.png" ,L"Island.png" };
			m_eveningTexName = { L"SkyAfternoon.png" ,L"OceanAfternoon.png" ,L"SeaAfternoon.png" ,L"CloudAfternoon.png" ,L"Island.png" };
			m_sunsetTexName = { L"SkySunset.png" ,L"OceanSunset.png" ,L"SeaSunset.png" ,L"CloudSunset.png" ,L"Island.png" };

			m_gameOverPos = -5.0f;
		}

		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;

		virtual void OnUpdate()override;

		//������
		virtual void OnDestroy()override;

		//�G�t�F�N�g�A�e�L�X�g�`��
		virtual void OnDraw()override;

		//�Q�b�^�[�A�Z�b�^�[
		shared_ptr<EfkInterface> GetEfkInterface()const { return m_efkInterface; }
		vector<shared_ptr<EfkEffect>> GetEfkEffect()const { return m_efkEffect; }
		vector<shared_ptr<EfkPlay>> GetEfkPlay()const { return m_efkPlay; }
		void SetEfkPlay(vector<shared_ptr<EfkPlay>> set, int efkNum) { m_efkPlay = set; }

		//�Q�[��UI���쐬
		void CreateGameUI();

		//�A�j���[�V����UI���쐬
		void CreateAnimUI();

		//�S�[������UI���쐬
		void CreateGoalUI();
		//�R�}���h�\�L��UI���쐬
		void CreateCommandUI();

		//�I�u�W�F�N�g�𐶐�����W�F�l���[�^�[���쐬
		void CreateGenerator();

		//�G�t�F�N�g���쐬
		void CreateEfkEffect();

		//�X�R�AUI�̕`�悷�鐔�������ւ���
		void UpdateScoreUI();

		void Hundler();

		//���U���g�X�e�[�W�Ɉړ�
		void LoadResultStage();

		//�Q�[���f�[�^��ۑ�
		int SaveGameData();

		//�Q�[���f�[�^�̓ǂݍ���
		int ReadGameData();

		//�ŏ��̃Q�[����~���̃J�E���g
		void FrastTimeCount();

		//�Q�[���N���A���̏���
		void GameClear();
		
		//�Q�[���I�[�o�[���̏���
		void GameEnd();

		//�X�y�V�����W�����v�ɓ�������
		void SpecialJumpController();

		//�}�b�v�̃A�C�R���𓮂���
		void MovePlayerIcon();

		//SE���Đ�����
		void PlaySE(EN_SoundTypeSE soundType, wstring seName, float vol);

		//BGM���Đ�����
		void PlayBGM(wstring bgmName);

		//BGM�̃t�F�[�h�C��
		void FadeInBGM(float maxVol, float time);

		//�r�b�g�t���O���グ��
		void TrueSpawnFlag(unsigned int bit_flag);

		//�r�b�g�t���O��������
		void FalseSpawnFlag(unsigned int bit_flag);

		//�t���O�̏�Ԃ��m�F����
		bool ConfirmSpawnFlag(unsigned int bit_flag);
	};
}
//end basecross


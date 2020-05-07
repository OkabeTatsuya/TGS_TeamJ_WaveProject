/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
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
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();

		Bit_SpawnFlag m_spawnBitFlag;

		//BGM�̍Đ�
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<SoundItem> m_SE;

		vector<shared_ptr<AnimationUI>> m_startUI;
		shared_ptr<AnimationUI> m_goalUI;
		
		vector<int> m_gameClearScore;

		Vec3 m_textScale;

		//�Q�[�����~������t���O
		bool m_isPause;

		//�Q�[�����n�߂�O�̍d������
		float m_startTimeCount;
		float m_maxStartTime;
		bool m_isFrastStop;

		//�Q�[�����N���A�������Ɏg��
		float m_loadStageTimeCount;
		float m_maxLoadStageTime;
		float m_gameClearSpeed;
		bool m_isLoadStage;
		bool m_isCreateGoalUI;

		//�X�|�i�[�̐����I���t���O
		unsigned int m_spawnFlag;

	public:
		//�\�z�Ɣj��
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
		//������
		virtual void OnCreate()override;

		virtual void OnUpdate()override;

		//������
		virtual void OnDestroy()override;

		//�Q�b�^�[�A�Z�b�^�[

		void CreateAnimUI();

		void CreateGoalUI();

		void CreateGenerator();

		void LoadResultStage();

		int SaveGameData();

		int ReadGameData();

		void FrastTimeCount();

		void GameClear();
		
		//�r�b�g�t���O���グ��
		void TrueSpawnFlag(unsigned int bit_flag);

		//�r�b�g�t���O��������
		void FalseSpawnFlag(unsigned int bit_flag);

		//�t���O�̏�Ԃ��m�F����
		bool ConfirmSpawnFlag(unsigned int bit_flag);

	};


}
//end basecross


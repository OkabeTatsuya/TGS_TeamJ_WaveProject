/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();

		//BGM�̍Đ�
		shared_ptr<SoundItem> m_BGM;
		shared_ptr<SoundItem> m_SE;

		bool m_isPause;

		//�Q�[�����n�߂�O�̍d������
		float m_startTimeCount;
		float m_maxStartTime;
		bool m_isFrastStop;

		//�Q�[�����N���A�������Ɏg��
		float m_loadStageTimeCount;
		float m_maxLoadStageTime;
		bool m_isFadeIn;

	public:
		//�\�z�Ɣj��
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
		//������
		virtual void OnCreate()override;

		virtual void OnUpdate()override;

		//������
		virtual void OnDestroy()override;

		void LoadResultStage();

		int SaveGameData();

		int ReadGameData();

		void FrastTimeCount();

		void GameClear();

	};


}
//end basecross


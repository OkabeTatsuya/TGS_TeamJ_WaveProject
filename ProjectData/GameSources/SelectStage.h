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
	class SelectStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();

		//�X�e�[�W���I�΂ꂽ��
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
		//�\�z�Ɣj��
		SelectStage() :Stage() {
			m_stageName = L"ToGameStage";
			m_stageNum = 0;

			m_stickDelta = 0.5f;
			m_stickTime = 0.0f;
			m_stageImageName = { L"cloud2.png",
				L"Gaol_Pattern2.png", L"Seagull.png", L"Island.png"};
		}
		virtual ~SelectStage() {}
		//������
		virtual void OnCreate()override;

		virtual void OnUpdate()override;

		virtual void OnDestroy()override;

		//���Ԃ����߂āA�V�[����J�ڂ���
		void Sceneloader();

		//�R���g���[���[������
		void Handler();

		int LoadBinaryData();

		int CreateBinaryData();

		//UI�����֐�
		void CreateUI();

		void PushA();

		void StickL();

		void ChengeStegeNum();

		//BGM���Đ�������֐�
		void PlayBGM(wstring soundName, float vol);

		//SE���Đ�������֐�
		void PlaySE(wstring soundName, float vol);

	};
}
//end basecross


/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	���U���g�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class ResultStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();
		shared_ptr<UnlockStageUI> m_unlockStageUI;
		//�T�E���h
		shared_ptr<SoundItem> m_SE;
		shared_ptr<SoundItem> m_voiceSE;
		shared_ptr<SoundItem> m_BGM;
		//�{�C�X�̖��O
		vector<wstring> m_gameclearVoiceStr;
		vector<wstring> m_gameoverVoiceStr;

		float m_Time=0;//A�{�^��������3�b��ɃX�e�[�W��ʂɑJ��
		bool m_isPush;//A�{�^��������3�b��ɃX�e�[�W��ʂɑJ��

		float m_Timer = 3;//�R���g���[���[���X�e�B�b�N����
		bool m_Push;//�R���g���[���[���X�e�B�b�N����

		wstring m_ResultUi[3]; 

		int m_ResultUiCount = 0;

		bool m_playUnlockStageAnim;

		void m_ControllerA();

		//shared_ptr<�J�[�\���N���X�̖��O>
		shared_ptr<CursorUI>m_CursorUI;

		Vec2 GetMoveVector();

		Vec2 m_Pos[3];
	public:
		//�\�z�Ɣj��
		ResultStage() :Stage() {
			m_gameclearVoiceStr = { L"Voice1_12.wav",L"Voice1_13.wav" };
			m_gameoverVoiceStr = { L"Voice1_14.wav",L"Voice2_15.wav" };
		}

		virtual ~ResultStage() {}
		//������
		virtual void OnCreate()override;

		virtual void OnUpdate()override;

		virtual void OnDestroy()override;

		//���Ԃ����߂āA�V�[����J�ڂ���
		void Sceneloader();
		//�R���g���[���[������
		void Press();
		void SetNextStage();
		//UI���쐬����
		void CreateResultUI();
		//�X�e�[�W������o
		void UnlockStageAnim();

		//BGM�𗬂�
		void GetBGM();
		//SE�𗬂�
		void GetSE();

		void RandomVoiceSE();
	};

	//�R���g���[���[
	template<typename T>
	struct bInputHandler 
	{

		void Pushandle(const shared_ptr<T>& Obj)
		{

		}

	};


}
//end basecross

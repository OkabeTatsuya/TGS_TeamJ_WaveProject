#pragma once
#include "stdafx.h"

//�R���g���[���[
namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------

	class CopywriterStage : public Stage {
		//�t�F�[�h�C������UI
		shared_ptr<UIBase> m_fadeInUI;
		//SE
		shared_ptr<SoundItem>m_SE;
		//���[�h���鎞��
		float m_loadTimeCount;
		//�^�C�g���X�e�[�W�Ɉڂ鎞��
		float m_maxLoadTime;
		//���̃X�e�[�W�����[�h����t���O
		bool m_isLoadStage;


		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		CopywriterStage() :Stage() {
			m_isLoadStage = false;
			m_maxLoadTime = 2.0f;
			m_loadTimeCount = 0.0f;
		}

		virtual ~CopywriterStage() {}

		//������
		virtual void OnCreate()override;

		virtual void OnDestroy()override;

		virtual void OnUpdate()override;

		//UI���쐬
		void CreateUI();
		//�X�e�[�W�̃��[�h
		void LoadTitleStage();
		//�R���g���[���[�̓��͎�t
		void Hundler();
		//A�{�^���������ꂽ��
		void PushAButton();
	};
}
//end basecross

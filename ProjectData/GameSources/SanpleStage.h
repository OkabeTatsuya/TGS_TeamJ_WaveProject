/*!
@file SanpleStage.h
@brief �I�u�W�F�N�g�Љ�X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------

	class SanpleStage : public Stage {
		//BGM
		shared_ptr<SoundItem>m_BGM;

		//�r���[�̍쐬
		void CreateViewLight();
	public:

		//�\�z�Ɣj��
		SanpleStage() :Stage() {}
		virtual ~SanpleStage() {}

		//������
		virtual void OnCreate()override;

		//�ʂ̃X�e�[�W�Ɉڂ������ȂǁA���̃V�[�����j������鎞�ɌĂ΂��֐�
		virtual void OnDestroy()override;

		virtual void OnUpdate()override;

		//UI�����֐�
		void CreateUI();

		//BGM���Đ�������֐�
		void PlayBGM(wstring soundName, float vol);

		//�V�[�������[�h����֐�
		void LoadStage(wstring stageName);
	};
}
//end basecross

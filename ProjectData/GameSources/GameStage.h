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

		float m_startTimeCount;
		float m_maxStartTime;
		bool m_isFrastStop;

	public:
		//�\�z�Ɣj��
		GameStage() :Stage() {}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;

		//������
		virtual void OnDestroy()override;

		void FrastTimeCount();
	};


}
//end basecross


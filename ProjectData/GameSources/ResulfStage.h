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
	class ResulfStage : public Stage {
		//�r���[�̍쐬
		void CreateViewLight();

	public:
		//�\�z�Ɣj��
		ResulfStage() :Stage() {}
		virtual ~ResulfStage() {}
		//������
		virtual void OnCreate()override;
	};


}
//end basecross


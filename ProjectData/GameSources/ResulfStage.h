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

	//�R���g���[���[
	template<typename T>
	struct bInputHandler 
	{
		voidPushHandler
		{
			void Pushandle(const shared_ptr<T>& Obj)
			{
			//�R���g���[���[�̎擾
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			  if (cntVec[0].bConnected) {
				  //A�{�^��
				  if (cntVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
				  {
					  obj->OnPushA();

				  }
			  }
		}

	};



}
//end basecross


#pragma once
#include "stdafx.h"

//�R���g���[���[
namespace basecross {
	template<typename T>
	struct InputHandler {
		void PushHandle(const shared_ptr<T>& Obj) {
			auto cutlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bconnected) {
			}
		}
	};

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------

	class TitleStage : public Stage {
		//BGM
		shared_ptr<SoundItem>m_BGM;
		//SE
		shared_ptr<SoundItem>m_SE;

		//�r���[�̍쐬
		void CreateViewLight();
	public:

		//�\�z�Ɣj��
		TitleStage() :Stage() {}
		virtual ~TitleStage() {}

		//������
		virtual void OnCreate()override;

		virtual void OnDestroy()override;

		virtual void OnUpdate()override;
	};
}
//end basecross

/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void ResulfStage::CreateViewLight() {//���U���g���
		const Vec3 eye(0.0f, 0.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();

	}



	void ResulfStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//					 ���[�e�[�V����,�X�P�[��,�|�W�V����
			//AddGameObject<Enemy>(Vec3(0.0f), Vec3(10.0f), Vec3(0.0f));

			AddGameObject<UIBase>(Vec3(0.0f), Vec3(40.0f, 40.0f, 1.0f), Vec2(-600.0f, 350.0f), float(2.0f), L"trace.png");
			//App::GetApp()->GetScene<Scene>()->LoadStage(L"ToGameStage");


			//�V�[���ړ�
			//App::GetApp()->GetScene<Scene>()->LoadStage(L"ToTitleStage");
		
			//�T�E���h�̒ǉ�
			auto BGM = App::GetApp()->GetXAudio2Manager();
			BGM->Start(L"SampleBGM.wav", 0, 0.5f);


		}
		catch (...) {

			throw;
		}
	}

}
//end basecross

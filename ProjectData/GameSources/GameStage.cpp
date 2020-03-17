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
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 0.0f, -10.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);//���W
		PtrCamera->SetAt(at);//�œ_
        PtrCamera->SetPers(false);//���ߖ@
        PtrCamera->SetWidth(10);//��ʂɕ\�����鉡���̃��j�b�g��
        PtrCamera->SetHeight(10);//��ʂɕ\������c���̃��j�b�g��
        PtrCamera->SetFovY(0.5f);//����p
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
            SetPhysicsActive(true);

			AddGameObject<WaveSpawner>();

            AddGameObject<Player>(Vec3(0, 0, 0), Vec3(1, 1, 1),Vec3(-4.0, 2, 0));
            AddGameObject<GroundCollision>(Vec3(0, 0, 0), Vec3(1, 0.5, 3), Vec3(-4, -2, 0));

			//AddGameObject<Wave>(Vec3(0, 0, 0), Vec3(1, 1, 1), Vec3(0, -1.5, 0));
			//AddGameObject<Wave>(Vec3(0, 0, 0), Vec3(1, 1, 1), Vec3(8, -1.5, 0));
			//AddGameObject<Wave>(Vec3(0, 0, 0), Vec3(1, 1, 1), Vec3(16, -1.5, 0));
			
			auto BGM = App::GetApp()->GetXAudio2Manager();
			m_BGM = BGM->Start(L"SampleBGM.wav", XAUDIO2_LOOP_INFINITE, 0.4f);
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnDestroy() {
		//BGM�̃X�g�b�v
		auto BGM = App::GetApp()->GetXAudio2Manager();
		BGM->Stop(m_BGM);
	}


}
//end basecross

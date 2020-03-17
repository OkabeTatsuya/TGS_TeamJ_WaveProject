#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------

	void TitleStage::CreateViewLight() {
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
	void TitleStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			AddGameObject<UIBase>(Vec3(0.0f), Vec3(500.0f,500.0f, 1.0f), Vec2(0.0f, 0.0f), float(2.0f), L"FadeBG.png");

			//BGM�Đ�
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			m_BGM = XAPtr->Start(L"SampleBGM.wav", XAUDIO2_LOOP_INFINITE, 0.4f);
			
			//App::GetApp()->GetScene<Scene>()->LoadStage(L"ToGameStage");
		}
		catch (...) {
			throw;
		}
	}

	void TitleStage::OnUpdate(){
		//B�{�^���ŃV�[���ړ�
		auto CutlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CutlVec[0].bConnected) {
			if (CutlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
				PostEvent(0.0f, GetThis <ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
			}

			//A�{�^���������āA3�b�o������V�[���ړ�
			if (CutlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
				if (!m_isPushA) {
					//SE�Đ�
					auto XAPtr = App::GetApp()->GetXAudio2Manager();
					m_SE = XAPtr->Start(L"se_maoudamashii_system37.wav", 0, 0.1f);
					//A�{�^�����������Ƃ��̏���
					m_isPushA = true;
				}
			}
		}

		//���Ԃ�ۑ�����
		if (m_isPushA) {
			m_time += App::GetApp()->GetElapsedTime();
		}

		//�V�[���ړ�
		if (m_time >= 3) {
			PostEvent(0.0f, GetThis <ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
			
		}
	}

	//BGM���~�߂�
	void TitleStage::OnDestroy() {
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
		XAPtr->Stop(m_SE);
	}
}
//end basecross

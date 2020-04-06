/*!
@file SanpleStage.cpp
@brief �I�u�W�F�N�g�Љ�X�e�[�W�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�J�����A���C�g�̐ݒ�
	//--------------------------------------------------------------------------------------
	void SanpleStage::CreateViewLight() {
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

	void SanpleStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			//UI�����֐�
			CreateUI();

			//BGM���Đ�������֐�
			PlayBGM(L"SampleBGM.wav", 0.5f);

			//�w�肵���V�[�������[�h����֐�
			//LoadStage(L"ToTitleStage");
		}
		catch (...) {
			throw;
		}
	}

	void SanpleStage::OnUpdate(){

	}

	//--------------------------------------------------------------------------------------
	//�ʂ̃X�e�[�W�Ɉڂ������ȂǁA���̃V�[�����j������鎞�ɌĂ΂��֐�
	//--------------------------------------------------------------------------------------
	void SanpleStage::OnDestroy() {
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	//--------------------------------------------------------------------------------------
	//UI�����֐�
	//--------------------------------------------------------------------------------------
	void SanpleStage::CreateUI() {
		//�摜��\������UI
		//�����@Vec3(Rot),Vec3(Sca),Vec2(Pos.xy),float(Layer),wstring(ImageName)
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(100.0f, 100.0f, 1.0f), Vec2(-150.0f, 0.0f), float(2.0f), L"FadeBG.png");
		//AddGameObject<ImageUI>(Vec3(0.0f), Vec3(1280.0f, 800.0f, 1.0f), Vec2(0.0f, 0.0f), float(3.0f), L"BGImage.png");

		//�摜��_�ł�����UI
		//�����@Vec3(Rot),Vec3(Sca),Vec2(Pos.xy),float(Layer),wstring(ImageName),float(FlashSpeed)
		AddGameObject<FlashingUI>(Vec3(0.0f), Vec3(100.0f, 100.0f, 1.0f), Vec2(150.0f, 0.0f), float(2.0f), L"FadeBG.png", 2.0f);
		//AddGameObject<FlashingUI>(Vec3(0.0f), Vec3(1280.0f, 800.0f, 1.0f), Vec2(0.0f, 0.0f), float(3.0f), L"BGImage.png",3.5f);

	}

	//--------------------------------------------------------------------------------------
	//BGM���Đ�������֐�
	//--------------------------------------------------------------------------------------
	void SanpleStage::PlayBGM(wstring soundName, float vol) {
		//BGM�Đ��Ɖ��ʒ���
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(soundName, XAUDIO2_LOOP_INFINITE, vol);
	}

	//--------------------------------------------------------------------------------------
	//�V�[�������[�h����֐�
	//--------------------------------------------------------------------------------------
	void SanpleStage::LoadStage(wstring stageName) {
		App::GetApp()->GetScene<Scene>()
			->PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), stageName);
	}

}
//end basecross

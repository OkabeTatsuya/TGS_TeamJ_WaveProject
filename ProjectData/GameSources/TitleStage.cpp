#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�^�C�g���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------

	void TitleStage::CreateViewLight() {
		const Vec3 eye(0.0f, 0.0f, -10.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();

		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);

		PtrCamera->SetPers(false);//���ߖ@
		PtrCamera->SetWidth(10);//��ʂɕ\�����鉡���̃��j�b�g��
		PtrCamera->SetHeight(10);//��ʂɕ\������c���̃��j�b�g��
		PtrCamera->SetFovY(0.5f);//����p

		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();

		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}
	void TitleStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			//�l�̏�����
			GameManager::GetInstance().ResetGame();

			//�o�b�N�O���E���h
			BackGroundState SkyState = { Vec3(0.0f), Vec3(-10.0f,  0.0f,  0.0f),	Vec2(5.0f, 5.0f), 0, L"Sky.png", -10.0f, 0.037f };
			BackGroundState SeaBGState = { Vec3(0.0f), Vec3(-10.0f,  0.0f, -3.0f),	Vec2(5.0f, 5.0f), 3, L"Ocean.png", -10.0f, 0.037f };
			BackGroundState SeaState = { Vec3(0.0f), Vec3(-10.0f, -0.12f, -8.0),	Vec2(5.0f, 5.0f), 5, L"Sea.png", -10.0f, 0.137f };
			BackGroundState CloudState = { Vec3(0.0f), Vec3(-10.0f,  0.0f, -1.0),	Vec2(5.0f, 5.0f), 1, L"cloud.png", -10.0f, 0.0062f };
			BackGroundState IslandState = { Vec3(0.0f), Vec3(-10.0f, -0.3f, -2.0),	Vec2(1.5f, 1.5f), 2, L"Island.png", -10.0f, 0.02f };

			AddGameObject<BGGenerator>(SkyState);
			AddGameObject<BGGenerator>(SeaBGState);
			AddGameObject<BGGenerator>(SeaState);
			AddGameObject<BGGenerator>(CloudState);
			AddGameObject<RandomGenerator>(IslandState, 10.0f, 15);
			AddGameObject<Fade>();

			//�摜
			AddGameObject<TitleAnimationUI>(Vec3(0.0f), Vec3(200.0f, 200.0f, 1.0f), Vec2(-500.0f, -245.0f), float(4.0f), L"JumpFinish_7.png");

			//AddGameObject<UIBase>(Vec3(0.0f), Vec3(200.0f, 200.0f, 1.0f), Vec2(-500.0f, -225.0f), float(2.0f), L"JumpFinish_7.png");

			//AddGameObject<UIBase>(Vec3(0.0f), Vec3(200.0f, 200.0f, 1.0f), Vec2(0.0f, 0.0f), float(2.0f), L"JumpFinish_1.png");

			//AddGameObject<UIBase>(Vec3(0.0f), Vec3(200.0f, 200.0f, 1.0f), Vec2(500.0f, -225.0f), float(2.0f), L"JumpFinish_7.png");

			//�^�C�g���摜
			AddGameObject<UIBase>(Vec3(0.0f), Vec3(1024.0f, 512.0f, 1.0f), Vec2(50.0f,100.0f), float(9.0f), L"TitleLogo.png");

			//�_�ł����ă{�^�������Ă���������UI
			AddGameObject<FlashingUI>(Vec3(0.0f), Vec3(400.0f, 200.0f, 1.0f), Vec2(-0.0f, -200.0f), float(6.0f), L"StartBattan.png", 2.0f);

			//BGM�Đ��Ɖ��ʒ���
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			m_BGM = XAPtr->Start(L"game_maoudamashii_5_town12.wav", XAUDIO2_LOOP_INFINITE, 0.9f);
			
			m_SE = XAPtr->Start(L"Voice1_1.wav", 0, 1.0f);
			//App::GetApp()->GetScene<Scene>()->LoadStage(L"ToGameStage");

		}
		catch (...) {
			throw;
		}
	}

	void TitleStage::OnUpdate(){
		auto CutlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CutlVec[0].bConnected) {
			//A�{�^������������V�[���ړ�
			if (CutlVec[0].wPressedButtons) {
				if (!m_isPushA) {
					//SE�Đ��Ɖ��ʒ���
					auto XAPtr = App::GetApp()->GetXAudio2Manager();
					XAPtr->Stop(m_SE);

					m_SE = XAPtr->Start(L"Voice1_3.wav", 0, 1.0f);
					//A�{�^�����������Ƃ��̏���
					m_isPushA = true;
				}
			}
		}

		//���Ԃ�ۑ�����
		if (m_isPushA) {
			m_time += App::GetApp()->GetElapsedTime();
		}

		//A�{�^���������āA2�b�o������V�[���ړ�
		if (m_time >= 1.0f) {
			AddGameObject<Fade>(L"ToSelectStage");
			m_time = 0;
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

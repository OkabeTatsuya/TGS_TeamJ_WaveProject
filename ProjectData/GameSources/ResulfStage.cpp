/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	���U���g�X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void ResultStage::CreateViewLight() {//���U���g���
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
		{
			m_Time = false;
		}
	}

	//�{�^��������
	void ResultStage::Press() {
		auto cntVec = App::GetApp()->GetInputDevice().GetControlerVec();
		cntVec[0].wPressedButtons & XINPUT_GAMEPAD_A;
	}

	//�{�^���������ƃV�[���J�ڂ���
	void ResultStage::Sceneloader() {
		App::GetApp()->GetScene<Scene>()->LoadStage(m_ResultUi[m_ResultUiCount]);
	}

	//BGM�𗬂�����
	void ResultStage::GetBGM() {
		auto BGM = App::GetApp()->GetXAudio2Manager();
		m_BGM = BGM->Start(L"bgm_maoudamashii_acoustic41.wav", XAUDIO2_LOOP_INFINITE, 0.5f);
	}

	//SE�𗬂�����
	void ResultStage::GetSE() {
		auto SE = App::GetApp()->GetXAudio2Manager();
		m_SE = SE->Start(L"se_maoudamashii_system37.wav", 0, 0.5f);
	}

	void ResultStage::m_ControllerA()		//�R���g���[���[A
	{
		//�R���g���[���[�̎擾
		auto cntVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntVec[0].bConnected)
		{
			//A�{�^��
			if (cntVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
			{

				auto SE = App::GetApp()->GetXAudio2Manager();
				m_SE = SE->Start(L"se_maoudamashii_system37.wav", 0, 0.5f);

			}
		}
	}

	void ResultStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			/*Fade*/
			AddGameObject<Fade>();

			///*BG(�o�b�N�O���E���h)*/
			AddGameObject<ImageUI>(Vec3(0.0f), Vec3(1300.0f, 800.0f, 1.0f), Vec2(0.0f, 0.0f), float(2.0f), L"ResultBG.png");//��̉摜

			AddGameObject<ImageUI>(Vec3(0.0f), Vec3(700.0f, 700.0f, 1.0f), Vec2(-200.0f, -50.0f), float(2.0f), L"Junp3_34.png");//�v���C���[�̉摜
			
			/*�Q�[���N���Aor�Q�[���I�[�o�[*/
			//AddGameObject<ImageUI>(Vec3(0.0f), Vec3(800.0f, 150.0f, 1.0f), Vec2(0.0f, 300.0f), float(2.0f), L"Tx_GameClear.png");

			Vec3 buttonSize = Vec3(512.0f, 256.0f, 1.0f);
			/*�^�C�g����*/
			AddGameObject<ImageUI>(Vec3(0.0f), buttonSize, Vec2(-450.0f, -300.0f), float(2.0f), L"TitleButton.png");

			/*�X�e�[�W�Z���N�g��*/
			AddGameObject<ImageUI>(Vec3(0.0f), buttonSize, Vec2(-50.0f, -300.0f), float(2.0f), L"SelectButton.png");

			/*���̃X�e�[�W��*/
			AddGameObject<ImageUI>(Vec3(0.0f), buttonSize, Vec2(400.0f, -300.0f), float(2.0f), L"NextStageButton.png");

			/*�X�e�[�W�ԍ��̕\��*/
			AddGameObject<ImageUI>(Vec3(0.0f), buttonSize, Vec2(-450.0f, 350.0f), float(2.0f), L"StageUI.png");

			AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(40.0f, 40.0f, 1.0f), Vec2(-400.0f, 350.0f), float(2.0f), L"BlackNumbers.png", 1, false);
			GameManager::GetInstance().DrawStageNum();

			Vec2 resultsTabelPos = Vec2(350.0f, 0.0f);
			AddGameObject<ImageUI>(Vec3(0.0f), Vec3(512.0f, 512.0f, 1.0f), resultsTabelPos, float(2.0f), L"ResultsTable.png");

			float scoreSize = 40.0f;
			vector<Vec2> resultsTabe = {
				resultsTabelPos + Vec2(200.0f, 110.0f),
				resultsTabelPos + Vec2(200.0f, 35.0f),
				resultsTabelPos + Vec2(120.0f, -40.0f),
				resultsTabelPos + Vec2(120.0f, -120.0f)
			};

			//�X�R�A�̕\��
			AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(50.0f, 50.0f, 1.0f), resultsTabe[0], float(2.0f), L"PinkNumbers.png", 7, false);
			GameManager::GetInstance().DrawScore();

			//�N���A�X�R�A�̕\��
			AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(scoreSize, scoreSize, 1.0f), resultsTabe[1], float(2.0f), L"GrayNumbers.png", 7, false);
			GameManager::GetInstance().DrawClearScore(GameManager::GetInstance().GetSelectStageNum());

			//Perfect�̉񐔂�\��
			AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(scoreSize, scoreSize, 1.0f), resultsTabe[2], float(2.0f), L"BlackNumbers.png", 2, false);
			GameManager::GetInstance().DrawJudgeCount(JudgeName::en_Perfect);

			//Good�̉񐔂�\��
			AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(scoreSize, scoreSize, 1.0f), resultsTabe[3], float(2.0f), L"BlackNumbers.png", 2, false);
			GameManager::GetInstance().DrawJudgeCount(JudgeName::en_Good);

			m_Pos[0] = Vec2(-450.0f, -300.0f);//�^�C�g����
			m_Pos[1] = Vec2(-50.0f, -300.0f);//�X�e�[�W�Z���N�g
			m_Pos[2] = Vec2(400.0f, -300.0f);//���̃X�e�[�W��

			/*�_��*/
			m_CursorUI = AddGameObject<CursorUI>(Vec3(0.0f), Vec3(400.0f, 80.0f, 1.0f), m_Pos[m_ResultUiCount], float(3.0f), L"FadeBG.png", float(2.0));


			//�T�E���h�̒ǉ�
			auto BGM = App::GetApp()->GetXAudio2Manager();
			m_BGM = BGM->Start(L"bgm_maoudamashii_acoustic41.wav", XAUDIO2_LOOP_INFINITE, 0.5f);

			//auto SE = App::GetApp()->GetXAudio2Manager();
			//m_SE = SE->Start(L"se_maoudamashii_system37.wav", 0, 0.5f);
			m_ResultUi[0] = L"ToTitleStage"; //���U���g��ʂ̃{�^���z�u
			m_ResultUi[1] = L"ToSelectStage";
			m_ResultUi[2] = L"ToGameStage";
			//m_ResultUi[3] = L"ToGameStage";

		}
		catch (...) {

			throw;
		}
	}

	void ResultStage::OnUpdate()
	{
		try
		{
			m_ControllerA();

			//�J�E���g���Ƃ�
			//m_Time += App::GetApp()->GetElapsedTime();

			auto cntVec = App::GetApp()->GetInputDevice().GetControlerVec();

			//�w�b�^�[�ɏ����Ȃ��ƕۑ�����Ȃ��̂Œ���
			//bool m_isPush = false;

			if (cntVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
			{
				//boll��true�ɂ���
				m_isPush = true;
			}

			if (m_isPush)
			{
				m_Time += App::GetApp()->GetElapsedTime();
			}

			if (m_Time >= 0.1)//0.1�b��ɃV�[���J��
			{
				AddGameObject<Fade>(m_ResultUi[m_ResultUiCount]);
				m_Time = 0.0f;
			}
			GetMoveVector();
		}
		catch (...) {

			throw;
		}
	}

	void ResultStage::OnDestroy() {

		auto SEManager = App::GetApp()->GetXAudio2Manager();
		SEManager->Stop(m_SE);

		auto AudioManager = App::GetApp()->GetXAudio2Manager();
		AudioManager->Stop(m_BGM);

	}

	Vec2 ResultStage::GetMoveVector()
	{
		Vec2 angle(0, 0);
		//�R���g���[���̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		float fThumbLX = 0.0f;
		float fThumbLY = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {

			fThumbLX = cntlVec[0].fThumbLX;
			fThumbLY = cntlVec[0].fThumbLY;
			wButtons = cntlVec[0].wButtons;
		}


		if (m_Push) {
			m_Timer += App::GetApp()->GetElapsedTime();

		}

		if (m_Timer >= 0.25)
		{
			if (fThumbLX <= -1.0f)//�X�e�B�b�N�����ɓ|�ꂽ��
			{
				auto SE = App::GetApp()->GetXAudio2Manager();
				SE->Start(L"se_maoudamashii_system37.wav", 0, 0.5f);
				m_Timer = 0;
				m_Push = true;

				m_ResultUiCount -= 1;//����1�ړ�
			}
			if (fThumbLX >= +1.0f)//�X�e�B�b�N���E�ɓ|�ꂽ��
			{
				auto SE = App::GetApp()->GetXAudio2Manager();
				SE->Start(L"se_maoudamashii_system37.wav", 0, 0.5f);
				m_Timer = 0;
				m_Push = true;

				m_ResultUiCount += 1;//�E��1�ړ�
			}
		}

		if (m_ResultUiCount > 2)//���U���g�{�^����3�ȏ�ړ����Ȃ��悤��
		{
			m_ResultUiCount = 2;
		}
		if (m_ResultUiCount < 0)
		{
			m_ResultUiCount = 0;
		}

		//�|�W�V������ݒ肷��
		m_CursorUI->GetComponent<Transform>()->SetPosition(Vec3(m_Pos[m_ResultUiCount].x, m_Pos[m_ResultUiCount].y, 1.0f));

		return angle;
	}
}
//end basecross

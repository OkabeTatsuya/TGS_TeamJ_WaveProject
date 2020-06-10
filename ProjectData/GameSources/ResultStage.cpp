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
		const Vec3 eye(0.0f, 0.0f, -20.0f);
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
			if (!m_isPlayUnlockStageAnim && cntVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
			{
				auto SE = App::GetApp()->GetXAudio2Manager();
				m_SE = SE->Start(L"se_maoudamashii_system37.wav", 0, 0.5f);

			}
		}
	}

	void ResultStage::SetNextStage() {
		auto &gameManager = GameManager::GetInstance();
		if (m_ResultUiCount == 0) {
			auto& manager = GameManager::GetInstance();
			auto clearStageNum = manager.GetClearStageNum();
			auto selectStageNum = manager.GetSelectStageNum();

			if (selectStageNum < gameManager.GetSaveScore().size()-1 && selectStageNum < clearStageNum) {
				gameManager.SetSelectStageNum(selectStageNum + 1);
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
			AddGameObject<ImageUI>(Vec3(0.0f), Vec3(1300.0f, 800.0f, 1.0f), Vec2(0.0f, 0.0f), float(0.0f), L"ResultBG.png");//��̉摜

			if (GameManager::GetInstance().GetIsGameClear()) {
				AddGameObject<ImageUI>(Vec3(0.0f), Vec3(600.0f, 600.0f, 1.0f), Vec2(-250.0f, -0.0f), float(1.0f), L"WinIllsutration.png");//�v���C���[�̉摜
			}
			else {
				AddGameObject<ImageUI>(Vec3(0.0f), Vec3(600.0f, 600.0f, 1.0f), Vec2(-250.0f, -0.0f), float(1.0f), L"LoseIllsutration.png");//�v���C���[�̉摜
			}
			
			/*�Q�[���N���Aor�Q�[���I�[�o�[*/
			//AddGameObject<ImageUI>(Vec3(0.0f), Vec3(800.0f, 150.0f, 1.0f), Vec2(0.0f, 300.0f), float(2.0f), L"Tx_GameClear.png");

			Vec3 buttonSize = Vec3(512.0f, 256.0f, 1.0f);

			m_Pos[0] = Vec2(-430.0f, -300.0f);//���̃X�e�[�W��
			m_Pos[1] = Vec2(0.0f, -300.0f);//�X�e�[�W�Z���N�g
			m_Pos[2] = Vec2(430.0f, -300.0f);//�^�C�g����

			/*���̃X�e�[�W��*/
			AddGameObject<ImageUI>(Vec3(0.0f), buttonSize, m_Pos[0], float(2.0f), L"NextStageButton.png");

			/*�X�e�[�W�Z���N�g��*/
			AddGameObject<ImageUI>(Vec3(0.0f), buttonSize, m_Pos[1], float(2.0f), L"SelectButton.png");

			/*�^�C�g����*/
			AddGameObject<ImageUI>(Vec3(0.0f), buttonSize, m_Pos[2], float(2.0f), L"TitleButton.png");

			/*�X�e�[�W�ԍ��̕\��*/
			AddGameObject<ImageUI>(Vec3(0.0f), buttonSize, Vec2(-450.0f, 350.0f), float(2.0f), L"StageUI.png");

			AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(40.0f, 40.0f, 1.0f), Vec2(-200.0f, 350.0f), float(3.0f), L"BlackNumbers.png", 1, false);
			GameManager::GetInstance().DrawStageNum();

			CreateResultUI();

			/*�_��*/
			m_CursorUI = AddGameObject<CursorUI>(Vec3(0.0f), Vec3(400.0f, 80.0f, 1.0f), m_Pos[m_ResultUiCount], float(3.0f), L"FadeBG.png", float(2.0));


			//�T�E���h�̒ǉ�
			auto BGM = App::GetApp()->GetXAudio2Manager();
			m_BGM = BGM->Start(L"bgm_maoudamashii_acoustic41.wav", XAUDIO2_LOOP_INFINITE, 0.5f);

			RandomVoiceSE();

			m_ResultUi[0] = L"ToGameStage"; //���U���g��ʂ̃{�^���z�u
			m_ResultUi[1] = L"ToSelectStage";
			m_ResultUi[2] = L"ToTitleStage";
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

			if (!m_isPlayUnlockStageAnim && cntVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
			{
				//boll��true�ɂ���
				m_isPush = true;
			}

			if (m_isPush && !m_isloadStage)
			{
				m_Time += App::GetApp()->GetElapsedTime();
			}

			if (m_Time >= 0.1)//0.1�b��ɃV�[���J��
			{
				SetNextStage();
				AddGameObject<Fade>(m_ResultUi[m_ResultUiCount]);
				m_isloadStage = true;
				m_Time = 0.0f;
			}

			if (!m_isPlayUnlockStageAnim) {
				GetMoveVector();
			}

			UnlockStageAnim();
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
		AudioManager->Stop(m_voiceSE);
	}

	void ResultStage::CreateResultUI() {
		//���U���g�e�[�u���@���̒l��ύX����ƃX�R�AUI�����ׂĈړ�����
		Vec2 resultsTabelPos = Vec2(300.0f, 0.0f);
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(650.0f, 670.0f, 1.0f), resultsTabelPos, float(2.0f), L"WhiteBoard.png");

		float scoreSize = 40.0f;
		vector<Vec2> resultsTabe = {
			resultsTabelPos + Vec2(0.0f, 110.0f),		//�X�R�A
			resultsTabelPos + Vec2(-40.0f, 65.0f),		//�N���A�X�R�A
			resultsTabelPos + Vec2(-110.0f, -10.0f),	//�p�[�t�@�N�g��
			resultsTabelPos + Vec2(-110.0f, -90.0f),	//�O�b�h��
			resultsTabelPos + Vec2(40.0f, 90.0f),		//�X�R�A�Ԃ̐�
			resultsTabelPos + Vec2(10.0f, 30.0f),		//�X�R�A�e�L�X�g
			resultsTabelPos + Vec2(10.0f, 30.0f),		//�X�R�A�̉���
			resultsTabelPos + Vec2(-100.0f, -10.0f),	//�p�[�t�F�N�g�e�L�X�g
			resultsTabelPos + Vec2(-140.0f, -90.0f),	//�O�b�h�e�L�X�g
			resultsTabelPos + Vec2(-00.0f, -40.0f),		//�p�[�t�F�N�g�񐔂̉���
			resultsTabelPos + Vec2(-00.0f, -120.0f),	//�O�b�h�񐔂̉���
			resultsTabelPos + Vec2(-120.0f, -170.0f),	//�A�C�e��
			resultsTabelPos + Vec2(-110.0f, -170.0f),   //�A�C�e����
			resultsTabelPos + Vec2(-40.0f, -170.0f),	//�A�C�e�����̏��
			resultsTabelPos + Vec2(130.0f, -10.0f),		//�~�e�L�X�g�P
			resultsTabelPos + Vec2(130.0f, -90.0f),		//�~�e�L�X�g�Q
			resultsTabelPos + Vec2(130.0f, -170.0f),	//�~�e�L�X�g�R
			resultsTabelPos + Vec2(200.0f, -10.0f),		//�p�[�t�F�N�g�̃X�R�A
			resultsTabelPos + Vec2(200.0f, -90.0f),		//�O�b�h�̃X�R�A
		};

		Vec2 baseScale = Vec2(1.0f);

		//�X�R�A�̕\��
		AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(45.0f, 45.0f, 1.0f), resultsTabe[0], float(3.0f), L"PinkNumbers.png", 7, false,true);
		GameManager::GetInstance().DrawScore();

		//�N���A�X�R�A�̕\��
		AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(scoreSize, scoreSize, 1.0f), resultsTabe[1], float(3.0f), L"GrayNumbers.png", 7, false);
		GameManager::GetInstance().DrawClearScore(GameManager::GetInstance().GetSelectStageNum());

		//Perfect�̉񐔂�\��
		AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(scoreSize, scoreSize, 1.0f), resultsTabe[2], float(3.0f), L"BlackNumbers.png", 2, false);
		GameManager::GetInstance().DrawJudgeCount(JudgeName::en_Perfect);

		//Good�̉񐔂�\��
		AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(scoreSize, scoreSize, 1.0f), resultsTabe[3], float(3.0f), L"BlackNumbers.png", 2, false);
		GameManager::GetInstance().DrawJudgeCount(JudgeName::en_Good);

		//�Z���N�g�e�L�X�g
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(512.0f, 512.0f, 1.0f), resultsTabe[5], float(3.0f), L"ScoreLetter.png");
		//�X�R�A����
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(420.0f, 7.0f, 1.0f), resultsTabe[6], float(3.0f), L"Border.png");
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(256.0f, 128.0f, 1.0f), resultsTabe[7], float(4.0f), L"Perfect.png");
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(256.0f, 128.0f, 1.0f), resultsTabe[8], float(4.0f), L"Good.png");

		//����
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(154.0f, 92.0f, 1.0f), resultsTabe[4], float(3.0f), L"DaigonalLine.png");
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(413.0f, 3.0f, 1.0f), resultsTabe[9], float(5.0f), L"UnderLine.png");
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(413.0f, 3.0f, 1.0f), resultsTabe[10], float(5.0f), L"UnderLine.png");

		//�A�C�e��
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(60.0f, 60.0f, 1.0f), resultsTabe[11], float(4.0f), L"Coin.png");

		//�A�C�e����
		AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(scoreSize, scoreSize, 1.0f), resultsTabe[12], float(3.0f), L"BlackNumbers.png", 2, false);
		GameManager::GetInstance().DrawNum(GameManager::GetInstance().GetItemCount());

		//�A�C�e���̏��
		AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(scoreSize, scoreSize, 1.0f), resultsTabe[13], float(3.0f), L"BlackNumbers.png", 2, false);
		GameManager::GetInstance().DrawNum(GameManager::GetInstance().GetMaxItemNum());

		//X�e�L�X�g
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(50.0f, 50.0f, 1.0f), resultsTabe[16], float(5.0f), L"Slash.png");

		//�X�e�[�W�A�����b�N���oUI
		m_unlockStageUI = AddGameObject<UnlockStageUI>(Vec3(0.0f), Vec3(50.0f, 50.0f, 1.0f), resultsTabe[16], float(5.0f), L"Slash.png");
	};

	void ResultStage::UnlockStageAnim() {
		auto& manager = GameManager::GetInstance();
		auto maxStageNum = manager.GetSaveScore().size();
		auto selectStageNum = manager.GetSelectStageNum();
		auto clearStageNum = manager.GetClearStageNum();

		//
		bool unlockFlag = clearStageNum == selectStageNum && selectStageNum < manager.GetGameClearScoreVector().size() -1;

		//�Q�[���N���A���A�A�����b�N���o���܂��N���Ă��Ȃ�
		if (!m_isPush && !m_unlockStageUI->GetIsEndAnim() && manager.GetIsGameClear() && unlockFlag) {
			auto unlockStageNum = clearStageNum + 1;

			if (manager.GetIsGameClear() && unlockStageNum < maxStageNum && clearStageNum == selectStageNum) {
				manager.SetClearStageNum(unlockStageNum);
			}

			m_isPlayUnlockStageAnim = true;
		}

		if (m_unlockStageUI->GetIsEndAnim()) {
			m_isPlayUnlockStageAnim = false;
		}

		if (m_isPlayUnlockStageAnim) {
			m_unlockStageUI->PlayAnim();
		}

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

	void ResultStage::RandomVoiceSE() {
		std::random_device rando;
		std::mt19937 mt(rando());
		int num = mt() % 2;

		auto SE = App::GetApp()->GetXAudio2Manager();
		if (GameManager::GetInstance().GetIsGameClear()) {
			m_voiceSE = SE->Start(m_gameclearVoiceStr[num], 0, 1.5f);
		}
		else {
			m_voiceSE = SE->Start(m_gameoverVoiceStr[num], 0, 1.0f);
		}

	}
}
//end basecross

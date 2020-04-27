/*!
@file SelectStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void SelectStage::CreateViewLight() {//���U���g���
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


	void SelectStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			CreateUI();

            AddGameObject<Fade>();
	
			LoadBinaryData();

			CreateBinaryData();
			//�T�E���h�̒ǉ�
			//PlayBGM(L"SampleBGM.wav", 0.5f);

		}
		catch (...) {

			throw;
		}
	}

	void SelectStage::OnUpdate()
	{
		Handler();
	}

	void SelectStage::OnDestroy() {

		auto SEManager = App::GetApp()->GetXAudio2Manager();
		SEManager->Stop(m_SE);

		auto AudioManager = App::GetApp()->GetXAudio2Manager();
		AudioManager->Stop(m_BGM);

	}

	//�R���g���[���[�̓���
	void SelectStage::Handler() {
		auto controlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		float sticNum = 0.8f;
		if (controlVec.bConnected && !m_isSelectStage) {
			bool trueStic = controlVec.fThumbLX <= sticNum && controlVec.fThumbLX >= -sticNum;

			if (!trueStic) {
				StickL();
			}
			else {
				m_stickTime = 0.0f;
			}

			if (controlVec.wPressedButtons & XINPUT_GAMEPAD_A) {
				PushA();
			}
		}
	}

	//A�{�^���������ꂽ���̏���
	void SelectStage::PushA() {
		GameManager::GetInstance().SetSelectStageNum(m_stageNum);
		PlaySE(L"se_maoudamashii_system37.wav", 0.5f);
		Sceneloader();
		m_isSelectStage = true;
	}

	//�X�e�B�b�N���|���ꂽ���̏���
	void SelectStage::StickL() {
		auto controlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		float sticNum = 0.8f;
		auto time = App::GetApp()->GetElapsedTime();

		//�X�e�B�b�N���ŏ��ɓ|���ꂽ��
		if (m_stickTime == 0.0f) {
			m_isChengeStage = true;
		}

		//�X�e�B�b�N�����������ꂽ��
		if (m_stickTime > m_stickDelta) {
			m_isChengeStage = true;
			m_stickTime = 0.1f;
		}
		else {
			m_stickTime += time;
		}

		//�ŏ��ɓ|�����Ƃ��A��莞�Ԓ��������ꂽ�Ƃ��ɃX�e�[�W��؂�ւ���
		if (m_isChengeStage) {
			if (controlVec.fThumbLX >= sticNum) {
				m_stageNum++;
			}
			else if (controlVec.fThumbLX <= -sticNum) {
				m_stageNum--;
			}
			m_isChengeStage = false;

			//�ŏ��X�e�[�W���𒴂�����ő�Ɉڂ�
			if (m_stageNum < 0) {
				m_stageNum = (int)m_stageImageName.size() - 1;
			}
			//�ő�X�e�[�W���𒴂�����ŏ��Ɉڂ�
			if (m_stageNum > (int)m_stageImageName.size() - 1) {
				m_stageNum = 0;
			}

			//�摜�̍����ւ�
			m_stageImageUI->ChangeImage(m_stageImageName[m_stageNum]);

			PlaySE(L"se_maoudamashii_system37.wav", 0.5f);
		}

	}

	//
	int SelectStage::LoadBinaryData() {
		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);

		wstring outfile = mediaDir + L"GameData/SaveData/file.otb";
		vector<int> saveNum = GameManager::GetInstance().GetSaveScore();
		ifstream fin(outfile, ios::in | ios::binary);

		//�ǂݍ��߂Ȃ�������1��Ԃ�
		if (!fin) {
			fin.close();
			return 1;
		}

		//�X�e�[�W�̐������Z�[�u�f�[�^�����
		if (m_stageImageName.size() > saveNum.size()) {
			for (int i = 0; i < m_stageImageName.size(); i++) {
				saveNum.push_back(0);
			}
		}

		int num = 0;
		//�o�C�i���f�[�^�̒��g���ׂĂ��m�F����
		while (!fin.eof()) {
			//�o�C�i���f�[�^��ǂݍ���
			fin.read((char *)&saveNum[num], sizeof(int));
			num++;
			GameManager::GetInstance().SetSaveScore(saveNum);
		}
		fin.close();
		return 0;
	}


	//�ۑ��f�[�^�̐�������Ȃ��������ɍ�蒼������
	int SelectStage::CreateBinaryData() {
		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);

		wstring outfile = mediaDir + L"GameData/SaveData/file.otb";
		vector<int> saveNum;

		ofstream fout(outfile, ios::out | ios::binary | ios::trunc);
		ofstream fadd(outfile, ios::app | ios::binary);

		//�ǂݍ��߂Ȃ�������1��Ԃ�
		if (!fout) {
			fout.close();
			fadd.close();
			return 1;
		}

		auto saveScore = GameManager::GetInstance().GetSaveScore();

		//�T�C�Y������Ȃ�������
		if (saveScore.size() < m_stageImageName.size()) {
			for (int i = 0; i < saveNum.size(); i++) {
				fout.write((char *)&saveNum[i], sizeof(int));
			}
			fout.close();

			int loopNum = m_stageImageName.size() - saveScore.size() + 1;
			int nown = 0;
			for (int i = 0; i < loopNum; i++) {
				fadd.write((char *)&nown, sizeof(int));
			}
			fadd.close();

			return 0;
		}

		fout.close();
		fadd.close();
		return 0;
	}


	void SelectStage::CreateUI() {
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(1300.0f, 800.0f, 1.0f), Vec2(0.0f, 0.0f), float(1.0f), L"FadeBG.png");

		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(256.0f, 64.0f, 1.0f), Vec2(0.0f, -300.0f), float(2.0f), L"Tx_Stage1.png");

		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(128.0f, 128.0f, 1.0f), Vec2(550.0f, 0.0f), float(2.0f), L"RightArrow.png");
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(128.0f, 128.0f, 1.0f), Vec2(-550.0f, 0.0f), float(2.0f), L"LeftArrow.png");

		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(512.0f, 128.0f, 1.0f), Vec2(0.0f, 300.0f), float(2.0f), L"TxStageSelect.png");


		
		//�X�e�[�W�̃C���[�W�摜���擾
		m_stageImageUI = AddGameObject<ImageUI>(Vec3(0.0f), Vec3(300.0f, 300.0f, 1.0f), Vec2(0.0f, 0.0f), float(2.0f), m_stageImageName[m_stageNum]);
	}


	void SelectStage::ChengeStegeNum() {

	}

	//--------------------------------------------------------------------------------------
	//BGM���Đ�������֐�
	//--------------------------------------------------------------------------------------
	void SelectStage::PlayBGM(wstring soundName, float vol) {
		//BGM�Đ��Ɖ��ʒ���
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(soundName, XAUDIO2_LOOP_INFINITE, vol);
	}

	//--------------------------------------------------------------------------------------
	//SE���Đ�������֐�
	//--------------------------------------------------------------------------------------
	void SelectStage::PlaySE(wstring soundName, float vol) {
		//BGM�Đ��Ɖ��ʒ���
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_SE = XAPtr->Start(soundName, 0.0f, vol);
	}

	//�{�^���������ƃV�[���J�ڂ���
	void SelectStage::Sceneloader() {
		AddGameObject<Fade>(m_stageName);
	}
}
//end basecross

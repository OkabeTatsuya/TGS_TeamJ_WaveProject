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

			GameManager::GetInstance().SetIsGameEnd(false);		
			GameManager::GetInstance().SetIsStopSpawner(false);
			GameManager::GetInstance().ReSetGameScore();

			ObjectState BGState = { Vec3(0.0f), Vec3(10.05f, 10.0f, 1.0f), Vec3(-10.0f, 0.0f, 0.0f), L"Sea2.png", -6.0f };
			ObjectState SeaState = { Vec3(0.0f), Vec3(10.05f, 2.0f, 1.0f), Vec3(0.0, -4.0, -5.0), L"Sea1.png", -6.0f };

			AddGameObject<BGGenerator>(BGState);

			AddGameObject<WaveSpawner>();
			AddGameObject<GoalGenerator>();

            AddGameObject<Sea>(Vec3(0, 0, 0), Vec3(11, 4, 1), Vec3(0, -3.7, -5.0));
            AddGameObject<Player>(Vec3(0, 0, 0), Vec3(1, 1, 1),Vec3(-4.0, -2, -3.0));
            AddGameObject<SeaCollision>(Vec3(0, 0, 0), Vec3(1, 0.5, 1), Vec3(-4, -4, -3.0));

            AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(50.0f, 50.0f, 1.0f), Vec2(600.0f, 350.f), float(2.0f),L"",7);

			auto BGM = App::GetApp()->GetXAudio2Manager();
			m_BGM = BGM->Start(L"SampleBGM.wav", XAUDIO2_LOOP_INFINITE, 0.5f);
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate() {
		GameClear();
	}

	void GameStage::OnDestroy() {
		//BGM�̃X�g�b�v
		auto BGM = App::GetApp()->GetXAudio2Manager();
		BGM->Stop(m_BGM);
	}

	//���߂̍d������
	void GameStage::FrastTimeCount() {
		if (m_startTimeCount < m_maxStartTime) {
			auto delta = App::GetApp()->GetElapsedTime();
			m_startTimeCount += delta;
		}
		else if(m_isFrastStop){
			m_isFrastStop = false;
			GameManager::GetInstance().SetIsStopSpawner(false);
		}
	}

	void GameStage::GameClear() {
		bool isGameEnd = GameManager::GetInstance().GetIsGameEnd();
		if (isGameEnd) {
			//SaveGameData();
			LoadResultStage();
		}
	}

	//���U���g�X�e�[�W�Ɉړ�
	void GameStage::LoadResultStage() {
		bool isGameEnd = GameManager::GetInstance().GetIsGameEnd();
		if (isGameEnd) {
			App::GetApp()->GetScene<Scene>()->LoadStage(L"ToResulfStage");
		}
	}

	//�Q�[���̃Z�[�u
	int GameStage::SaveGameData() {
		int saveNum = GameManager::GetInstance().GetGameScore();
		int num = 1;
		int save = 9999999;
		ofstream fout;

		FILE* fp;

		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);

		char saveFileName[] = "../media/GameData/SaveData/file.otb";
		//�J���Ȃ��������͐V�K�쐬
		fopen_s(&fp, saveFileName, "wb");

		for (int i = 0; i < 2; i++) {

			//�o�C�i���̏����o��
			fwrite(&saveNum, sizeof(saveNum), 1, fp);
		}

		num = num * 4;
		//�ꕔ���������o���������ꍇ�Ɏg��
		fseek(fp, num , SEEK_SET);
		fwrite(&save, sizeof(save), 1, fp);
		
		fclose(fp);

		return 0;
	}

	//�o�C�i���f�[�^�̃��[�h
	int GameStage::ReadGameData() {
		char outfile[] = "file.otb";
		int saveNum = 0;
		ifstream fin(outfile, ios::in | ios::binary);

		//�ǂݍ��߂Ȃ�������1��Ԃ�
		if (!fin) {
			fin.close();
			return 1;
		}

		//�o�C�i���f�[�^�̒��g���ׂĂ��m�F����
		while (!fin.eof()) {
			//�ǂݍ��݂����f�[�^�̈ʒu���w�肷��ꍇ�Ɏg��
			//int readBinaryItr = 0;
			//fin.seekg(readBinaryItr * sizeof(int));

			//�o�C�i���f�[�^��ǂݍ���
			fin.read((char *)&saveNum, sizeof(int));
		}
		fin.close();
		return 0;
	}


}
//end basecross

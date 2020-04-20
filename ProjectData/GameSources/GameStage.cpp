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
			GameManager::GetInstance().SetIsStopSpawner(true);
			GameManager::GetInstance().ReSetGameScore();

            AddGameObject<Fade>();

			CreateAnimUI();
			CreateGoalUI();

			CreateGenerator();

            AddGameObject<Player>(Vec3(0, 0, 0), Vec3(1.5f, 1.5f, 1),Vec3(-4.0, -2, -3.0));
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
		FrastTimeCount();
		GameClear();
	}

	void GameStage::OnDestroy() {
		//BGM�̃X�g�b�v
		auto BGM = App::GetApp()->GetXAudio2Manager();
		BGM->Stop(m_BGM);
	}

	//�A�j���[�V��������UI���쐬
	void GameStage::CreateAnimUI() {
		St_AnimUI statUIState1 = {
			Vec2(1000.0f,200.0f),Vec3(0.0f),m_textScale,
			Vec2(0.0f,200.0f),Vec3(0.0f),m_textScale,
			2.0f,0.0f,0.5f,AnimType::Delete
		};
		St_AnimUI statUIState2 = {
			Vec2(1000.0f,-200.0f),Vec3(0.0f),m_textScale,
			Vec2(0.0f,-200.0f),Vec3(0.0f),m_textScale,
			2.0f,2.0f,2.5f,AnimType::Delete
		};

		
		vector<St_AnimUI> animUIState{
			statUIState1,
			statUIState2
		};

		//����t����e�N�X�`��
		vector<wstring> texter {
			L"Tx_Ledy.png",
			L"Tx_Start.png"
		};

		for (int i = 0; i < animUIState.size(); i++) {
			m_startUI.push_back(AddGameObject<AnimationUI>(animUIState[i], texter[i], m_maxStartTime));
			m_startUI[i]->SetIsStartAnim(true);
		}
	}

	//�S�[���������̃A�j���[�V����UI���쐬
	void GameStage::CreateGoalUI() {
		St_AnimUI GoalUIState = {
			Vec2(1000.0f,200.0f),Vec3(0.0f),m_textScale,
			Vec2(0.0f,200.0f),Vec3(0.0f),m_textScale,
			2.0f,0.0f,0.5f,AnimType::Delete
		};

		//����t����e�N�X�`��
		wstring texter{
			L"Tx_Goal.png",
		};

		m_goalUI = AddGameObject<AnimationUI>(GoalUIState, texter, m_maxLoadStageTime);
		m_isCreateGoalUI = true;
	}

	//�W�F�l���[�^�[���쐬
	void GameStage::CreateGenerator() {
		BackGroundState BGState =  { Vec3(0.0f), Vec3(-10.0f, 0.0f, 0.0f), Vec2(5.0f, 5.0f), L"Sea2.png", -10.0f, 0.5f};
		BackGroundState SeaState = { Vec3(0.0f), Vec3(-10.0f, 0.0f, -5.0), Vec2(5.0f, 5.0f), L"Sea1.png", -10.0f, 1.5f};

		AddGameObject<BGGenerator>(BGState);
		AddGameObject<BGGenerator>(SeaState);

		AddGameObject<WaveSpawner>();
		AddGameObject<GoalGenerator>();
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

		if (isGameEnd && !m_isLoadStage) {
			auto time = App::GetApp()->GetElapsedTime();
			m_loadStageTimeCount += time;
			m_goalUI->SetIsStartAnim(true);
		}

		if (m_loadStageTimeCount > m_maxLoadStageTime) {
			//SaveGameData();
			m_isLoadStage = true;
			LoadResultStage();
		}
	}

	//���U���g�X�e�[�W�Ɉړ�
	void GameStage::LoadResultStage() {
		if (m_isLoadStage) {
            AddGameObject<Fade>(L"ToResulfStage");
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


	//�r�b�g�t���O���グ��
	void GameStage::TrueSpawnFlag(unsigned int bit_flag) {
		if (!(m_spawnFlag & bit_flag)) {
			m_spawnFlag |= bit_flag;
		}
	}

	//�r�b�g�t���O��������
	void GameStage::FalseSpawnFlag(unsigned int bit_flag) {
		if (m_spawnFlag & bit_flag) {
			m_spawnFlag &= ~(bit_flag);
		}
	}

	//�t���O�̏�Ԃ��m�F����
	bool GameStage::ConfirmSpawnFlag(unsigned int bit_flag) {
		if (m_spawnFlag & bit_flag) {
			return true;
		}
		else {
			return false;
		}
	}

}
//end basecross

/*!
@file GameStage.cpp
@brief ƒQ[ƒ€ƒXƒe[ƒWÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ƒQ[ƒ€ƒXƒe[ƒWƒNƒ‰ƒXÀ‘Ì
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 0.0f, -100.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ƒrƒ…[‚ÌƒJƒƒ‰‚Ìİ’è
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);//À•W
		PtrCamera->SetAt(at);//Å“_
        PtrCamera->SetPers(false);//‰“‹ß–@
        PtrCamera->SetWidth(10);//‰æ–Ê‚É•\¦‚·‚é‰¡•‚Ìƒ†ƒjƒbƒg”
        PtrCamera->SetHeight(10);//‰æ–Ê‚É•\¦‚·‚éc•‚Ìƒ†ƒjƒbƒg”
        PtrCamera->SetFovY(0.5f);//‹–ìŠp
		//ƒ}ƒ‹ƒ`ƒ‰ƒCƒg‚Ìì¬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//ƒfƒtƒHƒ‹ƒg‚Ìƒ‰ƒCƒeƒBƒ“ƒO‚ğw’è
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::OnCreate() {
		try {
			//ƒrƒ…[‚Æƒ‰ƒCƒg‚Ìì¬
			CreateViewLight();
            SetPhysicsActive(true);

			GameManager::GetInstance().SetIsGameEnd(false);		
			GameManager::GetInstance().SetIsStopSpawner(true);
			GameManager::GetInstance().ReSetGameScore();

            AddGameObject<Fade>();

			CreateAnimUI();
			CreateGoalUI();

			CreateGenerator();

            m_playerObj = AddGameObject<Player>(Vec3(0, 0, 0), Vec3(1.0f, 1.0f, 1),Vec3(-4.0, -2, -6.0));
            AddGameObject<SeaCollision>(Vec3(0, 0, 0), Vec3(1, 0.5, 1), Vec3(-4, -4.0, -6.0));

            AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(55.0f, 55.0f, 1.0f), Vec2(600.0f, 350.f), float(5.0f),L"",7,false);
			AddGameObject<ImageUI>(Vec3(0.0f), Vec3(256.0f, 64.0f, 1.0f), Vec2(100.0f, 350.f), float(5.0f), L"Score.png");

			auto BGM = App::GetApp()->GetXAudio2Manager();
			m_BGM = BGM->Start(L"game_maoudamashii_5_town05.wav", XAUDIO2_LOOP_INFINITE, 0.0f);
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate() {
		m_efkInterface->OnUpdate();
		FrastTimeCount();
		GameClear();
		auto BGM = App::GetApp()->GetXAudio2Manager();
		BGM->MyFadeIn(m_BGM, 0.5f, 2.0f);
		SpecialJumpController();
	}

	void GameStage::OnDestroy() {
		//BGM‚ÌƒXƒgƒbƒv
		auto BGM = App::GetApp()->GetXAudio2Manager();
		BGM->Stop(m_BGM);
	}

	//ƒAƒjƒ[ƒVƒ‡ƒ“‚·‚éUI‚ğì¬
	void GameStage::CreateAnimUI() {
		St_AnimUI statUIState1 = {
			//ï¿½ï¿½ï¿½ï¿½ï¿½gï¿½ï¿½ï¿½ï¿½ï¿½Xï¿½tï¿½Hï¿½[ï¿½ï¿½
			Vec2(1000.0f,100.0f),Vec3(0.0f),m_textScale,
			//ï¿½Aï¿½jï¿½ï¿½ï¿½[ï¿½Vï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ìƒgï¿½ï¿½ï¿½ï¿½ï¿½Xï¿½tï¿½Hï¿½[ï¿½ï¿½
			Vec2(0.0f,100.0f),Vec3(0.0f),m_textScale,
			//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½@ï¿½ï¿½ï¿½Cï¿½ï¿½ï¿½[ï¿½Aï¿½Aï¿½jï¿½ï¿½ï¿½[ï¿½Vï¿½ï¿½ï¿½ï¿½ï¿½Jï¿½nï¿½ï¿½ï¿½ÔAï¿½Iï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
			8.0f,0.0f,0.5f,
			//ï¿½Aï¿½jï¿½ï¿½ï¿½[ï¿½Vï¿½ï¿½ï¿½ï¿½ï¿½Iï¿½ï¿½ï¿½ï¿½Ìï¿½ï¿½ï¿½
			AnimType::Delete
		};
		St_AnimUI statUIState2 = {
			Vec2(1000.0f,-200.0f),Vec3(0.0f),m_textScale,
			Vec2(0.0f,-200.0f),Vec3(0.0f),m_textScale,
			8.0f,2.0f,2.5f,AnimType::Delete
		};

		
		vector<St_AnimUI> animUIState{
			statUIState1,
			statUIState2
		};

		//’£‚è•t‚¯‚éƒeƒNƒXƒ`ƒƒ
		vector<wstring> texter {
			L"Lady.png",
			L"Go.png"
		};

		for (int i = 0; i < animUIState.size(); i++) {
			m_startUI.push_back(AddGameObject<AnimationUI>(animUIState[i], texter[i], m_maxStartTime));
			m_startUI[i]->SetIsStartAnim(true);
		}

		AddGameObject<SpecialJumpUI>(Vec3(0.0f), Vec3(1400, 800, 0), Vec2(0.0f), float(4.0f), L"SpecialJumpBG.png");
	}

	//ƒS[ƒ‹‚µ‚½‚ÌƒAƒjƒ[ƒVƒ‡ƒ“UI‚ğì¬
	void GameStage::CreateGoalUI() {
		St_AnimUI GoalUIState = {
			Vec2(1000.0f,200.0f),Vec3(0.0f),m_textScale,
			Vec2(0.0f,200.0f),Vec3(0.0f),m_textScale,
			8.0f,0.0f,0.5f,AnimType::Delete
		};

		//’£‚è•t‚¯‚éƒeƒNƒXƒ`ƒƒ
		wstring texter{
			L"Gorl.png",
		};

		m_goalUI = AddGameObject<AnimationUI>(GoalUIState, texter, m_maxLoadStageTime);
		m_isCreateGoalUI = true;
	}

	//ƒWƒFƒlƒŒ[ƒ^[‚ğì¬
	void GameStage::CreateGenerator() {
		BackGroundState SkyState = { Vec3(0.0f), Vec3(-10.0f, 0.0f, 0.0f), Vec2(5.0f, 5.0f), L"Sky.png", -10.0f, 0.3f };
		BackGroundState SeaBGState =  { Vec3(0.0f), Vec3(-10.0f, 0.0f, -3.0f), Vec2(5.0f, 5.0f), L"Ocean.png", -10.0f, 0.3f};
		BackGroundState SeaState = { Vec3(0.0f), Vec3(-10.0f, -0.12f, -8.0), Vec2(5.0f, 5.0f), L"Sea.png", -10.0f, 1.1f };
		BackGroundState CloudState = { Vec3(0.0f), Vec3(-10.0f, 0.0f, -1.0), Vec2(5.0f, 5.0f), L"cloud.png", -10.0f, 0.05f };
		BackGroundState IslandState = { Vec3(0.0f), Vec3(-10.0f, -0.3f, -2.0), Vec2(1.5f, 1.5f), L"Island.png", -10.0f, 0.2f };

		AddGameObject<BGGenerator>(SkyState);
		AddGameObject<BGGenerator>(SeaBGState);
		AddGameObject<BGGenerator>(SeaState);
		AddGameObject<BGGenerator>(CloudState);
		AddGameObject<RandomGenerator>(IslandState, 10.0f, 15);

		AddGameObject<WaveSpawner>();
		AddGameObject<ItemGenerator>();
		AddGameObject<GoalGenerator>();
	}

	//‰‚ß‚Ìd’¼ŠÔ
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
		auto &gameManager = GameManager::GetInstance();
		bool isGameEnd = gameManager.GetIsGameEnd();

		if (isGameEnd && m_loadStageTimeCount == 0) {
			int stageNum = gameManager.GetSelectStageNum();
			int gameScore = gameManager.GetGameScore();

			if (gameManager.GetGameClearScore(stageNum) < gameScore) {
				gameManager.SetIsGameClear(true);
				auto AudioManager = App::GetApp()->GetXAudio2Manager();
				m_SE = AudioManager->Start(L"se_GameClear.wav", 0, 0.9f);
			}
			else {
				gameManager.SetIsGameClear(false);
				auto AudioManager = App::GetApp()->GetXAudio2Manager();
				m_SE = AudioManager->Start(L"se_GameOver.wav", 0, 0.9f);
			}
		}

		if (isGameEnd && !m_isLoadStage) {
			auto time = App::GetApp()->GetElapsedTime();
			m_loadStageTimeCount += time;
			m_goalUI->SetIsStartAnim(true);
		}

		if (m_loadStageTimeCount > m_maxLoadStageTime) {
			int gameScore = GameManager::GetInstance().GetGameScore();

			auto maxStageNum = gameManager.GetSaveScore().size();
			auto unlockStageNum = gameManager.GetClearStageNum() + 1;

			if (gameManager.GetIsGameClear() && unlockStageNum < maxStageNum) {
				gameManager.SetClearStageNum(unlockStageNum);
			}

			SaveGameData();
			LoadResultStage();
			m_isLoadStage = true;
			m_loadStageTimeCount = 0;
		}
	}

	//ƒŠƒUƒ‹ƒgƒXƒe[ƒW‚ÉˆÚ“®
	void GameStage::LoadResultStage() {
		if (m_isLoadStage) {
            AddGameObject<Fade>(L"ToResulfStage");
		}
	}

	//ƒQ[ƒ€‚ÌƒZ[ƒu
	int GameStage::SaveGameData() {
		int saveNum = GameManager::GetInstance().GetGameScore();
		int num = 1;
		int save = 9999999;
		ofstream fout;

		FILE* fp;

		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);

		char saveFileName[] = "../media/GameData/SaveData/file.otb";
		//ŠJ‚¯‚È‚©‚Á‚½‚ÍV‹Kì¬
		fopen_s(&fp, saveFileName, "wb");

		for (int i = 0; i < 2; i++) {

			//ƒoƒCƒiƒŠ‚Ì‘‚«o‚µ
			fwrite(&saveNum, sizeof(saveNum), 1, fp);
		}

		num = num * 4;
		//ˆê•”‚¾‚¯‘‚«o‚µ‚µ‚½‚¢ê‡‚Ég‚¤
		fseek(fp, num , SEEK_SET);
		fwrite(&save, sizeof(save), 1, fp);
		
		fclose(fp);

		return 0;
	}

	//ƒoƒCƒiƒŠƒf[ƒ^‚Ìƒ[ƒh
	int GameStage::ReadGameData() {
		char outfile[] = "file.otb";
		int saveNum = 0;
		ifstream fin(outfile, ios::in | ios::binary);

		//“Ç‚İ‚ß‚È‚©‚Á‚½1‚ğ•Ô‚·
		if (!fin) {
			fin.close();
			return 1;
		}

		//ƒoƒCƒiƒŠƒf[ƒ^‚Ì’†g‚·‚×‚Ä‚ğŠm”F‚·‚é
		while (!fin.eof()) {
			//“Ç‚İ‚İ‚½‚¢ƒf[ƒ^‚ÌˆÊ’u‚ğw’è‚·‚éê‡‚Ég‚¤
			//int readBinaryItr = 0;
			//fin.seekg(readBinaryItr * sizeof(int));

			//ƒoƒCƒiƒŠƒf[ƒ^‚ğ“Ç‚İ‚Ş
			fin.read((char *)&saveNum, sizeof(int));
		}
		fin.close();
		return 0;
	}


	//ƒrƒbƒgƒtƒ‰ƒO‚ğã‚°‚é
	void GameStage::TrueSpawnFlag(unsigned int bit_flag) {
		if (!(m_spawnFlag & bit_flag)) {
			m_spawnFlag |= bit_flag;
		}
	}

	//ƒrƒbƒgƒtƒ‰ƒO‚ğ‰º‚°‚é
	void GameStage::FalseSpawnFlag(unsigned int bit_flag) {
		if (m_spawnFlag & bit_flag) {
			m_spawnFlag &= ~(bit_flag);
		}
	}

	//ƒtƒ‰ƒO‚Ìó‘Ô‚ğŠm”F‚·‚é
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

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
		const Vec3 eye(0.0f, 0.0f, -10.0f);
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

			AddGameObject<BGGenerator>();

			AddGameObject<WaveSpawner>();
            AddGameObject<Player>(Vec3(0, 0, 0), Vec3(1, 1, 1),Vec3(-4.0, 0, -3.0));
            AddGameObject<SeaCollision>(Vec3(0, 0, 0), Vec3(1, 0.5, 1), Vec3(-4, -2, -3.0));
            AddGameObject<Sea>(Vec3(0, 0, 0), Vec3(11, 4, 1), Vec3(0, -3.7, -5.0));

            AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(50.0f, 50.0f, 1.0f), Vec2(600.0f, 350.f), float(2.0f),L"",7);

			auto BGM = App::GetApp()->GetXAudio2Manager();
			m_BGM = BGM->Start(L"SampleBGM.wav", XAUDIO2_LOOP_INFINITE, 0.5f);
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnDestroy() {
		//BGM‚ÌƒXƒgƒbƒv
		auto BGM = App::GetApp()->GetXAudio2Manager();
		BGM->Stop(m_BGM);
	}

	//E½E½E½ß‚ÌdE½E½E½E½E½E½
	void GameStage::FrastTimeCount() {
		if (m_startTimeCount < m_maxStartTime) {
			auto delta = App::GetApp()->GetElapsedTime();
			m_startTimeCount += delta;
			return;
		}
		else {
			m_isFrastStop = false;
			GameManager::GetInstance().SetIsStopSpawner(false);
		}
	}

	void GameStage::GameClear() {
		bool isGameEnd = GameManager::GetInstance().GetIsGameEnd();
		if (isGameEnd) {
			SaveGameData();
			LoadResultStage();
		}
	}

	//ï¿½ï¿½ï¿½Uï¿½ï¿½ï¿½gï¿½Xï¿½eï¿½[ï¿½Wï¿½ÉˆÚ“ï¿½
	void GameStage::LoadResultStage() {
		bool isGameEnd = GameManager::GetInstance().GetIsGameEnd();
		if (isGameEnd) {
			SaveGameData();
			App::GetApp()->GetScene<Scene>()->LoadStage(L"ToResulfStage");
		}
	}

	int GameStage::SaveGameData() {
		int saveNum = GameManager::GetInstance().GetGameScore();
		int num = 1;
		int save = 9999999;
		ofstream fout;

		FILE* fp;

		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);

		char saveFileName[] = "../media/GameData/SaveData/file.otb";
		//ï¿½Jï¿½ï¿½ï¿½È‚ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ÍVï¿½Kï¿½ì¬
		fopen_s(&fp, saveFileName, "wb");

		for (int i = 0; i < 2; i++) {

			//ï¿½oï¿½Cï¿½iï¿½ï¿½ï¿½Ìï¿½ï¿½ï¿½ï¿½oï¿½ï¿½
			fwrite(&saveNum, sizeof(saveNum), 1, fp);
		}

		num = num * 4;
		//ï¿½ê•”ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½oï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ê‡ï¿½Égï¿½ï¿½
		fseek(fp, num , SEEK_SET);
		fwrite(&save, sizeof(save), 1, fp);
		
		fclose(fp);

		return 0;
	}


	//ï¿½oï¿½Cï¿½iï¿½ï¿½ï¿½fï¿½[ï¿½^ï¿½Ìƒï¿½ï¿½[ï¿½h
	int GameStage::ReadGameData() {
		char outfile[] = "file.otb";
		int saveNum = 0;
		ifstream fin(outfile, ios::in | ios::binary);

		//ï¿½Ç‚İï¿½ï¿½ß‚È‚ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½1ï¿½ï¿½Ô‚ï¿½
		if (!fin) {
			fin.close();
			return 1;
		}

		//ï¿½oï¿½Cï¿½iï¿½ï¿½ï¿½fï¿½[ï¿½^ï¿½Ì’ï¿½ï¿½gï¿½ï¿½ï¿½×‚Ä‚ï¿½mï¿½Fï¿½ï¿½ï¿½ï¿½
		while (!fin.eof()) {
			//ï¿½Ç‚İï¿½ï¿½İ‚ï¿½ï¿½ï¿½ï¿½fï¿½[ï¿½^ï¿½ÌˆÊ’uï¿½ï¿½wï¿½è‚·ï¿½ï¿½ê‡ï¿½Égï¿½ï¿½
			//int readBinaryItr = 0;
			//fin.seekg(readBinaryItr * sizeof(int));

			//ï¿½oï¿½Cï¿½iï¿½ï¿½ï¿½fï¿½[ï¿½^ï¿½ï¿½Ç‚İï¿½ï¿½ï¿½
			fin.read((char *)&saveNum, sizeof(int));
		}
		fin.close();
		return 0;
	}
}
//end basecross

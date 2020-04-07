/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 0.0f, -10.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);//座標
		PtrCamera->SetAt(at);//焦点
        PtrCamera->SetPers(false);//遠近法
        PtrCamera->SetWidth(10);//画面に表示する横幅のユニット数
        PtrCamera->SetHeight(10);//画面に表示する縦幅のユニット数
        PtrCamera->SetFovY(0.5f);//視野角
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::OnCreate() {
		try {
			//ビューとライトの作成
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
		//BGMのストップ
		auto BGM = App::GetApp()->GetXAudio2Manager();
		BGM->Stop(m_BGM);
	}

	//初めの硬直時間
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

	//リザルトステージに移動
	void GameStage::LoadResultStage() {
		bool isGameEnd = GameManager::GetInstance().GetIsGameEnd();
		if (isGameEnd) {
			App::GetApp()->GetScene<Scene>()->LoadStage(L"ToResulfStage");
		}
	}

	//ゲームのセーブ
	int GameStage::SaveGameData() {
		int saveNum = GameManager::GetInstance().GetGameScore();
		int num = 1;
		int save = 9999999;
		ofstream fout;

		FILE* fp;

		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);

		char saveFileName[] = "../media/GameData/SaveData/file.otb";
		//開けなかった時は新規作成
		fopen_s(&fp, saveFileName, "wb");

		for (int i = 0; i < 2; i++) {

			//バイナリの書き出し
			fwrite(&saveNum, sizeof(saveNum), 1, fp);
		}

		num = num * 4;
		//一部だけ書き出ししたい場合に使う
		fseek(fp, num , SEEK_SET);
		fwrite(&save, sizeof(save), 1, fp);
		
		fclose(fp);

		return 0;
	}

	//バイナリデータのロード
	int GameStage::ReadGameData() {
		char outfile[] = "file.otb";
		int saveNum = 0;
		ifstream fin(outfile, ios::in | ios::binary);

		//読み込めなかった時1を返す
		if (!fin) {
			fin.close();
			return 1;
		}

		//バイナリデータの中身すべてを確認する
		while (!fin.eof()) {
			//読み込みたいデータの位置を指定する場合に使う
			//int readBinaryItr = 0;
			//fin.seekg(readBinaryItr * sizeof(int));

			//バイナリデータを読み込む
			fin.read((char *)&saveNum, sizeof(int));
		}
		fin.close();
		return 0;
	}


}
//end basecross

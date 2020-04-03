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
		//BGMのストップ
		auto BGM = App::GetApp()->GetXAudio2Manager();
		BGM->Stop(m_BGM);
	}

	//・ｽ・ｽ・ｽﾟの硬・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
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

	//�ｿｽQ�ｿｽ[�ｿｽ�ｿｽ�ｿｽﾌセ�ｿｽ[�ｿｽu
	int GameStage::SaveGameData() {
		int saveNum = GameManager::GetInstance().GetGameScore();
		int num = 1;
		int save = 9999999;
		ofstream fout;

		FILE* fp;

		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);

		char saveFileName[] = "../media/GameData/SaveData/file.otb";
		//�ｿｽJ�ｿｽ�ｿｽ�ｿｽﾈゑｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾍ新�ｿｽK�ｿｽ�成
		fopen_s(&fp, saveFileName, "wb");

		for (int i = 0; i < 2; i++) {

			//�ｿｽo�ｿｽC�ｿｽi�ｿｽ�ｿｽ�ｿｽﾌ擾ｿｽ�ｿｽ�ｿｽ�ｿｽo�ｿｽ�ｿｽ
			fwrite(&saveNum, sizeof(saveNum), 1, fp);
		}

		num = num * 4;
		//�ｿｽ齦費ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽo�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ鼾��ｿｽﾉ使�ｿｽ�ｿｽ
		fseek(fp, num , SEEK_SET);
		fwrite(&save, sizeof(save), 1, fp);
		
		fclose(fp);

		return 0;
	}


	//�ｿｽo�ｿｽC�ｿｽi�ｿｽ�ｿｽ�ｿｽf�ｿｽ[�ｿｽ^�ｿｽﾌ��ｿｽ�ｿｽ[�ｿｽh
	int GameStage::ReadGameData() {
		char outfile[] = "file.otb";
		int saveNum = 0;
		ifstream fin(outfile, ios::in | ios::binary);

		//�ｿｽﾇみ搾ｿｽ�ｿｽﾟなゑｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ1�ｿｽ�ｿｽﾔゑｿｽ
		if (!fin) {
			fin.close();
			return 1;
		}

		//�ｿｽo�ｿｽC�ｿｽi�ｿｽ�ｿｽ�ｿｽf�ｿｽ[�ｿｽ^�ｿｽﾌ抵ｿｽ�ｿｽg�ｿｽ�ｿｽ�ｿｽﾗてゑｿｽm�ｿｽF�ｿｽ�ｿｽ�ｿｽ�ｿｽ
		while (!fin.eof()) {
			//�ｿｽﾇみ搾ｿｽ�ｿｽﾝゑｿｽ�ｿｽ�ｿｽ�ｿｽf�ｿｽ[�ｿｽ^�ｿｽﾌ位置�ｿｽ�ｿｽw�ｿｽ閧ｷ�ｿｽ�ｿｽ鼾��ｿｽﾉ使�ｿｽ�ｿｽ
			//int readBinaryItr = 0;
			//fin.seekg(readBinaryItr * sizeof(int));

			//�ｿｽo�ｿｽC�ｿｽi�ｿｽ�ｿｽ�ｿｽf�ｿｽ[�ｿｽ^�ｿｽ�ｿｽﾇみ搾ｿｽ�ｿｽ�ｿｽ
			fin.read((char *)&saveNum, sizeof(int));
		}
		fin.close();
		return 0;
	}
}
//end basecross

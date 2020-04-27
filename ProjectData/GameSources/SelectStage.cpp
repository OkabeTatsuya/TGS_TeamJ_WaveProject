/*!
@file SelectStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void SelectStage::CreateViewLight() {//リザルト画面
		const Vec3 eye(0.0f, 0.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();

		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);

		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();

		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}


	void SelectStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();

			CreateUI();

            AddGameObject<Fade>();
	
			LoadBinaryData();

			CreateBinaryData();
			//サウンドの追加
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

	//コントローラーの入力
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

	//Aボタンが押された時の処理
	void SelectStage::PushA() {
		GameManager::GetInstance().SetSelectStageNum(m_stageNum);
		PlaySE(L"se_maoudamashii_system37.wav", 0.5f);
		Sceneloader();
		m_isSelectStage = true;
	}

	//スティックが倒された時の処理
	void SelectStage::StickL() {
		auto controlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		float sticNum = 0.8f;
		auto time = App::GetApp()->GetElapsedTime();

		//スティックが最初に倒された時
		if (m_stickTime == 0.0f) {
			m_isChengeStage = true;
		}

		//スティックが長押しされた時
		if (m_stickTime > m_stickDelta) {
			m_isChengeStage = true;
			m_stickTime = 0.1f;
		}
		else {
			m_stickTime += time;
		}

		//最初に倒したとき、一定時間長押しされたときにステージを切り替える
		if (m_isChengeStage) {
			if (controlVec.fThumbLX >= sticNum) {
				m_stageNum++;
			}
			else if (controlVec.fThumbLX <= -sticNum) {
				m_stageNum--;
			}
			m_isChengeStage = false;

			//最小ステージ数を超えたら最大に移る
			if (m_stageNum < 0) {
				m_stageNum = (int)m_stageImageName.size() - 1;
			}
			//最大ステージ数を超えたら最小に移る
			if (m_stageNum > (int)m_stageImageName.size() - 1) {
				m_stageNum = 0;
			}

			//画像の差し替え
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

		//読み込めなかった時1を返す
		if (!fin) {
			fin.close();
			return 1;
		}

		//ステージの数だけセーブデータを作る
		if (m_stageImageName.size() > saveNum.size()) {
			for (int i = 0; i < m_stageImageName.size(); i++) {
				saveNum.push_back(0);
			}
		}

		int num = 0;
		//バイナリデータの中身すべてを確認する
		while (!fin.eof()) {
			//バイナリデータを読み込む
			fin.read((char *)&saveNum[num], sizeof(int));
			num++;
			GameManager::GetInstance().SetSaveScore(saveNum);
		}
		fin.close();
		return 0;
	}


	//保存データの数が合わなかった時に作り直す処理
	int SelectStage::CreateBinaryData() {
		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);

		wstring outfile = mediaDir + L"GameData/SaveData/file.otb";
		vector<int> saveNum;

		ofstream fout(outfile, ios::out | ios::binary | ios::trunc);
		ofstream fadd(outfile, ios::app | ios::binary);

		//読み込めなかった時1を返す
		if (!fout) {
			fout.close();
			fadd.close();
			return 1;
		}

		auto saveScore = GameManager::GetInstance().GetSaveScore();

		//サイズが合わなかった時
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


		
		//ステージのイメージ画像を取得
		m_stageImageUI = AddGameObject<ImageUI>(Vec3(0.0f), Vec3(300.0f, 300.0f, 1.0f), Vec2(0.0f, 0.0f), float(2.0f), m_stageImageName[m_stageNum]);
	}


	void SelectStage::ChengeStegeNum() {

	}

	//--------------------------------------------------------------------------------------
	//BGMを再生させる関数
	//--------------------------------------------------------------------------------------
	void SelectStage::PlayBGM(wstring soundName, float vol) {
		//BGM再生と音量調整
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(soundName, XAUDIO2_LOOP_INFINITE, vol);
	}

	//--------------------------------------------------------------------------------------
	//SEを再生させる関数
	//--------------------------------------------------------------------------------------
	void SelectStage::PlaySE(wstring soundName, float vol) {
		//BGM再生と音量調整
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_SE = XAPtr->Start(soundName, 0.0f, vol);
	}

	//ボタンを押すとシーン遷移する
	void SelectStage::Sceneloader() {
		AddGameObject<Fade>(m_stageName);
	}
}
//end basecross

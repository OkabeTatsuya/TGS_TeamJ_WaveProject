/*!
@file SelectStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <utility>

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
	
			CreateSaveData();

			//サウンドの追加
			PlayBGM(L"bgm_maoudamashii_acoustic13.wav", 0.5f);
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
			if (controlVec.wPressedButtons & XINPUT_GAMEPAD_B) {
				PushB();
			}
			if (controlVec.wPressedButtons & XINPUT_GAMEPAD_X) {
				GameManager::GetInstance().SetClearStageNum(3);
				PlaySE(L"se_maoudamashii_system37.wav", 0.5f);
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

	void SelectStage::PushB() {
		PlaySE(L"se_maoudamashii_system20.wav", 0.5f);
		AddGameObject<Fade>(L"ToTitleStage");
		m_isSelectStage = true;
	}


	//スティックが倒された時の処理
	void SelectStage::StickL() {
		auto &gameManager = GameManager::GetInstance();
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
				m_stageNum = gameManager.GetClearStageNum();
			}
			//最大ステージ数を超えたら最小に移る
			if (m_stageNum > gameManager.GetClearStageNum()) {
				m_stageNum = 0;
			}

			//画像の差し替え
			m_stageImageUI->ChangeImage(m_stageImageName[m_stageNum]);
			m_stageNumUI->ChangeImage(m_stageNumImageName[m_stageNum]);
			GameManager::GetInstance().DrawClearScore(m_stageNum);
			PlaySE(L"se_maoudamashii_system37.wav", 0.5f);
		}

	}


	void SelectStage::CreateSaveData() {
		auto saveScore = GameManager::GetInstance().GetSaveScore();
		//サイズが合わなかった時
		if (saveScore.size() != m_stageImageName.size()) {
			//ステージの数だけセーブデータを作る
			if (m_stageImageName.size() > saveScore.size()) {
				for (int i = 0; i < m_stageImageName.size(); i++) {
					saveScore.push_back(0);
				}
				GameManager::GetInstance().SetSaveScore(saveScore);
			}
		}
	}

	void SelectStage::CreateUI() {
		//背景
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(1300.0f, 800.0f, 1.0f), Vec2(0.0f, 0.0f), float(1.0f), L"SelectBG.png");
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(1280.0f, 800.0f, 1.0f), Vec2(0.0f, -300.0f), float(2.0f), L"ScoreBG.png"); 

		AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(80.0f, 80.0f, 1.0f), Vec2(200.0f, -300.0f), float(5.0f), L"Number.png", 7, false);
		GameManager::GetInstance().DrawClearScore(m_stageNum);

		AddGameObject<FlashingUI>(Vec3(0.0f), Vec3(128.0f, 128.0f, 1.0f), Vec2(550.0f, -00.0f), float(4.0f), L"RightArrow.png", 3.0f);
		AddGameObject<FlashingUI>(Vec3(0.0f), Vec3(128.0f, 128.0f, 1.0f), Vec2(-550.0f, -00.0f), float(4.0f), L"LeftArrow.png", 3.0f);

		//AddGameObject<ImageUI>(Vec3(0.0f), Vec3(512.0f, 256.0f, 1.0f), Vec2(0.0f, 300.0f), float(4.0f), L"StageSelect.png");
		//AddGameObject<ImageUI>(Vec3(0.0f), Vec3(512.0f, 256.0f, 1.0f), Vec2(-220.0f, -300.0f), float(4.0f), L"ClearScoreUI.png");

		//ステージのイメージ画像を取得
		m_stageImageUI = AddGameObject<ImageUI>(Vec3(0.0f), Vec3(650.0f, 400.0f, 1.0f), Vec2(0.0f, -00.0f), float(4.0f), m_stageImageName[m_stageNum]);
		m_stageNumUI = AddGameObject<ImageUI>(Vec3(0.0f), Vec3(512.0f, 256.0f, 1.0f), Vec2(0.0f, 250.0f), float(4.0f), m_stageNumImageName[m_stageNum]);
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

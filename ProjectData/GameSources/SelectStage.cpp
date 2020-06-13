/*!
@file SelectStage.cpp
@brief ƒQ[ƒ€ƒXƒe[ƒWÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <utility>

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ƒQ[ƒ€ƒXƒe[ƒWƒNƒ‰ƒXÀ‘Ì
	//--------------------------------------------------------------------------------------
	void SelectStage::CreateViewLight() {//ƒŠƒUƒ‹ƒg‰æ–Ê
		const Vec3 eye(0.0f, 0.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();

		//ƒrƒ…[‚ÌƒJƒƒ‰‚Ìİ’è
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);

		//ƒ}ƒ‹ƒ`ƒ‰ƒCƒg‚Ìì¬
		auto PtrMultiLight = CreateLight<MultiLight>();

		//ƒfƒtƒHƒ‹ƒg‚Ìƒ‰ƒCƒeƒBƒ“ƒO‚ğw’è
		PtrMultiLight->SetDefaultLighting();
	}


	void SelectStage::OnCreate() {
		try {
			//ƒrƒ…[‚Æƒ‰ƒCƒg‚Ìì¬
			CreateViewLight();

			CreateUI();
	
			CreateSaveData();

			//ƒTƒEƒ“ƒh‚Ì’Ç‰Á
			PlayBGM(L"bgm_maoudamashii_acoustic13.wav", 0.5f);

			PlaySE(L"Voice1_5.wav", 1.0f);
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
		auto AudioManager = App::GetApp()->GetXAudio2Manager();
		//ï¿½Tï¿½Eï¿½ï¿½ï¿½hï¿½ï¿½~ï¿½ß‚ï¿½
		AudioManager->Stop(m_SE);
		AudioManager->Stop(m_voiceSE);
		AudioManager->Stop(m_BGM);
	}

	//ƒRƒ“ƒgƒ[ƒ‰[‚Ì“ü—Í
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
			//if (controlVec.wPressedButtons & XINPUT_GAMEPAD_X) {
			//	GameManager::GetInstance().SetClearStageNum(3);
			//	PlaySE(L"se_maoudamashii_system37.wav", 0.5f);
			//}
		}
	}

	//Aƒ{ƒ^ƒ“‚ª‰Ÿ‚³‚ê‚½‚Ìˆ—
	void SelectStage::PushA() {
		auto& gameManager = GameManager::GetInstance();

		if (m_stageNum <= gameManager.GetClearStageNum()) {
			gameManager.SetSelectStageNum(m_stageNum);
			PlaySE(L"se_maoudamashii_system37.wav", 0.5f);
			PlayeVoice(L"Voice1_6.wav", 1.0f);
			Sceneloader();
			m_isSelectStage = true;
		}
		else {
			PlaySE(L"se_maoudamashii_onepoint14.wav", 0.5f);
		}
	}

	void SelectStage::PushB() {
		PlaySE(L"se_maoudamashii_system20.wav", 0.5f);
		AddGameObject<Fade>(L"ToTitleStage");
		m_isSelectStage = true;
	}


	//ƒXƒeƒBƒbƒN‚ª“|‚³‚ê‚½‚Ìˆ—
	void SelectStage::StickL() {
		auto &gameManager = GameManager::GetInstance();
		auto controlVec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		float sticNum = 0.8f;
		auto time = App::GetApp()->GetElapsedTime();

		//ƒXƒeƒBƒbƒN‚ªÅ‰‚É“|‚³‚ê‚½
		if (m_stickTime == 0.0f) {
			m_isChengeStage = true;
		}

		//ƒXƒeƒBƒbƒN‚ª’·‰Ÿ‚µ‚³‚ê‚½
		if (m_stickTime > m_stickDelta) {
			m_isChengeStage = true;
			m_stickTime = 0.1f;
		}
		else {
			m_stickTime += time;
		}

		//Å‰‚É“|‚µ‚½‚Æ‚«Aˆê’èŠÔ’·‰Ÿ‚µ‚³‚ê‚½‚Æ‚«‚ÉƒXƒe[ƒW‚ğØ‚è‘Ö‚¦‚é
		if (m_isChengeStage) {
			if (controlVec.fThumbLX >= sticNum) {
				m_stageNum++;
			}
			else if (controlVec.fThumbLX <= -sticNum) {
				m_stageNum--;
			}
			m_isChengeStage = false;

			//Å¬ƒXƒe[ƒW”‚ğ’´‚¦‚½‚çÅ‘å‚ÉˆÚ‚é
			if (m_stageNum < 0) {
				m_stageNum = m_stageImageName.size() - 1;
			}
			//Å‘åƒXƒe[ƒW”‚ğ’´‚¦‚½‚çÅ¬‚ÉˆÚ‚é
			if (m_stageNum > m_stageImageName.size() - 1) {
				m_stageNum = 0;
			}

			if (m_stageNum <= gameManager.GetClearStageNum()) {
				m_stageLockUI->SetDrawActive(false);
				m_stageIconLockUI->SetDrawActive(false);
			}
			else {
				m_stageLockUI->SetDrawActive(true);
				m_stageIconLockUI->SetDrawActive(true);
			}

			//‰æ‘œ‚Ì·‚µ‘Ö‚¦
			m_stageImageUI->ChangeImage(m_stageImageName[m_stageNum]);
			m_stageNumUI->ChangeImage(m_stageNumImageName[m_stageNum]);
			GameManager::GetInstance().DrawClearScore(m_stageNum);
			PlaySE(L"se_maoudamashii_system37.wav", 0.5f);
		}
	}


	void SelectStage::CreateSaveData() {
		auto saveScore = GameManager::GetInstance().GetSaveScore();
		//ƒTƒCƒY‚ª‡‚í‚È‚©‚Á‚½
		if (saveScore.size() != m_stageImageName.size()) {
			//ƒXƒe[ƒW‚Ì”‚¾‚¯ƒZ[ƒuƒf[ƒ^‚ğì‚é
			if (m_stageImageName.size() > saveScore.size()) {
				for (int i = 0; i < m_stageImageName.size(); i++) {
					saveScore.push_back(0);
				}
				GameManager::GetInstance().SetSaveScore(saveScore);
			}
		}
	}

	void SelectStage::CreateUI() {
		//”wŒi
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(1300.0f, 800.0f, 1.0f), Vec2(0.0f, 0.0f), float(1.0f), L"SelectBG.png");
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(1280.0f, 800.0f, 1.0f), Vec2(0.0f, -300.0f), float(2.0f), L"ScoreBG.png"); 

		AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(80.0f, 80.0f, 1.0f), Vec2(120.0f, -300.0f), float(5.0f), L"Number.png", 7, false,true);
		GameManager::GetInstance().DrawClearScore(m_stageNum);

		AddGameObject<FlashingUI>(Vec3(0.0f), Vec3(128.0f, 128.0f, 1.0f), Vec2(550.0f, -00.0f), float(4.0f), L"RightArrow.png", 3.0f);
		AddGameObject<FlashingUI>(Vec3(0.0f), Vec3(128.0f, 128.0f, 1.0f), Vec2(-550.0f, -00.0f), float(4.0f), L"LeftArrow.png", 3.0f);

		//AddGameObject<ImageUI>(Vec3(0.0f), Vec3(512.0f, 256.0f, 1.0f), Vec2(0.0f, 300.0f), float(4.0f), L"StageSelect.png");
		//AddGameObject<ImageUI>(Vec3(0.0f), Vec3(512.0f, 256.0f, 1.0f), Vec2(-220.0f, -300.0f), float(4.0f), L"ClearScoreUI.png");

		//ƒXƒe[ƒW‚ÌƒCƒ[ƒW‰æ‘œ‚ğæ“¾
		m_stageImageUI = AddGameObject<ImageUI>(Vec3(0.0f), Vec3(640.0f, 400.0f, 1.0f), Vec2(0.0f, -15.0f), float(4.0f), m_stageImageName[m_stageNum]);
		m_stageNumUI = AddGameObject<ImageUI>(Vec3(0.0f), Vec3(512.0f, 256.0f, 1.0f), Vec2(0.0f, 250.0f), float(4.0f), m_stageNumImageName[m_stageNum]);
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(1350.0f, 900.0f, 1.0f), Vec2(-5.0f, 40.0f), float(3.0f), L"StageBG.png");

		//ƒXƒe[ƒWƒCƒ[ƒW‚ğ•‚­‚Ú‚©‚·UI
		m_stageLockUI = AddGameObject<ImageUI>(Vec3(0.0f), Vec3(640.0f, 400.0f, 1.0f), Vec2(0.0f, -15.0f), float(4.0f), L"SpecialJumpBG.png");
		m_stageLockUI->SetDrawActive(false);
		auto drawPtr = m_stageLockUI->GetComponent<PCTSpriteDraw>();
		drawPtr->SetDiffuse(Col4(1.0f,1.0f,1.0f,0.5f));

		//“ì‹ùUI
		m_stageIconLockUI = AddGameObject<ImageUI>(Vec3(0.0f), Vec3(256.0f, 256.0f, 1.0f), Vec2(0.0f, -15.0f), float(5.0f), L"Lock.png");
		m_stageIconLockUI->SetDrawActive(false);

	}

	//--------------------------------------------------------------------------------------
	//BGM‚ğÄ¶‚³‚¹‚éŠÖ”
	//--------------------------------------------------------------------------------------
	void SelectStage::PlayBGM(wstring soundName, float vol) {
		//BGMÄ¶‚Æ‰¹—Ê’²®
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(soundName, XAUDIO2_LOOP_INFINITE, vol);
	}

	//--------------------------------------------------------------------------------------
	//SE‚ğÄ¶‚³‚¹‚éŠÖ”
	//--------------------------------------------------------------------------------------
	void SelectStage::PlaySE(wstring soundName, float vol) {
		//SEÄ¶‚Æ‰¹—Ê’²®
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_SE = XAPtr->Start(soundName, 0, vol);
	}

	void SelectStage::PlayeVoice(wstring soundName, float vol) {
		//SEÄ¶‚Æ‰¹—Ê’²®
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_voiceSE = XAPtr->Start(soundName, 0, vol);
	}

	//ƒ{ƒ^ƒ“‚ğ‰Ÿ‚·‚ÆƒV[ƒ“‘JˆÚ‚·‚é
	void SelectStage::Sceneloader() {
		AddGameObject<Fade>(m_stageName);
	}
}
//end basecross

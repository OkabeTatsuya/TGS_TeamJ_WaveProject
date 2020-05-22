/*!
@file SelectStage.cpp
@brief ƒQ[ƒ€ƒXƒe[ƒWÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

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

            AddGameObject<Fade>();
	
			CreateBinaryData();
			//ƒTƒEƒ“ƒh‚Ì’Ç‰Á
			//PlayBGM(L"SampleBGM.wav", 0.5f);

			//LoadBinaryData();

			//ï¿½Tï¿½Eï¿½ï¿½ï¿½hï¿½Ì’Ç‰ï¿½
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
		}
	}

	//Aƒ{ƒ^ƒ“‚ª‰Ÿ‚³‚ê‚½‚Ìˆ—
	void SelectStage::PushA() {
		GameManager::GetInstance().SetSelectStageNum(m_stageNum);
		PlaySE(L"se_maoudamashii_system37.wav", 0.5f);
		Sceneloader();
		m_isSelectStage = true;
	}

	//ƒXƒeƒBƒbƒN‚ª“|‚³‚ê‚½‚Ìˆ—
	void SelectStage::StickL() {
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
				m_stageNum = (int)m_stageImageName.size() - 1;
			}
			//Å‘åƒXƒe[ƒW”‚ğ’´‚¦‚½‚çÅ¬‚ÉˆÚ‚é
			if (m_stageNum > (int)m_stageImageName.size() - 1) {
				m_stageNum = 0;
			}

			//‰æ‘œ‚Ì·‚µ‘Ö‚¦
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

		//“Ç‚İ‚ß‚È‚©‚Á‚½1‚ğ•Ô‚·
		if (!fin) {
			fin.close();
			return 1;
		}

		//ƒXƒe[ƒW‚Ì”‚¾‚¯ƒZ[ƒuƒf[ƒ^‚ğì‚é
		if (m_stageImageName.size() > saveNum.size()) {
			for (int i = 0; i < m_stageImageName.size(); i++) {
				saveNum.push_back(0);
			}
		}

		int num = 0;
		//ƒoƒCƒiƒŠƒf[ƒ^‚Ì’†g‚·‚×‚Ä‚ğŠm”F‚·‚é
		while (!fin.eof()) {
			//ƒoƒCƒiƒŠƒf[ƒ^‚ğ“Ç‚İ‚Ş
			fin.read((char *)&saveNum[num], sizeof(int));
			num++;
			GameManager::GetInstance().SetSaveScore(saveNum);
		}
		fin.close();
		return 0;
	}


	//•Û‘¶ƒf[ƒ^‚Ì”‚ª‡‚í‚È‚©‚Á‚½‚Éì‚è’¼‚·ˆ—
	int SelectStage::CreateBinaryData() {
		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);

		wstring outfile = mediaDir + L"GameData/SaveData/file.otb";
		vector<int> saveNum;

		ofstream fout(outfile, ios::out | ios::binary | ios::trunc);
		ofstream fadd(outfile, ios::app | ios::binary);

		//“Ç‚İ‚ß‚È‚©‚Á‚½1‚ğ•Ô‚·
		if (!fout) {
			fout.close();
			fadd.close();
			return 1;
		}

		auto saveScore = GameManager::GetInstance().GetSaveScore();

		//ƒTƒCƒY‚ª‡‚í‚È‚©‚Á‚½
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


		
		//ƒXƒe[ƒW‚ÌƒCƒ[ƒW‰æ‘œ‚ğæ“¾
		m_stageImageUI = AddGameObject<ImageUI>(Vec3(0.0f), Vec3(300.0f, 300.0f, 1.0f), Vec2(0.0f, 0.0f), float(2.0f), m_stageImageName[m_stageNum]);
	}


	void SelectStage::ChengeStegeNum() {

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
		//BGMÄ¶‚Æ‰¹—Ê’²®
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_SE = XAPtr->Start(soundName, 0.0f, vol);
	}

	//ƒ{ƒ^ƒ“‚ğ‰Ÿ‚·‚ÆƒV[ƒ“‘JˆÚ‚·‚é
	void SelectStage::Sceneloader() {
		AddGameObject<Fade>(m_stageName);
	}
}
//end basecross

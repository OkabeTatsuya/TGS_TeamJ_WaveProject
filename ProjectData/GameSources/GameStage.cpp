/*!
@file GameStage.cpp
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

			//ƒGƒtƒFƒNƒg‚ğì¬
			m_efkInterface = ObjectFactory::Create<EfkInterface>();
			CreateEfkEffect();

			//’l‚Ì‰Šú‰»
			GameManager::GetInstance().ResetGame();
			GameManager::GetInstance().SetMaxSpecialCount(m_maxSpecialCount[m_specialJumpCount]);

            AddGameObject<Fade>();

			//UIì¬
			CreateAnimUI();
			CreateGoalUI();
			CreateGameUI();

			//ƒIƒuƒWƒFƒNƒg¶¬
			CreateGenerator();

			m_playerObj = AddGameObject<Player>(Vec3(0, 0, 0), Vec3(1.0f, 1.0f, 1), Vec3(-2.0f, -2, -7.0f), 7);
            m_playerObjTrans = m_playerObj->GetComponent<Transform>();
			m_playerIconTrans = m_playerIconUI->GetComponent<Transform>();
			AddGameObject<SeaCollision>(Vec3(0, 0, 0), Vec3(5, 0.5f, 1), Vec3(-2.5, -4.0, -7.0));

			//ƒXƒRƒAUI
			m_scoreCountUI = AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(50.0f, 50.0f, 1.0f), Vec2(350.0f, 350.f), float(5.0f), L"Number.png", 7, false);
			AddGameObject<ImageUI>(Vec3(0.0f), Vec3(200.0f, 50.0f, 1.0f), Vec2(30.0f, 350.f), float(5.0f), L"Score2.png");
 

			m_fadeInUI = AddGameObject<Fade>(L"ToResulfStage");
			m_fadeInUI->SetUpdateActive(false);

			auto audioManager = App::GetApp()->GetXAudio2Manager();
			m_BGM = audioManager->Start(L"game_maoudamashii_5_town05.wav", XAUDIO2_LOOP_INFINITE, 0.0f);

			for (int i = 0; i < 2; i++) {
				m_SE.push_back(nullptr);
			}
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate() {
		m_efkInterface->OnUpdate();
		FrastTimeCount();
		GameClear();
		UpdateScoreUI();
		auto BGM = App::GetApp()->GetXAudio2Manager();
		BGM->MyFadeIn(m_BGM, 0.5f, 2.0f);
		SpecialJumpController();
		Hundler();
		MovePlayerIcon();
		m_playerIconTrans->GetPosition().x;
	}

	void GameStage::OnDestroy() {
		//BGM‚ÌƒXƒgƒbƒv
		auto audioManager = App::GetApp()->GetXAudio2Manager();
		audioManager->Stop(m_BGM);

		for each (auto se in m_SE)
		{
			audioManager->Stop(se);
		}	
	}

	void GameStage::OnDraw() {
		auto& camera = GetView()->GetTargetCamera();
		m_efkInterface->SetViewProj(camera->GetViewMatrix(), camera->GetProjMatrix());
		m_efkInterface->OnDraw();
	}

	void GameStage::CreateGameUI() {
		//ƒAƒCƒeƒ€‚Ìƒ|ƒWƒVƒ‡ƒ“
		Vec2 baseItemPos = Vec2(-550.0f, 320.0f);
		vector<Vec2> itemUIPos = { 
			baseItemPos,
			Vec2(baseItemPos.x + 100.0f, baseItemPos.y),
			Vec2(baseItemPos.x + 150.0f, baseItemPos.y),
			Vec2(baseItemPos.x + 230.0f, baseItemPos.y)
		};

		//ƒ}ƒbƒv‚Ìƒ|ƒWƒVƒ‡ƒ“
		m_baseMapUIPos = Vec2(-380.0f, 360.0f);
		m_mapUIPos = {
			m_baseMapUIPos,
			Vec2(m_baseMapUIPos.x +  255.0f, m_baseMapUIPos.y + -5.0f),
			Vec2(m_baseMapUIPos.x + -245.0f, m_baseMapUIPos.y + -5.0f),
		};

		float baseCommandUIPosY = 45;
		Vec2 baseCommandUIPos = Vec2(450.0f, 350.0f);
		vector<Vec2> commandUIPos = {
			Vec2(baseCommandUIPos.x + 0.0f, baseCommandUIPos.y + -baseCommandUIPosY * 0),
			Vec2(baseCommandUIPos.x + 0.0f, baseCommandUIPos.y + -baseCommandUIPosY * 1),
			Vec2(baseCommandUIPos.x + 0.0f, baseCommandUIPos.y + -baseCommandUIPosY * 2),
			Vec2(baseCommandUIPos.x + 0.0f, baseCommandUIPos.y + -baseCommandUIPosY * 3)
		};

		vector<Vec2> commandIconUIPos = {
			Vec2(baseCommandUIPos.x + 120.0f, baseCommandUIPos.y + -baseCommandUIPosY * 0),
			Vec2(baseCommandUIPos.x + 120.0f, baseCommandUIPos.y + -baseCommandUIPosY * 1),
			Vec2(baseCommandUIPos.x + 120.0f, baseCommandUIPos.y + -baseCommandUIPosY * 2),
			Vec2(baseCommandUIPos.x + 120.0f, baseCommandUIPos.y + -baseCommandUIPosY * 3)
		};

		vector<wstring> commandImage = {
			L"JunpUI.png",
			L"CommandUI1.png",
			L"CommandUI2.png",
			L"CommandUI3.png"
		};

		Vec3 itemScale = Vec3(40.0f, 40.0f, 1.0f);
		AddGameObject<ImageUI>(Vec3(0.0f), itemScale, baseItemPos, float(5.0f), L"Coin.png");
		//ƒAƒCƒeƒ€ãŒÀUI
		m_itemCountUI = AddGameObject<ScoreUIPanel>(Vec3(0.0f), itemScale, itemUIPos[3], float(5.0f), L"GoldenNumbers.png", 2, false);
		//•`‰æ‚·‚é”š
		auto drawNum = GameManager::GetInstance().GetMaxSpecialCount();
		m_maxItemCountUI->ScoreDraw(drawNum);

		AddGameObject<ImageUI>(Vec3(0.0f), itemScale, itemUIPos[2], float(5.0f), L"Slash.png");

		//ƒAƒCƒeƒ€ƒJƒEƒ“ƒgUI
		m_itemCountUI = AddGameObject<ScoreUIPanel>(Vec3(0.0f), itemScale, itemUIPos[1], float(5.0f), L"GoldenNumbers.png", 2, false);
		drawNum = GameManager::GetInstance().GetSpecialCount();
		m_itemCountUI->ScoreDraw(drawNum);

		//ƒ}ƒbƒvUI
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(512.0f, 125.0f, 1.0f), m_mapUIPos[0], float(5.0f), L"MapStage.png");
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(30.0f, 30.0f, 1.0f), m_mapUIPos[1], float(6.0f), L"MapGoal.png");
		m_playerIconUI = AddGameObject<ImageUI>(Vec3(0.0f), Vec3(20.0f, 20.0f, 1.0f), m_mapUIPos[2], float(7.0f), L"MapPlayer.png");

		//ï¿½Jï¿½bï¿½gï¿½Cï¿½ï¿½UI
		m_cutInUI = AddGameObject<CutInUI>(Vec3(0.0f), Vec3(1300.0f, 400.0f, 1.0f), Vec2(0.0f), float(5.0f), L"CutIn.png");

		Vec2 baseCommandIconScl = Vec2(4.0f, 2.0f);
		float magnification = 30;
		float magnification1 = 25;

		vector<Vec3> commandScl = {
			Vec3(48.0f, 48.0f, 1.0f),
			Vec3(baseCommandIconScl.x * magnification, baseCommandIconScl.y * magnification, 1.0f),
			Vec3(baseCommandIconScl.x * magnification, baseCommandIconScl.y * magnification, 1.0f),
			Vec3(baseCommandIconScl.x * magnification, baseCommandIconScl.y * magnification, 1.0f)
		};

		vector<Vec3> commandIconScl = {
			Vec3(48.0f, 48.0f, 1.0f),
			Vec3(baseCommandIconScl.x * magnification1, baseCommandIconScl.y * magnification1, 1.0f),
			Vec3(baseCommandIconScl.x * magnification1, baseCommandIconScl.y * magnification1, 1.0f),
			Vec3(baseCommandIconScl.x * magnification1, baseCommandIconScl.y * magnification1, 1.0f)
		};

		//ƒRƒ}ƒ“ƒhUI
		for (int i = 0; i < commandUIPos.size(); i++) {
			AddGameObject<ImageUI>(Vec3(0.0f), commandScl[1], commandUIPos[i], float(6.0f), commandImage[i]);
		}

		//ƒAƒCƒRƒ“UI
		AddGameObject<ImageUI>(Vec3(0.0f), commandIconScl[0], commandIconUIPos[0], float(5.0f), L"ABttun.png");
		AddGameObject<ImageUI>(Vec3(0.0f), commandIconScl[1], commandIconUIPos[1], float(6.0f), L"Icon1.png");
		AddGameObject<ImageUI>(Vec3(0.0f), commandIconScl[2], commandIconUIPos[2], float(6.0f), L"Icon2.png");
		AddGameObject<ImageUI>(Vec3(0.0f), commandIconScl[3], commandIconUIPos[3], float(6.0f), L"Icon3.png");

	};

	//ƒAƒjƒ[ƒVƒ‡ƒ“‚·‚éUI‚ğì¬
	void GameStage::CreateAnimUI() {
		St_AnimUI statUIState1 = {
			//‰Šúƒgƒ‰ƒ“ƒXƒtƒH[ƒ€
			Vec2(1000.0f,50.0f),Vec3(0.0f),m_textScale,
			//ƒAƒjƒ[ƒVƒ‡ƒ“Œã‚Ìƒgƒ‰ƒ“ƒXƒtƒH[ƒ€
			Vec2(0.0f,50.0f),Vec3(0.0f),m_textScale,
			//¶‚©‚ç@ƒŒƒCƒ„[AƒAƒjƒ[ƒVƒ‡ƒ“ŠJnŠÔAI—¹ŠÔ
			8.0f,0.0f,0.5f,
			//ƒAƒjƒ[ƒVƒ‡ƒ“I—¹Œã‚Ìˆ—
			AnimType::Delete
		};
		St_AnimUI statUIState2 = {
			Vec2(1000.0f,-50.0f),Vec3(0.0f),m_textScale,
			Vec2(0.0f,-50.0f),Vec3(0.0f),m_textScale,
			8.0f,2.0f,2.5f,AnimType::Delete
		};
		
		vector<St_AnimUI> animUIState{
			statUIState1,
			statUIState2
		};

		//’£‚è•t‚¯‚éƒeƒNƒXƒ`ƒƒ
		vector<wstring> texter {
			L"Ready.png",
			L"Go.png"
		};

		vector<wstring> se{
			L"Voice1_7.wav",
			L"Voice1_8.wav"
		};

		for (int i = 0; i < animUIState.size(); i++) {
			m_startUI.push_back(AddGameObject<AnimationUI>(animUIState[i], texter[i], m_maxStartTime, se[i]));
			m_startUI[i]->SetIsStartAnim(true);
		}

		AddGameObject<SpecialJumpUI>(Vec3(0.0f), Vec3(1400, 800, 0), Vec2(0.0f), float(4.0f), L"SpecialJumpBG.png");
	}

	//ƒS[ƒ‹‚µ‚½‚ÌƒAƒjƒ[ƒVƒ‡ƒ“UI‚ğì¬
	void GameStage::CreateGoalUI() {
		St_AnimUI GoalUIState = {
			Vec2(1000.0f,50.0f),Vec3(0.0f),m_textScale,
			Vec2(0.0f,50.0f),Vec3(0.0f),m_textScale,
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
		BackGroundState SkyState =		{ Vec3(0.0f), Vec3(-10.0f,  0.0f,  0.0f),	Vec2(5.0f, 5.0f), 0,L"Sky.png", -10.0f, 0.3f };
		BackGroundState SeaBGState =	{ Vec3(0.0f), Vec3(-10.0f,  0.0f, -3.0f),	Vec2(5.0f, 5.0f), 3,L"Ocean.png", -10.0f, 0.3f};
		BackGroundState SeaState =		{ Vec3(0.0f), Vec3(-10.0f, -0.12f, -8.0),	Vec2(5.0f, 5.0f), 8,L"Sea.png", -10.0f, 1.1f };
		BackGroundState CloudState =	{ Vec3(0.0f), Vec3(-10.0f,  0.0f, -1.0),	Vec2(5.0f, 5.0f), 1,L"cloud.png", -10.0f, 0.05f };
		BackGroundState IslandState =	{ Vec3(0.0f), Vec3(-10.0f, -0.3f, -2.0),	Vec2(1.5f, 1.5f), 2,L"Island.png", -10.0f, 0.2f };

		AddGameObject<BGGenerator>(SkyState);
		AddGameObject<BGGenerator>(SeaBGState);
		AddGameObject<BGGenerator>(SeaState);
		AddGameObject<BGGenerator>(CloudState);
		AddGameObject<RandomGenerator>(IslandState, 10.0f, 15);

		m_waveSpawner = AddGameObject<WaveSpawner>();
		AddGameObject<ItemGenerator>();
		AddGameObject<GoalGenerator>();
	}

	void GameStage::CreateEfkEffect() {
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);

		for (int i = 0; i < m_effectNames.EffectName.size(); i++) {
			wstring effectStr = dataDir + L"Effect\\" + m_effectNames.EffectName[i];
			m_efkEffect.push_back(ObjectFactory::Create<EfkEffect>(m_efkInterface, effectStr));
		}
	}

	void GameStage::UpdateScoreUI() {
		auto drawNum = GameManager::GetInstance().GetSpecialCount();
		m_itemCountUI->ScoreDraw(drawNum);

		drawNum = GameManager::GetInstance().GetMaxSpecialCount();
		m_maxItemCountUI->ScoreDraw(drawNum);

		drawNum = GameManager::GetInstance().GetGameScore();
		m_scoreCountUI->ScoreDraw(drawNum);

	}

	void GameStage::Hundler() {
		//ƒRƒ“ƒgƒ[ƒ‰[‚Ìæ“¾
		auto cntVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntVec[0].bConnected)
		{
			m_isReset = cntVec[0].wPressedButtons & XINPUT_GAMEPAD_LEFT_THUMB &&
				cntVec[0].wPressedButtons & XINPUT_GAMEPAD_RIGHT_THUMB;
			if (m_isReset)
			{
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
			}
			//ï¿½ï¿½ï¿½Xï¿½^ï¿½[ï¿½g
			if (cntVec[0].wPressedButtons & XINPUT_GAMEPAD_START) 
			{
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
			}
		}
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

		GameEnd();

		if (isGameEnd && m_loadStageTimeCount == 0) {
			int stageNum = gameManager.GetSelectStageNum();
			int gameScore = gameManager.GetGameScore();

			if (gameManager.GetGameClearScore(stageNum) < gameScore) {
				gameManager.SetIsGameClear(true);
				PlaySE(EN_SoundTypeSE::en_SystemSE, m_seStr[EN_SE::en_GameClearSE], 0.9f);
				PlaySE(EN_SoundTypeSE::en_VoiceSE, m_seStr[EN_SE::en_GameClearVoice], 1.0f);
			}
			else {
				gameManager.SetIsGameClear(false);
				PlaySE(EN_SoundTypeSE::en_SystemSE, m_seStr[EN_SE::en_GameOverSE], 0.9f);
				PlaySE(EN_SoundTypeSE::en_VoiceSE, m_seStr[EN_SE::en_GameOverVoice], 1.0f);
			}
		}

		if (isGameEnd && !m_isLoadStage) {
			auto time = App::GetApp()->GetElapsedTime();
			m_loadStageTimeCount += time;
		}

		if (!m_isLoadStage && m_loadStageTimeCount > m_maxLoadStageTime) {
			int gameScore = GameManager::GetInstance().GetGameScore();

			auto maxStageNum = gameManager.GetSaveScore().size();
			auto unlockStageNum = gameManager.GetClearStageNum() + 1;

			if (gameManager.GetIsGameClear() && unlockStageNum < maxStageNum) {
				gameManager.SetClearStageNum(unlockStageNum);
			}

			SaveGameData();
			LoadResultStage();
			//m_loadStageTimeCount = 0;
			m_isLoadStage = true;
		}
	}

	void GameStage::GameEnd() {
		auto playerPosX = m_playerObjTrans->GetPosition().x;
		auto &gameManager = GameManager::GetInstance();
		if (playerPosX < m_gameOverPos) {
			gameManager.SetIsGameEnd(true);
			m_gameOver = true;
		}

		if (gameManager.GetIsGameEnd()) {
			if (m_gameOver) {
				m_goalUI->SetIsStartAnim(false);
			}
			else {
				m_goalUI->SetIsStartAnim(true);
			}
		}
	}

	void GameStage::SpecialJumpController() {
		//ƒWƒƒƒ“ƒvƒtƒ‰ƒO‚ª—§‚Á‚Ä‚¢‚½‚çƒXƒs[ƒh‚ğ‰º‚°‚é
		auto specialJumpFlag = GameManager::GetInstance().GetIsSpecialJump();

		auto specialJumpTimeFlag = GameManager::GetInstance().GetIsSpecialTime();

		if (!specialJumpTimeFlag) {
			m_playSpecialSE = false;
		}

		if (specialJumpTimeFlag && !m_playSpecialSE) {
			m_cutInUI->ResetState();
			PlaySE(EN_SoundTypeSE::en_SystemSE, m_seStr[EN_SE::en_SpecialTimeSE], 0.9f);
			PlaySE(EN_SoundTypeSE::en_VoiceSE, m_seStr[EN_SE::en_SpecialTImeVoice1], 1.0f);
			m_playSpecialSE = true;
		}

		if (specialJumpFlag) {
			GameManager::GetInstance().SetGameSpeed(m_SpecialJumpSpeed);

			float maxCount = 0.1f;
			float delta = App::GetApp()->GetElapsedTime();
			m_specialJumpTimer += delta;
			if (m_specialJumpTimer > maxCount) {
				m_specialJumpTimer = 0.0f;
				GameManager::GetInstance().SetGameSpeed(m_saveGameSpeed);
				GameManager::GetInstance().SetIsSpecialTime(false);
				GameManager::GetInstance().SetIsSpecialJump(false);
			}
		}
		else {
			m_saveGameSpeed = GameManager::GetInstance().GetGameSpeed();
		}
	}

	//ƒŠƒUƒ‹ƒgƒXƒe[ƒW‚ÉˆÚ“®
	void GameStage::LoadResultStage() {
		if (!m_isLoadStage) {
			m_fadeInUI->SetUpdateActive(true);
		}
	}

	//ƒQ[ƒ€‚ÌƒZ[ƒu
	int GameStage::SaveGameData() {
		if (!m_isLoadStage) {
			vector<int> saveScore = GameManager::GetInstance().GetSaveScore();
			int stageNum = GameManager::GetInstance().GetSelectStageNum();
			int score = GameManager::GetInstance().GetGameScore();

			if (saveScore[stageNum] < score) {
				saveScore[stageNum] = score;
				GameManager::GetInstance().SetSaveScore(saveScore);
			}
		}
		return 0;
	}

	//ƒoƒCƒiƒŠƒf[ƒ^‚Ìƒ[ƒh
	int GameStage::ReadGameData() {
		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);	

		wstring outfile = mediaDir + L"GameData/SaveData/file.otb";
		vector<int> saveNum;

		ifstream fin(outfile, ios::in | ios::binary);

		//“Ç‚İ‚ß‚È‚©‚Á‚½1‚ğ•Ô‚·
		if (!fin) {
			fin.close();
			return 1;
		}

		int num = 0;
		//ƒoƒCƒiƒŠƒf[ƒ^‚Ì’†g‚·‚×‚Ä‚ğŠm”F‚·‚é
		while (!fin.eof()) {
			//“Ç‚İ‚İ‚½‚¢ƒf[ƒ^‚ÌˆÊ’u‚ğw’è‚·‚éê‡‚Ég‚¤
			int readBinaryItr = 4;
			fin.seekg(readBinaryItr * sizeof(int));

			saveNum.push_back(0);

			//ƒoƒCƒiƒŠƒf[ƒ^‚ğ“Ç‚İ‚Ş
			fin.read((char *) &saveNum[num], sizeof(int));

			num++;
		}
		fin.close();
		return 0;
	}

	void GameStage::MovePlayerIcon() {

		auto maxMapPos = (-m_mapUIPos[EN_MapIcon::en_player].x) + m_mapUIPos[EN_MapIcon::en_goal].x;
		auto maxPos = m_waveSpawner->GetMaxCreatePosX();
		auto movement = (m_waveSpawner->GetSpawnTimer() / maxPos * maxMapPos);
		
		auto playerIconPos = m_playerIconTrans->GetPosition();

		auto cell = maxMapPos / maxPos;

		auto addPos = 0.0f;
		auto speed = 120.0f;
		if ((m_mapUIPos[EN_MapIcon::en_player].x + movement) > playerIconPos.x) {
			auto maxMovePos = m_mapUIPos[EN_MapIcon::en_player].x + movement;
			addPos = speed * App::GetApp()->GetElapsedTime();
		}

		Vec3 setPos = Vec3(playerIconPos.x + addPos, playerIconPos.y, playerIconPos.z);

		if (playerIconPos.x < m_mapUIPos[EN_MapIcon::en_goal].x) {
			m_playerIconTrans->SetPosition(setPos);
		}
		else {
			m_playerIconTrans->SetPosition(Vec3(m_mapUIPos[EN_MapIcon::en_goal].x, m_mapUIPos[EN_MapIcon::en_goal].y, playerIconPos.z));
		}
	}

	void GameStage::PlaySE(EN_SoundTypeSE soundType, wstring seName, float vol) {
		auto AudioManager = App::GetApp()->GetXAudio2Manager();
		m_SE[soundType] = AudioManager->Start(seName, 0, vol);
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

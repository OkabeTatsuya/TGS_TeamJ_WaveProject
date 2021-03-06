/*!
@file GameStage.cpp
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
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 0.0f, -100.0f);
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

			//エフェクトを作成
			m_efkInterface = ObjectFactory::Create<EfkInterface>();
			CreateEfkEffect();

			//値の初期化
			GameManager::GetInstance().ResetGame();
			GameManager::GetInstance().SetMaxSpecialCount(m_maxSpecialCount[m_specialJumpCount]);

			for (int i = 0; i < 2; i++) {
				m_SE.push_back(nullptr);
			}

			//UI作成
			CreateAnimUI();
			CreateGoalUI();
			CreateGameUI();

			//オブジェクト生成
			CreateGenerator();

			m_playerObj = AddGameObject<Player>(Vec3(0, 0, 0), Vec3(1.0f, 1.0f, 1), Vec3(-2.0f, -2, -7.0f), 7);
            m_playerObjTrans = m_playerObj->GetComponent<Transform>();

			AddGameObject<SeaCollision>(Vec3(0, 0, 0), Vec3(5, 0.5f, 1), Vec3(-2.5, -4.0, -7.0));

			//スコアUI
			m_scoreCountUI = AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(50.0f, 50.0f, 1.0f), Vec2(180.0f, 350.f), float(5.0f), L"Number.png", 7, false);
			AddGameObject<ImageUI>(Vec3(0.0f), Vec3(200.0f, 50.0f, 1.0f), Vec2(30.0f, 350.f), float(5.0f), L"Score.png");
 
			PlayBGM(L"game_maoudamashii_5_town05.wav");
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate() {
		m_efkInterface->OnUpdate();
		FadeInBGM(0.5f, 2.0f);
		FrastTimeCount();
		GameClear();
		UpdateScoreUI();
		SpecialJumpController();
		Hundler();
		MovePlayerIcon();
	}

	void GameStage::OnDestroy() {
		//BGMのストップ
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
		//アイテムのポジション
		Vec2 baseItemPos = Vec2(-550.0f, 320.0f);
		vector<Vec2> itemUIPos = { 
			baseItemPos,
			Vec2(baseItemPos.x + 330.0f, baseItemPos.y),
			Vec2(baseItemPos.x + 150.0f, baseItemPos.y),
			Vec2(baseItemPos.x + 380.0f, baseItemPos.y)
		};

		//マップのポジション
		m_baseMapUIPos = Vec2(-380.0f, 360.0f);
		m_mapUIPos = {
			m_baseMapUIPos,
			Vec2(m_baseMapUIPos.x +  255.0f, m_baseMapUIPos.y + -5.0f),
			Vec2(m_baseMapUIPos.x + -245.0f, m_baseMapUIPos.y + -5.0f),
		};

		Vec3 itemScale = Vec3(40.0f, 40.0f, 1.0f);
		AddGameObject<ImageUI>(Vec3(0.0f), itemScale, baseItemPos, float(5.0f), L"Coin.png");
		//アイテム上限UI
		m_maxItemCountUI = AddGameObject<ScoreUIPanel>(Vec3(0.0f), itemScale, itemUIPos[3], float(5.0f), L"GoldenNumbers.png", 2, false);
		//描画する数字
		auto drawNum = GameManager::GetInstance().GetMaxSpecialCount();
		m_maxItemCountUI->ScoreDraw(drawNum);

		AddGameObject<ImageUI>(Vec3(0.0f), itemScale, itemUIPos[2], float(5.0f), L"Slash.png");

		//アイテムカウントUI
		m_itemCountUI = AddGameObject<ScoreUIPanel>(Vec3(0.0f), itemScale, itemUIPos[1], float(5.0f), L"GoldenNumbers.png", 2, false);
		drawNum = GameManager::GetInstance().GetSpecialCount();
		m_itemCountUI->ScoreDraw(drawNum);

		//マップUI
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(512.0f, 125.0f, 1.0f), m_mapUIPos[0], float(5.0f), L"MapStage.png");
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(30.0f, 30.0f, 1.0f), m_mapUIPos[1], float(6.0f), L"MapGoal.png");
		m_playerIconUI = AddGameObject<ImageUI>(Vec3(0.0f), Vec3(20.0f, 20.0f, 1.0f), m_mapUIPos[2], float(7.0f), L"MapPlayer.png");
		m_playerIconTrans = m_playerIconUI->GetComponent<Transform>();

		CreateCommandUI();

		//カットインUI
		m_cutInUI = AddGameObject<CutInUI>(Vec3(0.0f), Vec3(1300.0f, 400.0f, 1.0f), Vec2(0.0f), float(5.0f), L"CutIN1.png");

		//ビッグウェーブで獲得したスコアを表示
		m_bigWaveScoreUI = AddGameObject<BigWaveScoreUI>(Vec3(0.0f), Vec3(256.0f, 128.0f, 1.0f), Vec2(-80.0f,70.0f), float(5.0f), L"Total.png");

		//フェードUI
		AddGameObject<Fade>();
		m_fadeInUI = AddGameObject<Fade>(L"ToResulfStage");
		m_fadeInUI->SetUpdateActive(false);
	};

	//アニメーションするUIを作成
	void GameStage::CreateAnimUI() {
		St_AnimUI statUIState1 = {
			//初期トランスフォーム
			Vec2(1000.0f,50.0f),Vec3(0.0f),m_textScale,
			//アニメーション後のトランスフォーム
			Vec2(0.0f,50.0f),Vec3(0.0f),m_textScale,
			//左から　レイヤー、アニメーション開始時間、終了時間
			8.0f,0.0f,0.5f,
			//アニメーション終了後の処理
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

		//張り付けるテクスチャ
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

	//ゴールした時のアニメーションUIを作成
	void GameStage::CreateGoalUI() {
		St_AnimUI GoalUIState = {
			Vec2(1000.0f,50.0f),Vec3(0.0f),m_textScale,
			Vec2(0.0f,50.0f),Vec3(0.0f),m_textScale,
			8.0f,0.0f,0.5f,AnimType::Delete
		};

		St_AnimUI failedUIState = {
			Vec2(1000.0f,50.0f),Vec3(0.0f),m_textScale,
			Vec2(0.0f,50.0f),Vec3(0.0f),m_textScale,
			8.0f,0.0f,0.5f,AnimType::Delete
		};

		//張り付けるテクスチャ
		vector<wstring> texter{
			L"Gorl.png",
			L"Failed.png",
		};

		m_goalUI = AddGameObject<AnimationUI>(GoalUIState, texter[0], m_maxLoadStageTime);
		m_failedUI = AddGameObject<AnimationUI>(failedUIState, texter[1], m_maxLoadStageTime);
	}

	void GameStage::CreateCommandUI() {
		float baseCommandUIPosY = 45;
		Vec2 baseCommandUIPos = Vec2(450.0f, 350.0f);
		vector<Vec2> commandUIPos;
		vector<Vec2> commandIconUIPos;

		for (int i = 0; i < 4; i++) {
			commandUIPos.push_back(Vec2(baseCommandUIPos.x + 0.0f, baseCommandUIPos.y + -baseCommandUIPosY * i));
			commandIconUIPos.push_back(Vec2(baseCommandUIPos.x + 120.0f, baseCommandUIPos.y + -baseCommandUIPosY * i));
		};

		Vec2 baseCommandIconScl = Vec2(4.0f, 2.0f);
		float magnification = 30;
		float magnification1 = 25;

		Vec3 commandScl =
			Vec3(baseCommandIconScl.x * magnification, baseCommandIconScl.y * magnification, 1.0f);

		vector<Vec3> commandIconScl = {
			Vec3(48.0f, 48.0f, 1.0f),
			Vec3(baseCommandIconScl.x * magnification1, baseCommandIconScl.y * magnification1, 1.0f),
			Vec3(baseCommandIconScl.x * magnification1, baseCommandIconScl.y * magnification1, 1.0f),
			Vec3(baseCommandIconScl.x * magnification1, baseCommandIconScl.y * magnification1, 1.0f)
		};

		vector<wstring> commandImage = {
			L"JunpUI.png",
			L"CommandUI1.png",
			L"CommandUI2.png",
			L"CommandUI3.png"
		};

		vector<wstring> commandIconImange = {
			L"ABttun.png",
			L"Icon1.png",
			L"Icon2.png",
			L"Icon3.png"
		};

		//コマンドUI
		for (int i = 0; i < commandUIPos.size(); i++) {
			AddGameObject<ImageUI>(Vec3(0.0f), commandScl, commandUIPos[i], float(6.0f), commandImage[i]);
		}

		//アイコンUI
		for (int i = 0; i < commandIconUIPos.size(); i++) {
			AddGameObject<ImageUI>(Vec3(0.0f), commandIconScl[i], commandIconUIPos[i], float(6.0f), commandIconImange[i]);
		}
	}

	//ジェネレーターを作成
	void GameStage::CreateGenerator() {
		auto& gm = GameManager::GetInstance();

		vector<wstring> setTexName = m_noonTexName;
		if (gm.GetSelectStageNum() == 2) {
			setTexName = m_eveningTexName;
		}

		if (gm.GetSelectStageNum() == 3) {
			setTexName = m_sunsetTexName;
		}
		vector<BackGroundState> BGState = {
			BackGroundState{ Vec3(0.0f), Vec3(-10.0f,  0.0f,  0.0f),	Vec2(5.0f, 5.0f), 0, setTexName[0], -10.0f, 0.037f },	//空
			BackGroundState{ Vec3(0.0f), Vec3(-10.0f,  0.0f, -3.0f),	Vec2(5.0f, 5.0f), 3, setTexName[1], -10.0f, 0.037f },	//背景の海
			BackGroundState{ Vec3(0.0f), Vec3(-10.0f, -0.12f, -8.0),	Vec2(5.0f, 5.0f), 8, setTexName[2], -10.0f, 0.137f },	//プレイヤーの下にある海
			BackGroundState{ Vec3(0.0f), Vec3(-10.0f,  0.0f, -1.0),	Vec2(5.0f, 5.0f), 1, setTexName[3], -10.0f, 0.0062f },		//雲
		};

		BackGroundState IslandState =	{ Vec3(0.0f), Vec3(-10.0f, -0.3f, -2.0),	Vec2(1.5f, 1.5f), 2, setTexName[4], -10.0f, 0.02f };

		for (int i = 0; i < BGState.size(); i++) {
			AddGameObject<BGGenerator>(BGState[i]);
		}
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
		//コントローラーの取得
		auto cntVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		if (cntVec[0].bConnected)
		{
			m_isReset = cntVec[0].wPressedButtons & XINPUT_GAMEPAD_LEFT_THUMB &&
				cntVec[0].wPressedButtons & XINPUT_GAMEPAD_RIGHT_THUMB;
			if (m_isReset)
			{
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
			}
			//リスタート
			if (cntVec[0].wPressedButtons & XINPUT_GAMEPAD_START) 
			{
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
			}
		}
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
		auto &gameManager = GameManager::GetInstance();
		bool isGameEnd = gameManager.GetIsGameEnd();

		GameEnd();

		if (isGameEnd && m_loadStageTimeCount == 0) {
			int stageNum = gameManager.GetSelectStageNum();
			int gameScore = gameManager.GetGameScore();

			if (gameManager.GetGameClearScore(stageNum) < gameScore && !m_gameOver) {
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
				m_failedUI->SetIsStartAnim(true);
			}
			else {
				m_goalUI->SetIsStartAnim(true);
			}
		}
	}

	void GameStage::SpecialJumpController() {
		//ジャンプフラグが立っていたらスピードを下げる
		auto& gameManager = GameManager::GetInstance();
		auto specialJumpFlag = gameManager.GetIsSpecialJump();
		auto specialJumpTimeFlag = gameManager.GetIsSpecialTime();

		if (!specialJumpTimeFlag) {
			m_playSpecialSE = false;
		}
		else {
			m_isVisibleBigWaveScore = false;
		}

		if (specialJumpTimeFlag && !m_playSpecialSE) {
			m_cutInUI->ResetState();
			if (m_specialJumpCount < m_maxSpecialCount.size() -1) {
				m_specialJumpCount++;
				gameManager.SetMaxSpecialCount(m_maxSpecialCount[m_specialJumpCount]);
			}
			m_playSpecialSE = true;
		}

		if (m_specialJumpCount != 0 && !specialJumpTimeFlag && !m_isVisibleBigWaveScore) {
			m_bigWaveScoreUI->ResetState();
			m_isVisibleBigWaveScore = true;
		}

		if (specialJumpFlag) {
			gameManager.SetGameSpeed(m_SpecialJumpSpeed);

			float maxCount = 0.1f;
			float delta = App::GetApp()->GetElapsedTime();
			m_specialJumpTimer += delta;
			if (m_specialJumpTimer > maxCount) {
				m_specialJumpTimer = 0.0f;
				gameManager.SetGameSpeed(m_saveGameSpeed);
				gameManager.SetIsSpecialJump(false);
			}
		}
		else {
			m_saveGameSpeed = gameManager.GetGameSpeed();
		}
	}

	//リザルトステージに移動
	void GameStage::LoadResultStage() {
		if (!m_isLoadStage) {
			m_fadeInUI->SetUpdateActive(true);
		}
	}

	//ゲームのセーブ
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

	//バイナリデータのロード
	int GameStage::ReadGameData() {
		wstring mediaDir;
		App::GetApp()->GetDataDirectory(mediaDir);	

		wstring outfile = mediaDir + L"GameData/SaveData/file.otb";
		vector<int> saveNum;

		ifstream fin(outfile, ios::in | ios::binary);

		//読み込めなかった時1を返す
		if (!fin) {
			fin.close();
			return 1;
		}

		int num = 0;
		//バイナリデータの中身すべてを確認する
		while (!fin.eof()) {
			//読み込みたいデータの位置を指定する場合に使う
			int readBinaryItr = 4;
			fin.seekg(readBinaryItr * sizeof(int));

			saveNum.push_back(0);

			//バイナリデータを読み込む
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

	void GameStage::PlayBGM(wstring bgmName) {
		auto audioManager = App::GetApp()->GetXAudio2Manager();
		audioManager->Stop(m_BGM);
		m_BGM = audioManager->Start(bgmName, XAUDIO2_LOOP_INFINITE, 0.1f);
	}

	//
	void GameStage::FadeInBGM(float maxVol, float time) {
		auto audioManager = App::GetApp()->GetXAudio2Manager();
		audioManager->MyFadeIn(m_BGM, maxVol, time);
	}

	//ビットフラグを上げる
	void GameStage::TrueSpawnFlag(unsigned int bit_flag) {
		if (!(m_spawnFlag & bit_flag)) {
			m_spawnFlag |= bit_flag;
		}
	}

	//ビットフラグを下げる
	void GameStage::FalseSpawnFlag(unsigned int bit_flag) {
		if (m_spawnFlag & bit_flag) {
			m_spawnFlag &= ~(bit_flag);
		}
	}

	//フラグの状態を確認する
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

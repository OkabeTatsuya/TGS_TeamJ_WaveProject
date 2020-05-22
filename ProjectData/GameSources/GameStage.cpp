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

            AddGameObject<Fade>();

			//UI作成
			CreateAnimUI();
			CreateGoalUI();

			//オブジェクト生成
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
		//BGMのストップ
		auto BGM = App::GetApp()->GetXAudio2Manager();
		BGM->Stop(m_BGM);
	}

	void GameStage::OnDraw() {
		auto& camera = GetView()->GetTargetCamera();
		m_efkInterface->SetViewProj(camera->GetViewMatrix(), camera->GetProjMatrix());
		m_efkInterface->OnDraw();
	}

	//アニメーションするUIを作成
	void GameStage::CreateAnimUI() {
		St_AnimUI statUIState1 = {
			//初期トランスフォーム
			Vec2(1000.0f,100.0f),Vec3(0.0f),m_textScale,
			//アニメーション後のトランスフォーム
			Vec2(0.0f,100.0f),Vec3(0.0f),m_textScale,
			//左から　レイヤー、アニメーション開始時間、終了時間
			8.0f,0.0f,0.5f,
			//アニメーション終了後の処理
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

		//張り付けるテクスチャ
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

	//ゴールした時のアニメーションUIを作成
	void GameStage::CreateGoalUI() {
		St_AnimUI GoalUIState = {
			Vec2(1000.0f,200.0f),Vec3(0.0f),m_textScale,
			Vec2(0.0f,200.0f),Vec3(0.0f),m_textScale,
			8.0f,0.0f,0.5f,AnimType::Delete
		};

		//張り付けるテクスチャ
		wstring texter{
			L"Gorl.png",
		};

		m_goalUI = AddGameObject<AnimationUI>(GoalUIState, texter, m_maxLoadStageTime);
		m_isCreateGoalUI = true;
	}

	//ジェネレーターを作成
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

	void GameStage::CreateEfkEffect() {
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);

		for (int i = 0; i < m_effectNames.EffectName.size(); i++) {
			wstring effectStr = dataDir + L"Effect\\" + m_effectNames.EffectName[i];
			m_efkEffect.push_back(ObjectFactory::Create<EfkEffect>(m_efkInterface, effectStr));
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

	void GameStage::SpecialJumpController() {
		//ジャンプフラグが立っていたらスピードを下げる
		auto specialJumpFlag = GameManager::GetInstance().GetIsSpecialJump();
		if (specialJumpFlag) {
			GameManager::GetInstance().SetGameSpeed(m_SpecialJumpSpeed);

			float maxCount = 0.2f;
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

	//リザルトステージに移動
	void GameStage::LoadResultStage() {
		if (!m_isLoadStage) {
            AddGameObject<Fade>(L"ToResulfStage");
		}
	}

	//ゲームのセーブ
	int GameStage::SaveGameData() {

		vector<int> saveScore = GameManager::GetInstance().GetSaveScore();
		int stageNum = GameManager::GetInstance().GetSelectStageNum();
		int score = GameManager::GetInstance().GetGameScore();


		if (saveScore[stageNum] < score) {
			saveScore[stageNum] = score;
			GameManager::GetInstance().SetSaveScore(saveScore);
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

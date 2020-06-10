/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	リザルトステージクラス実体
	//--------------------------------------------------------------------------------------
	void ResultStage::CreateViewLight() {//リザルト画面
		const Vec3 eye(0.0f, 0.0f, -20.0f);
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
		{
			m_Time = false;
		}
	}

	//ボタンを押す
	void ResultStage::Press() {
		auto cntVec = App::GetApp()->GetInputDevice().GetControlerVec();
		cntVec[0].wPressedButtons & XINPUT_GAMEPAD_A;
	}

	//ボタンを押すとシーン遷移する
	void ResultStage::Sceneloader() {
		App::GetApp()->GetScene<Scene>()->LoadStage(m_ResultUi[m_ResultUiCount]);
	}

	//BGMを流す処理
	void ResultStage::GetBGM() {
		auto BGM = App::GetApp()->GetXAudio2Manager();
		m_BGM = BGM->Start(L"bgm_maoudamashii_acoustic41.wav", XAUDIO2_LOOP_INFINITE, 0.5f);
	}

	//SEを流す処理
	void ResultStage::GetSE() {
		auto SE = App::GetApp()->GetXAudio2Manager();
		m_SE = SE->Start(L"se_maoudamashii_system37.wav", 0, 0.5f);
	}

	void ResultStage::m_ControllerA()		//コントローラーA
	{
		//コントローラーの取得
		auto cntVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntVec[0].bConnected)
		{
			//Aボタン
			if (!m_isPlayUnlockStageAnim && cntVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
			{
				auto SE = App::GetApp()->GetXAudio2Manager();
				m_SE = SE->Start(L"se_maoudamashii_system37.wav", 0, 0.5f);

			}
		}
	}

	void ResultStage::SetNextStage() {
		auto &gameManager = GameManager::GetInstance();
		if (m_ResultUiCount == 0) {
			auto& manager = GameManager::GetInstance();
			auto clearStageNum = manager.GetClearStageNum();
			auto selectStageNum = manager.GetSelectStageNum();

			if (selectStageNum < gameManager.GetSaveScore().size()-1 && selectStageNum < clearStageNum) {
				gameManager.SetSelectStageNum(selectStageNum + 1);
			}
		}
	}

	void ResultStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();

			/*Fade*/
			AddGameObject<Fade>();

			///*BG(バックグラウンド)*/
			AddGameObject<ImageUI>(Vec3(0.0f), Vec3(1300.0f, 800.0f, 1.0f), Vec2(0.0f, 0.0f), float(0.0f), L"ResultBG.png");//空の画像

			if (GameManager::GetInstance().GetIsGameClear()) {
				AddGameObject<ImageUI>(Vec3(0.0f), Vec3(600.0f, 600.0f, 1.0f), Vec2(-250.0f, -0.0f), float(1.0f), L"WinIllsutration.png");//プレイヤーの画像
			}
			else {
				AddGameObject<ImageUI>(Vec3(0.0f), Vec3(600.0f, 600.0f, 1.0f), Vec2(-250.0f, -0.0f), float(1.0f), L"LoseIllsutration.png");//プレイヤーの画像
			}
			
			/*ゲームクリアorゲームオーバー*/
			//AddGameObject<ImageUI>(Vec3(0.0f), Vec3(800.0f, 150.0f, 1.0f), Vec2(0.0f, 300.0f), float(2.0f), L"Tx_GameClear.png");

			Vec3 buttonSize = Vec3(512.0f, 256.0f, 1.0f);

			m_Pos[0] = Vec2(-430.0f, -300.0f);//次のステージへ
			m_Pos[1] = Vec2(0.0f, -300.0f);//ステージセレクト
			m_Pos[2] = Vec2(430.0f, -300.0f);//タイトルへ

			/*次のステージへ*/
			AddGameObject<ImageUI>(Vec3(0.0f), buttonSize, m_Pos[0], float(2.0f), L"NextStageButton.png");

			/*ステージセレクトへ*/
			AddGameObject<ImageUI>(Vec3(0.0f), buttonSize, m_Pos[1], float(2.0f), L"SelectButton.png");

			/*タイトルへ*/
			AddGameObject<ImageUI>(Vec3(0.0f), buttonSize, m_Pos[2], float(2.0f), L"TitleButton.png");

			/*ステージ番号の表示*/
			AddGameObject<ImageUI>(Vec3(0.0f), buttonSize, Vec2(-450.0f, 350.0f), float(2.0f), L"StageUI.png");

			AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(40.0f, 40.0f, 1.0f), Vec2(-200.0f, 350.0f), float(3.0f), L"BlackNumbers.png", 1, false);
			GameManager::GetInstance().DrawStageNum();

			CreateResultUI();

			/*点滅*/
			m_CursorUI = AddGameObject<CursorUI>(Vec3(0.0f), Vec3(400.0f, 80.0f, 1.0f), m_Pos[m_ResultUiCount], float(3.0f), L"FadeBG.png", float(2.0));


			//サウンドの追加
			auto BGM = App::GetApp()->GetXAudio2Manager();
			m_BGM = BGM->Start(L"bgm_maoudamashii_acoustic41.wav", XAUDIO2_LOOP_INFINITE, 0.5f);

			RandomVoiceSE();

			m_ResultUi[0] = L"ToGameStage"; //リザルト画面のボタン配置
			m_ResultUi[1] = L"ToSelectStage";
			m_ResultUi[2] = L"ToTitleStage";
			//m_ResultUi[3] = L"ToGameStage";

		}
		catch (...) {

			throw;
		}
	}

	void ResultStage::OnUpdate()
	{
		try
		{
			m_ControllerA();

			//カウントをとる
			//m_Time += App::GetApp()->GetElapsedTime();

			auto cntVec = App::GetApp()->GetInputDevice().GetControlerVec();

			//ヘッターに書かないと保存されないので注意
			//bool m_isPush = false;

			if (!m_isPlayUnlockStageAnim && cntVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
			{
				//bollをtrueにする
				m_isPush = true;
			}

			if (m_isPush && !m_isloadStage)
			{
				m_Time += App::GetApp()->GetElapsedTime();
			}

			if (m_Time >= 0.1)//0.1秒後にシーン遷移
			{
				SetNextStage();
				AddGameObject<Fade>(m_ResultUi[m_ResultUiCount]);
				m_isloadStage = true;
				m_Time = 0.0f;
			}

			if (!m_isPlayUnlockStageAnim) {
				GetMoveVector();
			}

			UnlockStageAnim();
		}
		catch (...) {

			throw;
		}
	}

	void ResultStage::OnDestroy() {

		auto SEManager = App::GetApp()->GetXAudio2Manager();
		SEManager->Stop(m_SE);

		auto AudioManager = App::GetApp()->GetXAudio2Manager();
		AudioManager->Stop(m_BGM);
		AudioManager->Stop(m_voiceSE);
	}

	void ResultStage::CreateResultUI() {
		//リザルトテーブル　この値を変更するとスコアUIがすべて移動する
		Vec2 resultsTabelPos = Vec2(300.0f, 0.0f);
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(650.0f, 670.0f, 1.0f), resultsTabelPos, float(2.0f), L"WhiteBoard.png");

		float scoreSize = 40.0f;
		vector<Vec2> resultsTabe = {
			resultsTabelPos + Vec2(0.0f, 110.0f),		//スコア
			resultsTabelPos + Vec2(-40.0f, 65.0f),		//クリアスコア
			resultsTabelPos + Vec2(-110.0f, -10.0f),	//パーファクト回数
			resultsTabelPos + Vec2(-110.0f, -90.0f),	//グッド回数
			resultsTabelPos + Vec2(40.0f, 90.0f),		//スコア間の線
			resultsTabelPos + Vec2(10.0f, 30.0f),		//スコアテキスト
			resultsTabelPos + Vec2(10.0f, 30.0f),		//スコアの下線
			resultsTabelPos + Vec2(-100.0f, -10.0f),	//パーフェクトテキスト
			resultsTabelPos + Vec2(-140.0f, -90.0f),	//グッドテキスト
			resultsTabelPos + Vec2(-00.0f, -40.0f),		//パーフェクト回数の下線
			resultsTabelPos + Vec2(-00.0f, -120.0f),	//グッド回数の下線
			resultsTabelPos + Vec2(-120.0f, -170.0f),	//アイテム
			resultsTabelPos + Vec2(-110.0f, -170.0f),   //アイテム個数
			resultsTabelPos + Vec2(-40.0f, -170.0f),	//アイテム個数の上限
			resultsTabelPos + Vec2(130.0f, -10.0f),		//×テキスト１
			resultsTabelPos + Vec2(130.0f, -90.0f),		//×テキスト２
			resultsTabelPos + Vec2(130.0f, -170.0f),	//×テキスト３
			resultsTabelPos + Vec2(200.0f, -10.0f),		//パーフェクトのスコア
			resultsTabelPos + Vec2(200.0f, -90.0f),		//グッドのスコア
		};

		Vec2 baseScale = Vec2(1.0f);

		//スコアの表示
		AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(45.0f, 45.0f, 1.0f), resultsTabe[0], float(3.0f), L"PinkNumbers.png", 7, false,true);
		GameManager::GetInstance().DrawScore();

		//クリアスコアの表示
		AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(scoreSize, scoreSize, 1.0f), resultsTabe[1], float(3.0f), L"GrayNumbers.png", 7, false);
		GameManager::GetInstance().DrawClearScore(GameManager::GetInstance().GetSelectStageNum());

		//Perfectの回数を表示
		AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(scoreSize, scoreSize, 1.0f), resultsTabe[2], float(3.0f), L"BlackNumbers.png", 2, false);
		GameManager::GetInstance().DrawJudgeCount(JudgeName::en_Perfect);

		//Goodの回数を表示
		AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(scoreSize, scoreSize, 1.0f), resultsTabe[3], float(3.0f), L"BlackNumbers.png", 2, false);
		GameManager::GetInstance().DrawJudgeCount(JudgeName::en_Good);

		//セレクトテキスト
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(512.0f, 512.0f, 1.0f), resultsTabe[5], float(3.0f), L"ScoreLetter.png");
		//スコア下線
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(420.0f, 7.0f, 1.0f), resultsTabe[6], float(3.0f), L"Border.png");
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(256.0f, 128.0f, 1.0f), resultsTabe[7], float(4.0f), L"Perfect.png");
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(256.0f, 128.0f, 1.0f), resultsTabe[8], float(4.0f), L"Good.png");

		//下線
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(154.0f, 92.0f, 1.0f), resultsTabe[4], float(3.0f), L"DaigonalLine.png");
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(413.0f, 3.0f, 1.0f), resultsTabe[9], float(5.0f), L"UnderLine.png");
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(413.0f, 3.0f, 1.0f), resultsTabe[10], float(5.0f), L"UnderLine.png");

		//アイテム
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(60.0f, 60.0f, 1.0f), resultsTabe[11], float(4.0f), L"Coin.png");

		//アイテム個数
		AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(scoreSize, scoreSize, 1.0f), resultsTabe[12], float(3.0f), L"BlackNumbers.png", 2, false);
		GameManager::GetInstance().DrawNum(GameManager::GetInstance().GetItemCount());

		//アイテムの上限
		AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(scoreSize, scoreSize, 1.0f), resultsTabe[13], float(3.0f), L"BlackNumbers.png", 2, false);
		GameManager::GetInstance().DrawNum(GameManager::GetInstance().GetMaxItemNum());

		//Xテキスト
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(50.0f, 50.0f, 1.0f), resultsTabe[16], float(5.0f), L"Slash.png");

		//ステージアンロック演出UI
		m_unlockStageUI = AddGameObject<UnlockStageUI>(Vec3(0.0f), Vec3(50.0f, 50.0f, 1.0f), resultsTabe[16], float(5.0f), L"Slash.png");
	};

	void ResultStage::UnlockStageAnim() {
		auto& manager = GameManager::GetInstance();
		auto maxStageNum = manager.GetSaveScore().size();
		auto selectStageNum = manager.GetSelectStageNum();
		auto clearStageNum = manager.GetClearStageNum();

		//
		bool unlockFlag = clearStageNum == selectStageNum && selectStageNum < manager.GetGameClearScoreVector().size() -1;

		//ゲームクリアし、アンロック演出がまだ起きていない
		if (!m_isPush && !m_unlockStageUI->GetIsEndAnim() && manager.GetIsGameClear() && unlockFlag) {
			auto unlockStageNum = clearStageNum + 1;

			if (manager.GetIsGameClear() && unlockStageNum < maxStageNum && clearStageNum == selectStageNum) {
				manager.SetClearStageNum(unlockStageNum);
			}

			m_isPlayUnlockStageAnim = true;
		}

		if (m_unlockStageUI->GetIsEndAnim()) {
			m_isPlayUnlockStageAnim = false;
		}

		if (m_isPlayUnlockStageAnim) {
			m_unlockStageUI->PlayAnim();
		}

	}

	Vec2 ResultStage::GetMoveVector()
	{
		Vec2 angle(0, 0);
		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		float fThumbLX = 0.0f;
		float fThumbLY = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {

			fThumbLX = cntlVec[0].fThumbLX;
			fThumbLY = cntlVec[0].fThumbLY;
			wButtons = cntlVec[0].wButtons;
		}


		if (m_Push) {
			m_Timer += App::GetApp()->GetElapsedTime();

		}

		if (m_Timer >= 0.25)
		{
			if (fThumbLX <= -1.0f)//スティックが左に倒れた時
			{
				auto SE = App::GetApp()->GetXAudio2Manager();
				SE->Start(L"se_maoudamashii_system37.wav", 0, 0.5f);
				m_Timer = 0;
				m_Push = true;

				m_ResultUiCount -= 1;//左に1つ移動
			}
			if (fThumbLX >= +1.0f)//スティックが右に倒れた時
			{
				auto SE = App::GetApp()->GetXAudio2Manager();
				SE->Start(L"se_maoudamashii_system37.wav", 0, 0.5f);
				m_Timer = 0;
				m_Push = true;

				m_ResultUiCount += 1;//右に1つ移動
			}
		}

		if (m_ResultUiCount > 2)//リザルトボタンで3つ以上移動しないように
		{
			m_ResultUiCount = 2;
		}
		if (m_ResultUiCount < 0)
		{
			m_ResultUiCount = 0;
		}

		//ポジションを設定する
		m_CursorUI->GetComponent<Transform>()->SetPosition(Vec3(m_Pos[m_ResultUiCount].x, m_Pos[m_ResultUiCount].y, 1.0f));

		return angle;
	}

	void ResultStage::RandomVoiceSE() {
		std::random_device rando;
		std::mt19937 mt(rando());
		int num = mt() % 2;

		auto SE = App::GetApp()->GetXAudio2Manager();
		if (GameManager::GetInstance().GetIsGameClear()) {
			m_voiceSE = SE->Start(m_gameclearVoiceStr[num], 0, 1.5f);
		}
		else {
			m_voiceSE = SE->Start(m_gameoverVoiceStr[num], 0, 1.0f);
		}

	}
}
//end basecross

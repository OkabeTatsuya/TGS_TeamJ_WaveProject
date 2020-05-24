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
			if (cntVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
			{

				auto SE = App::GetApp()->GetXAudio2Manager();
				m_SE = SE->Start(L"se_maoudamashii_system37.wav", 0, 0.5f);

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
			AddGameObject<ImageUI>(Vec3(0.0f), Vec3(1300.0f, 800.0f, 1.0f), Vec2(0.0f, 0.0f), float(2.0f), L"ResultBG.png");//空の画像

			AddGameObject<ImageUI>(Vec3(0.0f), Vec3(700.0f, 700.0f, 1.0f), Vec2(-200.0f, -50.0f), float(2.0f), L"Junp3_34.png");//プレイヤーの画像
			
			/*ゲームクリアorゲームオーバー*/
			//AddGameObject<ImageUI>(Vec3(0.0f), Vec3(800.0f, 150.0f, 1.0f), Vec2(0.0f, 300.0f), float(2.0f), L"Tx_GameClear.png");

			Vec3 buttonSize = Vec3(512.0f, 256.0f, 1.0f);
			/*タイトルへ*/
			AddGameObject<ImageUI>(Vec3(0.0f), buttonSize, Vec2(-450.0f, -300.0f), float(2.0f), L"TitleButton.png");

			/*ステージセレクトへ*/
			AddGameObject<ImageUI>(Vec3(0.0f), buttonSize, Vec2(-50.0f, -300.0f), float(2.0f), L"SelectButton.png");

			/*次のステージへ*/
			AddGameObject<ImageUI>(Vec3(0.0f), buttonSize, Vec2(400.0f, -300.0f), float(2.0f), L"NextStageButton.png");

			/*ステージ番号の表示*/
			AddGameObject<ImageUI>(Vec3(0.0f), buttonSize, Vec2(-450.0f, 350.0f), float(2.0f), L"StageUI.png");

			AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(40.0f, 40.0f, 1.0f), Vec2(-400.0f, 350.0f), float(2.0f), L"BlackNumbers.png", 1, false);
			GameManager::GetInstance().DrawStageNum();

			Vec2 resultsTabelPos = Vec2(350.0f, 0.0f);
			AddGameObject<ImageUI>(Vec3(0.0f), Vec3(512.0f, 512.0f, 1.0f), resultsTabelPos, float(2.0f), L"ResultsTable.png");

			float scoreSize = 40.0f;
			vector<Vec2> resultsTabe = {
				resultsTabelPos + Vec2(200.0f, 110.0f),
				resultsTabelPos + Vec2(200.0f, 35.0f),
				resultsTabelPos + Vec2(120.0f, -40.0f),
				resultsTabelPos + Vec2(120.0f, -120.0f)
			};

			//スコアの表示
			AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(50.0f, 50.0f, 1.0f), resultsTabe[0], float(2.0f), L"PinkNumbers.png", 7, false);
			GameManager::GetInstance().DrawScore();

			//クリアスコアの表示
			AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(scoreSize, scoreSize, 1.0f), resultsTabe[1], float(2.0f), L"GrayNumbers.png", 7, false);
			GameManager::GetInstance().DrawClearScore(GameManager::GetInstance().GetSelectStageNum());

			//Perfectの回数を表示
			AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(scoreSize, scoreSize, 1.0f), resultsTabe[2], float(2.0f), L"BlackNumbers.png", 2, false);
			GameManager::GetInstance().DrawJudgeCount(JudgeName::en_Perfect);

			//Goodの回数を表示
			AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(scoreSize, scoreSize, 1.0f), resultsTabe[3], float(2.0f), L"BlackNumbers.png", 2, false);
			GameManager::GetInstance().DrawJudgeCount(JudgeName::en_Good);

			m_Pos[0] = Vec2(-450.0f, -300.0f);//タイトルへ
			m_Pos[1] = Vec2(-50.0f, -300.0f);//ステージセレクト
			m_Pos[2] = Vec2(400.0f, -300.0f);//次のステージへ

			/*点滅*/
			m_CursorUI = AddGameObject<CursorUI>(Vec3(0.0f), Vec3(400.0f, 80.0f, 1.0f), m_Pos[m_ResultUiCount], float(3.0f), L"FadeBG.png", float(2.0));


			//サウンドの追加
			auto BGM = App::GetApp()->GetXAudio2Manager();
			m_BGM = BGM->Start(L"bgm_maoudamashii_acoustic41.wav", XAUDIO2_LOOP_INFINITE, 0.5f);

			//auto SE = App::GetApp()->GetXAudio2Manager();
			//m_SE = SE->Start(L"se_maoudamashii_system37.wav", 0, 0.5f);
			m_ResultUi[0] = L"ToTitleStage"; //リザルト画面のボタン配置
			m_ResultUi[1] = L"ToSelectStage";
			m_ResultUi[2] = L"ToGameStage";
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

			if (cntVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
			{
				//bollをtrueにする
				m_isPush = true;
			}

			if (m_isPush)
			{
				m_Time += App::GetApp()->GetElapsedTime();
			}

			if (m_Time >= 0.1)//0.1秒後にシーン遷移
			{
				AddGameObject<Fade>(m_ResultUi[m_ResultUiCount]);
				m_Time = 0.0f;
			}
			GetMoveVector();
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
}
//end basecross

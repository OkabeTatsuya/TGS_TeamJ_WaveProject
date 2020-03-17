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

				//シーン移動                               (ゲームステージへ)
				//App::GetApp()->GetScene<Scene>()->LoadStage(L"ToGameStage");

			}
		}
	}

	void ResultStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			//					 ローテーション,スケール,ポジション
			//AddGameObject<Enemy>(Vec3(0.0f), Vec3(10.0f), Vec3(0.0f));

			AddGameObject<UIBase>(Vec3(0.0f), Vec3(40.0f, 40.0f, 1.0f), Vec2(-600.0f, 350.0f), float(2.0f), L"trace.png");
			//シーン移動                                 (ゲームステージへ)
			//App::GetApp()->GetScene<Scene>()->LoadStage(L"ToGameStage");

			//シーン移動                                 (ゲームタイトルへ)
			//App::GetApp()->GetScene<Scene>()->LoadStage(L"ToTitleStage");

			//サウンドの追加
			auto BGM = App::GetApp()->GetXAudio2Manager();
			m_BGM = BGM->Start(L"SampleBGM.wav", XAUDIO2_LOOP_INFINITE, 0.5f);

			//auto SE = App::GetApp()->GetXAudio2Manager();
			//m_SE = SE->Start(L"se_maoudamashii_system37.wav", 0, 0.5f);

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

			if (m_Time >= 3)
			{
				App::GetApp()->GetScene<Scene>()->LoadStage(L"ToGameStage");
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

		if (m_Timer>=3)
		{

			if (fThumbLX >= 1.0f)//スティックが右に倒れた時
			{
				auto SE = App::GetApp()->GetXAudio2Manager();
				SE->Start(L"se_maoudamashii_system37.wav", 0, 0.5f);
				m_Timer = 0;
				m_Push = true;
			}
			if (fThumbLX <= -1.0f)//スティックが左に倒れた時
			{
				auto SE = App::GetApp()->GetXAudio2Manager();																	
				SE->Start(L"se_maoudamashii_system37.wav", 0, 0.5f);
				m_Timer = 0;
				m_Push = true;
			}
		}
		//if (fThumbLY > 0.0f)//スティックが上に倒れた時
		//{
		//	auto SE = App::GetApp()->GetXAudio2Manager();
		//	SE->Start(L"se_maoudamashii_system37.wav", 0, 0.5f);
		//}
		//if (fThumbLY < -0.0f)//スティックが下に倒れた時
		//{
		//	auto SE = App::GetApp()->GetXAudio2Manager();
		//	SE->Start(L"se_maoudamashii_system37.wav", 0, 0.5f);
		//}



		return angle;
	}
}
//end basecross

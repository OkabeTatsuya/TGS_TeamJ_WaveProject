#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------

	void TitleStage::CreateViewLight() {
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
	void TitleStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();

			//バックグラウンド
			AddGameObject<ImageUI>(Vec3(0.0f), Vec3(1300.0f, 800.0f, 1.0f), Vec2(0.0f, 0.0f), float(2.0f), L"FadeBG.png");

			//画像
			AddGameObject<UIBase>(Vec3(0.0f), Vec3(500.0f, 400.0f, 1.0f), Vec2(350.0f, -100.0f), float(2.0f), L"Red.png");

			//タイトル画像
			AddGameObject<UIBase>(Vec3(0.0f), Vec3(600.0f, 300.0f, 1.0f), Vec2(-300.0f, 150.0f), float(2.0f), L"Red.png");

			//点滅させてボタン押してくださいのUI
			AddGameObject<FlashingUI>(Vec3(0.0f), Vec3(400.0f, 100.0f, 1.0f), Vec2(-400.0f, -200.0f), float(2.0f), L"Tx_PushButtons.png", 2.0f);

			//BGM再生と音量調整
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			m_BGM = XAPtr->Start(L"SampleBGM.wav", XAUDIO2_LOOP_INFINITE, 0.5f);
			
			//App::GetApp()->GetScene<Scene>()->LoadStage(L"ToGameStage");

		}
		catch (...) {
			throw;
		}
	}

	void TitleStage::OnUpdate(){
		auto CutlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (CutlVec[0].bConnected) {
			//Aボタンを押して、3秒経ったらシーン移動
			if (CutlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
				if (!m_isPushA) {
					//SE再生と音量調整
					auto XAPtr = App::GetApp()->GetXAudio2Manager();
					m_SE = XAPtr->Start(L"se_maoudamashii_system37.wav", 0, 0.5f);
					//Aボタンを押したときの処理
					m_isPushA = true;
				}
			}

		////Bボタンでシーン移動
		//	if (CutlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
		//		PostEvent(0.0f, GetThis <ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
		//	}
		}

		//時間を保存する
		if (m_isPushA) {
			m_time += App::GetApp()->GetElapsedTime();
		}

		//シーン移動
		if (m_time >= 3) {
			PostEvent(0.0f, GetThis <ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
		}
	}

	//BGMを止める
	void TitleStage::OnDestroy() {
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
		XAPtr->Stop(m_SE);
	}
}
//end basecross

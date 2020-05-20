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

		PtrCamera->SetPers(false);//遠近法
		PtrCamera->SetWidth(10);//画面に表示する横幅のユニット数
		PtrCamera->SetHeight(10);//画面に表示する縦幅のユニット数
		PtrCamera->SetFovY(0.5f);//視野角

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
			BackGroundState SkyState = { Vec3(0.0f), Vec3(-10.0f, 0.0f, 0.0f), Vec2(5.0f, 5.0f), L"Sky.png", -10.0f, 0.5f };
			BackGroundState BGState = { Vec3(0.0f), Vec3(-10.0f, 0.0f, 0.0f), Vec2(5.0f, 5.0f), L"Sea2.png", -10.0f, 0.5f };
			BackGroundState SeaState = { Vec3(0.0f), Vec3(-10.0f, -0.12f, -2.0), Vec2(5.0f, 5.0f), L"Sea1.png", -10.0f, 1.5f };
			BackGroundState CloudState = { Vec3(0.0f), Vec3(-10.0f, 3.0f, -1.0), Vec2(1.0f, 1.0f), L"cloud1.png", -10.0f, 0.5f };

			AddGameObject<BGGenerator>(SkyState);
			AddGameObject<BGGenerator>(BGState);
			AddGameObject<BGGenerator>(SeaState);
			AddGameObject<RandomGenerator>(CloudState, 1.0f, 4);

			//画像
			AddGameObject<TitleAnimationUI>(Vec3(0.0f), Vec3(200.0f, 200.0f, 1.0f), Vec2(-500.0f, -150.0f), float(2.0f), L"player.png");

			//タイトル画像
			AddGameObject<UIBase>(Vec3(0.0f), Vec3(1024.0f, 512.0f, 1.0f), Vec2(50.0f,200.0f), float(2.0f), L"TitleLogo.png");

			//点滅させてボタン押してくださいのUI
			AddGameObject<FlashingUI>(Vec3(0.0f), Vec3(400.0f, 200.0f, 1.0f), Vec2(-0.0f, -200.0f), float(2.0f), L"StartBattan.png", 2.0f);

			//BGM再生と音量調整
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			m_BGM = XAPtr->Start(L"SampleBGM.wav", XAUDIO2_LOOP_INFINITE, 0.3f);
			
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
		}

		//時間を保存する
		if (m_isPushA) {
			m_time += App::GetApp()->GetElapsedTime();
		}

		//シーン移動
		if (m_time >= 3) {
			AddGameObject<Fade>(L"ToSelectStage");
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

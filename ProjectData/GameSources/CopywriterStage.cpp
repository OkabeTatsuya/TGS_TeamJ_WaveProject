#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void CopywriterStage::CreateViewLight() {
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
	void CopywriterStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();

			CreateUI();
		}
		catch (...) {
			throw;
		}
	}

	void CopywriterStage::OnUpdate(){
		Hundler();
		LoadTitleStage();
	}

	//BGMを止める
	void CopywriterStage::OnDestroy() {
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_SE);
	}

	void CopywriterStage::CreateUI() {
		AddGameObject<Fade>();
		m_fadeInUI = AddGameObject<Fade>(L"ToTitleStage");
		//OnUpdateを止める
		m_fadeInUI->SetUpdateActive(false);

		//バックグラウンド
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(1300.0f, 800.0f, 1.0f), Vec2(0.0f, -0.0f), float(2.0f), L"Copywriter.png");
	}

	void CopywriterStage::LoadTitleStage() {
		if (!m_isLoadStage) {
			m_loadTimeCount += App::GetApp()->GetElapsedTime();

			if (m_loadTimeCount > m_maxLoadTime) {
				m_isLoadStage = true;
			}
		}
		else {
			//OnUpdateを動かす
			m_fadeInUI->SetUpdateActive(true);
		}
	}

	void CopywriterStage::Hundler() {
		auto CutlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		if (CutlVec[0].bConnected) {
			//Aボタンを押した時すぐにシーン移動
			if (CutlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
				PushAButton();
			}
		}
		else {
			if (KeyState.m_bPressedKeyTbl[VK_SPACE]) {
				PushAButton();
			}
		}
	}

	void CopywriterStage::PushAButton() {
		if (!m_isLoadStage) {
			//SE再生
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			m_SE = XAPtr->Start(L"se_maoudamashii_system37.wav", 0, 0.5f);

			//ステージを読み込むフラグを立てる
			m_isLoadStage = true;
		}
	}
}
//end basecross

/*!
@file SanpleStage.cpp
@brief オブジェクト紹介ステージの実態
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	カメラ、ライトの設定
	//--------------------------------------------------------------------------------------
	void SanpleStage::CreateViewLight() {
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

	void SanpleStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();

			//UIを作る関数
			CreateUI();

			//BGMを再生させる関数
			PlayBGM(L"SampleBGM.wav", 0.5f);

			//指定したシーンをロードする関数
			//LoadStage(L"ToTitleStage");
		}
		catch (...) {
			throw;
		}
	}

	void SanpleStage::OnUpdate(){

	}

	//--------------------------------------------------------------------------------------
	//別のステージに移った時など、このシーンが破棄される時に呼ばれる関数
	//--------------------------------------------------------------------------------------
	void SanpleStage::OnDestroy() {
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	//--------------------------------------------------------------------------------------
	//UIを作る関数
	//--------------------------------------------------------------------------------------
	void SanpleStage::CreateUI() {
		//画像を表示するUI
		//引数　Vec3(Rot),Vec3(Sca),Vec2(Pos.xy),float(Layer),wstring(ImageName)
		AddGameObject<ImageUI>(Vec3(0.0f), Vec3(100.0f, 100.0f, 1.0f), Vec2(-150.0f, 0.0f), float(2.0f), L"FadeBG.png");
		//AddGameObject<ImageUI>(Vec3(0.0f), Vec3(1280.0f, 800.0f, 1.0f), Vec2(0.0f, 0.0f), float(3.0f), L"BGImage.png");

		//画像を点滅させるUI
		//引数　Vec3(Rot),Vec3(Sca),Vec2(Pos.xy),float(Layer),wstring(ImageName),float(FlashSpeed)
		AddGameObject<FlashingUI>(Vec3(0.0f), Vec3(100.0f, 100.0f, 1.0f), Vec2(150.0f, 0.0f), float(2.0f), L"FadeBG.png", 2.0f);
		//AddGameObject<FlashingUI>(Vec3(0.0f), Vec3(1280.0f, 800.0f, 1.0f), Vec2(0.0f, 0.0f), float(3.0f), L"BGImage.png",3.5f);

	}

	//--------------------------------------------------------------------------------------
	//BGMを再生させる関数
	//--------------------------------------------------------------------------------------
	void SanpleStage::PlayBGM(wstring soundName, float vol) {
		//BGM再生と音量調整
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		m_BGM = XAPtr->Start(soundName, XAUDIO2_LOOP_INFINITE, vol);
	}

	//--------------------------------------------------------------------------------------
	//シーンをロードする関数
	//--------------------------------------------------------------------------------------
	void SanpleStage::LoadStage(wstring stageName) {
		App::GetApp()->GetScene<Scene>()
			->PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), stageName);
	}

}
//end basecross

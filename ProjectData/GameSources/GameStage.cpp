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
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 0.0f, -10.0f);
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

			AddGameObject<WaveSpawner>();

            AddGameObject<Player>(Vec3(0, 0, 0), Vec3(1, 1, 1),Vec3(-4.0, 2, 0));
            AddGameObject<GroundCollision>(Vec3(0, 0, 0), Vec3(1, 0.5, 3), Vec3(-4, -2, 0));

			//AddGameObject<Wave>(Vec3(0, 0, 0), Vec3(1, 1, 1), Vec3(0, -1.5, 0));
			//AddGameObject<Wave>(Vec3(0, 0, 0), Vec3(1, 1, 1), Vec3(8, -1.5, 0));
			//AddGameObject<Wave>(Vec3(0, 0, 0), Vec3(1, 1, 1), Vec3(16, -1.5, 0));
			
			auto BGM = App::GetApp()->GetXAudio2Manager();
			m_BGM = BGM->Start(L"SampleBGM.wav", XAUDIO2_LOOP_INFINITE, 0.4f);
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnDestroy() {
		//BGMのストップ
		auto BGM = App::GetApp()->GetXAudio2Manager();
		BGM->Stop(m_BGM);
	}


}
//end basecross

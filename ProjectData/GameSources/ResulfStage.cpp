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
	void ResulfStage::CreateViewLight() {//リザルト画面
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



	void ResulfStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			//					 ローテーション,スケール,ポジション
			//AddGameObject<Enemy>(Vec3(0.0f), Vec3(10.0f), Vec3(0.0f));

			AddGameObject<UIBase>(Vec3(0.0f,0.0f,0.0f), Vec3(100.0f,100.0f,100.0f), Vec2(0.0f,0.0f),0.0f);
		

			//シーン移動
			//App::GetApp()->GetScene<Scene>()->LoadStage(L"ToTitleStage");
		}
		catch (...) {

			throw;
		}
	}

}
//end basecross

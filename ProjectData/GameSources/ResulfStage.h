/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class ResulfStage : public Stage {
		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		ResulfStage() :Stage() {}
		virtual ~ResulfStage() {}
		//初期化
		virtual void OnCreate()override;
	};

	//コントローラー
	template<typename T>
	struct bInputHandler 
	{
		voidPushHandler
		{
			void Pushandle(const shared_ptr<T>& Obj)
			{
			//コントローラーの取得
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			  if (cntVec[0].bConnected) {
				  //Aボタン
				  if (cntVec[0].wPressedButtons & XINPUT_GAMEPAD_A)
				  {
					  obj->OnPushA();

				  }
			  }
		}

	};



}
//end basecross


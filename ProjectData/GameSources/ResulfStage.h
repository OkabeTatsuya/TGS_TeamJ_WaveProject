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
	class ResultStage : public Stage {
		//ビューの作成
		void CreateViewLight();

		shared_ptr<SoundItem> m_SE;
		shared_ptr<SoundItem> m_BGM;

		float m_Time=0;//Aボタン押して3秒後にステージ画面に遷移
		bool m_isPush;//Aボタン押して3秒後にステージ画面に遷移

		float m_Timer = 3;//コントローラー左スティック処理
		bool m_Push;//コントローラー左スティック処理

		wstring m_ResultUi[4];

		int m_ResultUiCount = 0;

		void m_ControllerA();


		Vec2 GetMoveVector();

	public:
		//構築と破棄
		ResultStage() :Stage() {}
		virtual ~ResultStage() {}
		//初期化
		virtual void OnCreate()override;

		virtual void OnUpdate()override;

		virtual void OnDestroy()override;

		//時間を決めて、シーンを遷移する
		void Sceneloader();
		//コントローラーを押す
		void Press();
		//BGMを流す
		void GetBGM();
		//SEを流す
		void GetSE();
	};

	//コントローラー
	template<typename T>
	struct bInputHandler 
	{

		void Pushandle(const shared_ptr<T>& Obj)
		{

		}

	};


}
//end basecross


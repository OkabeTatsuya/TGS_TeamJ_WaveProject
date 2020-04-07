/*!
@file MoveBG.h
@brief 動いてくる波
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MoveBG : public MoveSpriteBase {
	protected:
		//移動判定
		bool m_isMove;
		//画面外判定のｘ座標
		float m_offScreenX;

		wstring m_texture;
	public:
		MoveBG(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& scale,
			Vec3& position,
			wstring tex,
			float offScreenX);

		virtual void OnUpdate() override;
		virtual void OnCreate() override;

		//移動処理
		void Move();

		//
		//void Movement(shared_ptr<Transform> transPtr);

		//移動判定のゲッター
		bool GetIsMove();
		//移動判定のセッター
		void SetIsMove(bool move);
		//画面外判定
		void OffScreen();
	};

}
//end basecross

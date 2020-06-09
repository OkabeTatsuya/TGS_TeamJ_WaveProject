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

		Vec2 m_imageSize;
		wstring m_texture;
		vector<float> m_coordinate;

	public:
		MoveBG(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& position,
			Vec2& image,
			int&  layer,
			wstring tex,
			float offScreenX,
			float moveSpeed);

		virtual void OnUpdate() override;
		virtual void OnCreate() override;

		//移動処理
		void Move();
		//UVを使った移動処理
		void MoveTexture();

		//移動判定のゲッター
		bool GetIsMove();
		//移動判定のセッター
		void SetIsMove(bool move);
		//画面外判定
		void OffScreen();
	};

}
//end basecross

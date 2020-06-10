/*!
@file ScoreUpItem.h
@brief 動いてくる波
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ScoreUpItem : public MoveSpriteBase {
	protected:
		//移動判定
		bool m_isMove;
		//アイテム取得判定
		bool m_isGetItem;
		//画面外判定のｘ座標
		float m_offScreenX;

		Vec2 m_texSize;

		shared_ptr<SoundItem> m_SE;

	public:
		ScoreUpItem(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& position,
			Vec2 texSize,
			int&  layer
			);

		virtual void OnUpdate() override;
		virtual void OnCreate() override;
		virtual void OnDestroy() override;
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;

		//移動処理
		void Move();
		//移動判定のゲッター
		bool GetIsMove();
		//移動判定のセッター
		void SetIsMove(bool move);
		//画面外判定
		void OffScreen();

		void VisibleItem();

		void PassiveCollision();

		void PlaySE();
	};
}
//end basecross

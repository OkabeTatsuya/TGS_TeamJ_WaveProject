/*!
@file GoalObject.h
@brief ゲームクリアするオブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GoalObject : public MoveSpriteBase {
	protected:
		//移動判定
		bool m_isMove;
		float m_offsetPosX;
		wstring m_textureName;

	public:
		GoalObject(const shared_ptr<Stage>& StagePtr,
			Vec3& rotation,
			Vec3& scale,
			Vec3& position,
			wstring tex);

		virtual void OnCreate()override;

		virtual void OnUpdate()override;

		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;

		//ゲッターとセッター
		//移動判定のゲッター
		bool GetIsMove() { return m_isMove; }
		//移動判定のセッター
		void SetIsMove(bool move) { m_isMove = false; };

		//関数
		//オブジェクトを動かし、オフセットを超えたら止める
		void MoveObject();

	};

}
/*!
@file MoveBG.cpp
@brief 動く波の実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MoveBG::MoveBG(const shared_ptr<Stage>& stage,
		Vec3& rotation,
		Vec3& scale,
		Vec3& position) :
		MoveSpriteBase(stage,
			rotation, scale, position
		)
	{
		m_isMove = true;
		m_offScreenX = -10.0f;
	}

	void MoveBG::OnCreate() {
		DrawingImage(L"BGImage.png");
		auto transComp = GetComponent<Transform>();
		transComp->SetScale(m_scale);
		transComp->SetRotation(m_rotation);
		transComp->SetPosition(m_position);

	}

	void MoveBG::OnUpdate() {
		Move();
		OffScreen();
	}

	//画面外判定
	void MoveBG::OffScreen() {
		if (GetComponent<Transform>()->GetPosition().x <= m_offScreenX) {
			SetIsMove(false);
		}
	}

	//スプライト自体の移動処理
	//void MoveBG::Movement(shared_ptr<Transform> transPtr) {
	//	auto pos = transPtr->GetPosition();
	//	pos.x -= GameManager::GetInstance().GetGameSpeed() * App::GetApp()->GetElapsedTime();
	//	GetComponent<Transform>()->SetPosition(pos);
	//	//auto collision = AddComponent<CollisionObb>();
	//	//collision->SetAfterCollision(AfterCollision::None);
	//
	//	//collision->SetDrawActive(true);
	//}

	//移動処理
	void MoveBG::Move() {
		if (m_isMove) {
			Movement(GetComponent<Transform>());
		}
	}

	//移動判定のゲッター
	bool MoveBG::GetIsMove() {
		return m_isMove;
	}

	//移動判定のセッター
	void MoveBG::SetIsMove(bool move) {
		m_isMove = move;
	}

}
//end basecross

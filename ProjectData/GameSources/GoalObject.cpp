/*!
@file GoalObject.cpp
@brief ゲームクリアするオブジェクトの実態
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	GoalObject::GoalObject(const shared_ptr<Stage>& StagePtr,
		Vec3& rotation,
		Vec3& scale,
		Vec3& position) :
		MoveSpriteBase(StagePtr, rotation, scale, position)
	{
		m_offsetPosX = -6.0f;
	}

	void GoalObject::OnCreate() {
		DrawingImage(L"Red.png");

		auto transPtr = AddComponent<Transform>();
		transPtr->SetPosition(m_position);
		transPtr->SetRotation(m_rotation);
		transPtr->SetScale(m_scale);

		auto collision = AddComponent<CollisionObb>();
		collision->SetAfterCollision(AfterCollision::None);
		collision->SetDrawActive(true);

	}

	void GoalObject::OnUpdate() {
		MoveObject();
	}

	void GoalObject::OnCollisionEnter(shared_ptr<GameObject>& other) {
		if (other->FindTag(L"Player")) {
			GameManager::GetInstance().SetIsGameEnd(true);
			GetComponent<CollisionObb>()->SetUpdateActive(false);
		}
	}

	void GoalObject::MoveObject() {
		auto pos = GetComponent<Transform>()->GetPosition();
		if (pos.x >= m_offsetPosX) {
			Movement(GetComponent<Transform>());
		}
	}
}
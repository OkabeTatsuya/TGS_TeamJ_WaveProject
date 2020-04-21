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
		Vec3& position,
		wstring tex) :
		MoveSpriteBase(StagePtr, rotation, scale, position)
	{
		m_offsetPosX = -8.5f;
		m_textureName = tex;
	}

	void GoalObject::OnCreate() {
		DrawingImage(m_textureName);

		auto transPtr = AddComponent<Transform>();
		transPtr->SetPosition(m_position.x, m_position.y, -3.0f);
		transPtr->SetRotation(m_rotation);
		transPtr->SetScale(m_scale);

		auto collision = AddComponent<CollisionObb>();
		collision->SetAfterCollision(AfterCollision::None);
		collision->SetMakedSize(Vec3(0.5f, 15.0f, 1.0f));
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
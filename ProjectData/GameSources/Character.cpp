/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	Enemy::Enemy(const shared_ptr<Stage>& stage,
		Vec3& rotation,
		Vec3& scale,
		Vec3& position) :

		ObjectBase(stage,
			rotation, scale, position
		)
	{}

	void Enemy::OnCreate() {

		DrawingImage();
		auto transPtr = AddComponent<Transform>();
		transPtr->SetPosition(m_position);
		transPtr->SetScale(m_scale);
		transPtr->SetRotation(m_rotation);

		//SetTexture(L"");
	}

}
//end basecross

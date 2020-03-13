/*!
@file Character.cpp
@brief “®‚­”g‚Ì“–‚½‚è”»’è‚ÌŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
    WaveCollision::WaveCollision(const shared_ptr<Stage>& stage,
        Vec3& rotation,
        Vec3& scale,
        Vec3& position
        ):

        GameObject(stage),
        m_rotation(rotation),
        m_scale(scale),
        m_position(position)		
	{}

	void WaveCollision::OnCreate() {
		auto transPtr = AddComponent<Transform>();
		transPtr->SetPosition(m_position);
		transPtr->SetScale(m_scale);
		transPtr->SetRotation(m_rotation);

        
        auto collision = AddComponent<CollisionObb>();
        collision->SetDrawActive(true);
        collision->SetAfterCollision(AfterCollision::None);

        AddTag(L"Wave");

		//SetTexture(L"");
	}

    void WaveCollision::OnUpdate() {
        Move();
    }

    void WaveCollision::Move() {
        auto pos = GetComponent<Transform>()->GetPosition();
        pos.x -= m_moveSpeed * App::GetApp()->GetElapsedTime();
        GetComponent<Transform>()->SetPosition(pos);
    }

}
//end basecross

/*!
@file WaveCollision.cpp
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

        ObjectBase(stage,
            rotation, scale, position
        )
	{}

	void WaveCollision::OnCreate() {
		auto transPtr = AddComponent<Transform>();
		transPtr->SetPosition(m_position);
		transPtr->SetScale(m_scale);
		transPtr->SetRotation(m_rotation);

        
        auto collision = AddComponent<CollisionObb>();
        collision->SetDrawActive(true);
        collision->SetMakedSize(1);
        collision->SetAfterCollision(AfterCollision::None);


        AddTag(L"Wave");

		//SetTexture(L"");
	}

    void WaveCollision::OnUpdate() {
        Stop();
    }

    void WaveCollision::Stop() {
        auto wave = dynamic_pointer_cast<Wave>(GetComponent<Transform>()->GetParent());
        if (!wave->GetIsMove()) {
            GetComponent<CollisionObb>()->SetUpdateActive(false);
        }
    }

}
//end basecross

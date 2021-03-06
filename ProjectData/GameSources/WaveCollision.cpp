/*!
@file WaveCollision.cpp
@brief 動く波の当たり判定の実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
    WaveCollision::WaveCollision(const shared_ptr<Stage>& stage,
        Vec3& rotation,
        Vec3& scale,
        Vec3& position,
        wstring typeName
        ):

        ObjectBase(stage,
            rotation, scale, position
        ),
        m_typeName(typeName)
	{}

	void WaveCollision::OnCreate() {
		auto transPtr = AddComponent<Transform>();
		transPtr->SetPosition(m_position);
		transPtr->SetScale(m_scale);
		transPtr->SetRotation(m_rotation);

        
        auto collision = AddComponent<CollisionObb>();
        collision->SetAfterCollision(AfterCollision::None);


        AddTag(m_typeName);

		//SetTexture(L"");
	}

    void WaveCollision::OnUpdate() {
        Stop();
		AwakeCollision();
    }

    void WaveCollision::Stop() {
        auto wave = dynamic_pointer_cast<Wave>(GetComponent<Transform>()->GetParent());
        if (!wave->GetIsMove()) {
            GetComponent<CollisionObb>()->SetUpdateActive(false);
        }
    }

	void WaveCollision::AwakeCollision() {
		auto wave = dynamic_pointer_cast<Wave>(GetComponent<Transform>()->GetParent());
		if (!GetComponent<CollisionObb>()->GetUpdateActive() && wave->GetIsMove()) {
			GetComponent<CollisionObb>()->SetUpdateActive(true);
		}
	}

}
//end basecross

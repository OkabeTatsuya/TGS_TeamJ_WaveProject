#include "stdafx.h"
#include "Project.h"

namespace basecross {
    GroundWave::GroundWave(const shared_ptr<Stage>& stage,
        Vec3& rotation,
        Vec3& scale,
        Vec3& position) :

        ObjectBase(stage,
            rotation, scale, position
        )
    {}

    void GroundWave::OnCreate() {

        DrawingImage();
        auto transPtr = AddComponent<Transform>();
        transPtr->SetPosition(m_position);
        transPtr->SetScale(m_scale);
        transPtr->SetRotation(m_rotation);


        PsBoxParam param(transPtr->GetWorldMatrix(), 1.0f, false, PsMotionType::MotionTypeFixed);

        auto psPtr = AddComponent<RigidbodyBox>(param);
        psPtr->SetDrawActive(true);

        AddComponent<CollisionObb>()->SetDrawActive(true);

        AddTag(L"GroundWave");

        //SetTexture(L"");
    }

}
//end basecross

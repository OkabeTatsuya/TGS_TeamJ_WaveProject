#include "stdafx.h"
#include "Project.h"

namespace basecross {
   SeaCollision::SeaCollision(const shared_ptr<Stage>& stage,
        Vec3& rotation,
        Vec3& scale,
        Vec3& position) :

        ObjectBase(stage,
            rotation, scale, position
        )
    {}

    void SeaCollision::OnCreate() {
        auto transPtr = AddComponent<Transform>();
        transPtr->SetPosition(m_position);
        transPtr->SetScale(m_scale);
        transPtr->SetRotation(m_rotation);

        auto collision = AddComponent<CollisionObb>();
        //collision->SetDrawActive(true);
        collision->SetFixed(true);

        AddTag(L"Sea");

        //SetTexture(L"");
    }
   

}
//end basecross

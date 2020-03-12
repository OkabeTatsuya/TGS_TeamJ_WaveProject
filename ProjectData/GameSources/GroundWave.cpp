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

        DrawingImage(L"trace.png");
        auto transPtr = AddComponent<Transform>();
        transPtr->SetPosition(m_position);
        transPtr->SetScale(m_scale);
        transPtr->SetRotation(m_rotation);
        m_initYPos = m_position.y;

        auto collision = AddComponent<CollisionObb>();
        collision->SetDrawActive(true);
        collision->SetFixed(true);

        AddTag(L"GroundWave");

        auto gameobjects = GetStage()->GetGameObjectVec();
        for (auto obj : gameobjects) {
            auto player = dynamic_pointer_cast<Player>(obj);
            if (player) {
                m_moveSpeed = player->GetCurrentSpeed();
            }
        }


        //SetTexture(L"");
    }

    void GroundWave::OnUpdate() {
        auto pos = GetComponent<Transform>()->GetPosition();
        pos.x -= m_moveSpeed * App::GetApp()->GetElapsedTime();
        pos.y = m_initYPos;
        GetComponent<Transform>()->SetPosition(pos);
    }
   

}
//end basecross

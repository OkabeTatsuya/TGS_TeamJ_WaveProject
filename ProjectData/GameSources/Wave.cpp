/*!
@file Character.cpp
@brief “®‚­”g‚ÌŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
    Wave::Wave(const shared_ptr<Stage>& stage,
        Vec3& rotation,
        Vec3& scale,
        Vec3& position) :

        ObjectBase(stage,
            rotation, scale, position
        )
    {}

    void Wave::OnCreate() {


        DrawingImage(L"trace.png");
        auto transPtr = AddComponent<Transform>();
        transPtr->SetPosition(m_position);
        transPtr->SetScale(m_scale);
        transPtr->SetRotation(m_rotation);

        auto gameobjects = GetStage()->GetGameObjectVec();
        for (auto obj : gameobjects) {
            auto player = dynamic_pointer_cast<Player>(obj);
            if (player) {
                m_moveSpeed = player->GetCurrentSpeed();
            }
        }

        auto waveCol = GetStage()->AddGameObject<WaveCollision>(Vec3(0, 0, 0), Vec3(1, 1, 1), Vec3(m_position.x - 1, m_position.y, m_position.z));
        waveCol->GetComponent<Transform>()->SetParent(GetThis<Wave>());
        waveCol->GetComponent<Transform>()->SetPosition(Vec3(-1, 0, 0));
        auto parent = waveCol->GetComponent<Transform>()->GetParent();

        //SetTexture(L"");
    }

    void Wave::OnUpdate() {
        auto pos = GetComponent<Transform>()->GetPosition();
        pos.x -= m_moveSpeed * App::GetApp()->GetElapsedTime();
         GetComponent<Transform>()->SetPosition(pos);
    }
}
//end basecross

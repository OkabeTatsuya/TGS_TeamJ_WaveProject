/*!
@file SpriteBase.cpp
@brief �����X�v���C�g�����̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
    MoveSpriteBase::MoveSpriteBase(const shared_ptr<Stage>& stage,
        Vec3& rotation,
        Vec3& scale,
        Vec3& position) :

        ObjectBase(stage,
            rotation, scale, position
        )
    {}

    //�X�v���C�g���̂̈ړ�����
    void MoveSpriteBase::Movement(shared_ptr<Transform> transPtr) {
        auto pos = transPtr->GetPosition();
        pos.x -= GameManager::GetInstance().GetGameSpeed() * App::GetApp()->GetElapsedTime();
        GetComponent<Transform>()->SetPosition(pos);
    }
}
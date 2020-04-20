/*!
@file SpriteBase.cpp
@brief 動くスプライト生成の実態
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
    {
		m_objSpeed = 1.0f;
	}

    //スプライト自体の移動処理
    void MoveSpriteBase::Movement(shared_ptr<Transform> transPtr) {
        auto pos = transPtr->GetPosition();
        pos.x -= GameManager::GetInstance().GetGameSpeed() * App::GetApp()->GetElapsedTime() * m_objSpeed;
        GetComponent<Transform>()->SetPosition(pos);
    }
}
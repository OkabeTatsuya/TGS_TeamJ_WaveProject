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
    {}

    //スプライト自体の移動処理
    void MoveSpriteBase::Movement(shared_ptr<Transform> transPtr) {
        float moveSpeed = 0;
        auto gameobjects = GetStage()->GetGameObjectVec();
        for (auto obj : gameobjects) {
            auto player = dynamic_pointer_cast<Player>(obj);
            if (player) {
                moveSpeed = player->GetCurrentSpeed();
            }
        }
        auto pos = transPtr->GetPosition();
        pos.x -= moveSpeed * App::GetApp()->GetElapsedTime();
        GetComponent<Transform>()->SetPosition(pos);
    }
}
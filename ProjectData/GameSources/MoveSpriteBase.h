/*!
@file SpriteBase.h
@brief 動くスプライト生成クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class MoveSpriteBase : public ObjectBase {

    public:
        MoveSpriteBase(const shared_ptr<Stage>& stage,
            Vec3& rotation,
            Vec3& scale,
            Vec3& position);

        void Movement(shared_ptr<Transform> transPtr);

    };
}
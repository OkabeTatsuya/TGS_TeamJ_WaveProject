
/*!
@file GroundCollision.h
@brief 地面となる波
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class GroundCollision : public ObjectBase {
    public:
        GroundCollision(const shared_ptr<Stage>& stage,
            Vec3& rotation,
            Vec3& scale,
            Vec3& position);

        virtual void OnCreate() override;
    };
}
//end basecross

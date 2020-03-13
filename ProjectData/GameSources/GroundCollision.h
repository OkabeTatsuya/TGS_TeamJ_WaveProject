
/*!
@file Character.h
@brief ’n–Ê‚Æ‚È‚é”g
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

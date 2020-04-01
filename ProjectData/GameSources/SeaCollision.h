
/*!
@file GroundCollision.h
@brief ’n–Ê‚Æ‚È‚é”g
*/

#pragma once
#include "stdafx.h"
namespace basecross {
    class SeaCollision : public ObjectBase {
    public:
        SeaCollision(const shared_ptr<Stage>& stage,
            Vec3& rotation,
            Vec3& scale,
            Vec3& position);

        virtual void OnCreate() override;
    };
}
//end basecross

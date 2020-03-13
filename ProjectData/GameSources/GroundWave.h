
/*!
@file Character.h
@brief 地面となる波
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class GroundWave : public ObjectBase {
    protected:
        //移動速度
        float m_moveSpeed;
    public:
        GroundWave(const shared_ptr<Stage>& stage,
            Vec3& rotation,
            Vec3& scale,
            Vec3& position);

        virtual void OnCreate() override;
        virtual void OnUpdate() override;
    };
}
//end basecross

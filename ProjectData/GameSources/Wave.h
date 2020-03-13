/*!
@file Character.h
@brief “®‚¢‚Ä‚­‚é”g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class Wave : public ObjectBase {
    protected:
        float m_moveSpeed;
    public:
        Wave(const shared_ptr<Stage>& stage,
            Vec3& rotation,
            Vec3& scale,
            Vec3& position);

        virtual void OnCreate() override;
        virtual void OnUpdate() override;
    };
}
//end basecross

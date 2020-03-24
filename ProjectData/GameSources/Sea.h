/*!
@file Wave.h
@brief ’n–Ê‚ÌŠC
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class Sea : public ObjectBase {
    public:
        Sea(const shared_ptr<Stage>& stage,
            Vec3& rotation,
            Vec3& scale,
            Vec3& position);
        virtual void OnCreate() override;

    };
}
//end basecross

/*!
@file SpriteBase.h
@brief �����X�v���C�g�����N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class Fade : public UIBase {

    public:
        Fade(const shared_ptr<Stage>& stage,
            Vec3& rotation,
            Vec3& scale,
            Vec2& position,
            float& layer);

        virtual void OnCreate() override;
        virtual void OnUpdate() override;

    };
}
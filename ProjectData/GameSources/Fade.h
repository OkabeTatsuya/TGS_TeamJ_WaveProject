/*!
@file SpriteBase.h
@brief 動くスプライト生成クラス
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
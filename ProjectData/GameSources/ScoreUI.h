/*!
@file Character.h
@brief ÉXÉRÉAUI
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class ScoreUI : public UIBase {

    public:
        ScoreUI(const shared_ptr<Stage>& stage,
            Vec3& rotation,
            Vec3& scale,
            Vec2& position,
            float& layer,
            wstring tex);

        virtual void OnCreate() override;
        void SetNumber(int number);
    };
}
//end basecross

/*!
@file Character.h
@brief ÉXÉRÉAUI
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class ScoreUI : public UIBase {
        int m_number;
    public:
        ScoreUI(const shared_ptr<Stage>& stage,
            Vec3& rotation,
            Vec3& scale,
            Vec2& position,
            float& layer,
            wstring tex);

        virtual void OnCreate() override;
        void SetNumber(int number);
        int GetNumber() { return m_number; }
    };
}
//end basecross

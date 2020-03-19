/*!
@file Character.cpp
@brief スコアUIをまとめるパネル実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
    ScoreUIPanel::ScoreUIPanel(const shared_ptr<Stage>& stage,
        Vec3& rotation,
        Vec3& scale,
        Vec2& position,
        float& layer,
        wstring tex,
        int count) :
        UIBase(stage, rotation,
            scale,
            position,
            layer,
            tex),
        m_count(count)
    {}

    void ScoreUIPanel::OnCreate() {
        for (int i = 0; i < 7; i++) {
            auto scoreUI = GetStage()->AddGameObject<ScoreUI>(Vec3(m_rotation), Vec3(m_scale), Vec2(m_position.x - i * m_scale.x, m_position.y), float(m_layer), L"number.png");
            m_scoreUIs.push_back(scoreUI);
        }
    }

}
//end basecross

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
    {
    }

    void ScoreUIPanel::OnCreate() {
        for (int i = 0; i < m_count; i++) {
            auto scoreUI = GetStage()->AddGameObject<ScoreUI>(Vec3(m_rotation), Vec3(m_scale), Vec2(m_position.x - i * m_scale.x, m_position.y), float(m_layer), L"number.png");
            m_scoreUIs.push_back(scoreUI);
        }
        GameManager::GetInstance().SetScoreUIPanel(GetThis<ScoreUIPanel>());
    }

    void ScoreUIPanel::ScoreDraw(int score) {
        int mask = 10;
        for (int i = m_count-1; i >= 0; i--) {
            int digit = (int)pow(mask, i);
            int digitScore = score / digit;
            m_scoreUIs[i]->SetNumber(digitScore);
            score %= digit;
        }
    }

}
//end basecross

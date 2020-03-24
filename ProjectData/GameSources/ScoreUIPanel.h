/*!
@file Character.h
@brief スコアUIをまとめるパネル
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class ScoreUIPanel: public UIBase {
    private:
        //表示するUIの桁数
        const int m_count;
        //表示するUI達
        vector<shared_ptr<ScoreUI>> m_scoreUIs;
    public:
        ScoreUIPanel(const shared_ptr<Stage>& stage,
            Vec3& rotation,
            Vec3& scale,
            Vec2& position,
            float& layer,
            wstring tex,
            int count);


        virtual void OnCreate() override;

        void ScoreDraw(int score);
    };
}
//end basecross

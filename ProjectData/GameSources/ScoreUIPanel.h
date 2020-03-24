/*!
@file Character.h
@brief �X�R�AUI���܂Ƃ߂�p�l��
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class ScoreUIPanel: public UIBase {
    private:
        //�\������UI�̌���
        const int m_count;
        //�\������UI�B
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

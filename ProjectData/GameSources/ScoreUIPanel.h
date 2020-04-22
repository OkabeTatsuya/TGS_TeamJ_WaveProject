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
        //プレイヤーの上に表示するか否か
        bool m_isScorePlusUI;
        //プレイヤーの上に表示する際の表示時間上限
        float m_maxScorePlusDrawTime;
        //現在のプレイヤーの上に表示している時間
        float m_currentScorePlusDrawTime;
        //スコアプラスUI表示フラグ
        bool m_isScorePlusUIActive;
    public:
        ScoreUIPanel(const shared_ptr<Stage>& stage,
            Vec3& rotation,
            Vec3& scale,
            Vec2& position,
            float& layer,
            wstring tex,
            int count,
            bool isPlyaerPlusScore);


        virtual void OnCreate() override;
        virtual void OnUpdate() override;

        //スコア表示
        void ScoreDraw(int score);
        //スコアアップ時の表示
        void ScorePlusDraw();
        //スコアアップ時のプレイヤーのポジションとの相対関係
        void AdjustPosition(Vec3 playerPos);


    };
}
//end basecross

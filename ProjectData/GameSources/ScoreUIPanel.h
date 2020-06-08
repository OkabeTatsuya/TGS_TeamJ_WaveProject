/*!
@file Character.h
@brief スコアUIをまとめるパネル
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    class ScoreUIPanel: public UIBase {
    private:
        //初期位置
        float m_initPosX;
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
		//次の数字間の空白を調整するための倍率
		float m_addPosMagnification;
        //表示するスコアの桁数認識
        bool m_isFirstNumber;
        //最初の桁数
        int m_firstNumberDigit;
        //表示するスコア
        int m_score;
        //左詰めするマス数
        int m_adjustLeftPosCount;
        //右詰めフラグ
        bool m_isAdjustRight;
    public:
        ScoreUIPanel(const shared_ptr<Stage>& stage,
            Vec3& rotation,
            Vec3& scale,
            Vec2& position,
            float& layer,
            wstring tex,
            int count,
            bool isPlyaerPlusScore);

        ScoreUIPanel(const shared_ptr<Stage>& stage,
            Vec3& rotation,
            Vec3& scale,
            Vec2& position,
            float& layer,
            wstring tex,
            int count,
            bool isPlyaerPlusScore,
            bool isAdjustRight);


        virtual void OnCreate() override;
        virtual void OnUpdate() override;

        //スコア表示
        void ScoreDraw(int score);
        //スコアアップ時の表示
        void ScorePlusDraw();
        //スコアアップ時のプレイヤーのポジションとの相対関係
        void AdjustPosition(Vec3 playerPos);
        //表示桁数管理
        void ScoreCountJudge(int score);
        //左詰め処理
        void AdjustLeftPosition();
    };
}
//end basecross

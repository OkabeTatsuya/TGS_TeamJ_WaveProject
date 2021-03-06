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
        int count,
        bool isPlayerPlusScore) :
        UIBase(stage, rotation,
            scale,
            position,
            layer,
            tex),
        m_count(count),
        m_isScorePlusUI(isPlayerPlusScore)
    {
        m_currentScorePlusDrawTime = 0;
        m_maxScorePlusDrawTime = 1.0f;
        m_isScorePlusUIActive = false;
		m_addPosMagnification = 0.7f;
    }

    ScoreUIPanel::ScoreUIPanel(const shared_ptr<Stage>& stage,
        Vec3& rotation,
        Vec3& scale,
        Vec2& position,
        float& layer,
        wstring tex,
        int count,
        bool isPlayerPlusScore,
        bool isAdjustRight) :
        UIBase(stage, rotation,
            scale,
            position,
            layer,
            tex),
        m_count(count),
        m_isScorePlusUI(isPlayerPlusScore),
        m_isAdjustRight(isAdjustRight)
    {
        m_currentScorePlusDrawTime = 0;
        m_maxScorePlusDrawTime = 1.0f;
        m_isScorePlusUIActive = false;
        m_addPosMagnification = 0.7f;
    }




    void ScoreUIPanel::OnCreate() {
        m_initPosX = m_position.x;
        for (int i = 0; i < m_count; i++) {
            auto scoreUI = GetStage()->AddGameObject<ScoreUI>(Vec3(m_rotation), Vec3(m_scale), Vec2(m_position.x - i * (m_scale.x * m_addPosMagnification), m_position.y), float(m_layer), m_textureName);
            scoreUI->GetComponent<Transform>()->SetParent(GetThis<GameObject>());
            m_scoreUIs.push_back(scoreUI);
            if (m_isScorePlusUI){
				m_scoreUIs[i]->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);
			}
        }
        GameManager::GetInstance().SetScoreUIPanel(GetThis<ScoreUIPanel>());
    }

    void ScoreUIPanel::OnUpdate() {
        if (m_isScorePlusUI) {
            if (m_isScorePlusUIActive) {
                ScorePlusDraw();
            }
        }
    }

    void ScoreUIPanel::AdjustLeftPosition() {
        auto transPtr = GetComponent<Transform>();
        auto pos = transPtr->GetPosition();
        pos.x =  m_initPosX - (m_adjustLeftPosCount * m_scale.x * m_addPosMagnification);
        transPtr->SetPosition(Vec3(pos.x,pos.y,m_layer));
    }

    void ScoreUIPanel::ScoreCountJudge(int score) {
        m_adjustLeftPosCount = 0;
        m_isFirstNumber = false;
        int mask = 10;
        for (int i = m_count-1; i >= 0; i--) {
            int digit = (int)pow(mask, i);
            int digitScore = score / digit;
            if (digitScore == 0 && !m_isFirstNumber) {
                m_scoreUIs[i]->SetDrawActive(false);
                m_adjustLeftPosCount += 1;
            }
            else {
                m_scoreUIs[i]->SetDrawActive(true);
            }
            if (digitScore != 0) {
                m_isFirstNumber = true;
            }
            if (score == 0) {
                m_scoreUIs[0]->SetDrawActive(true);
                m_adjustLeftPosCount = m_count-1;
            }
        }
    }

    void ScoreUIPanel::ScoreDraw(int score) {
        ScoreCountJudge(score);
        if (!m_isAdjustRight) {
            AdjustLeftPosition();
        }
        if (m_isScorePlusUI) {
            m_currentScorePlusDrawTime = 0;
            m_isScorePlusUIActive = true;
            for (int i = 0; i < m_count; i++) {
                m_scoreUIs[i]->SetNumber(0);
            }
        }
        int mask = 10;
        for (int i = m_count-1; i >= 0; i--) {
            int digit = (int)pow(mask, i);
            int digitScore = score / digit;
            m_scoreUIs[i]->SetNumber(digitScore);
            score %= digit;
        }
    }

    void ScoreUIPanel::ScorePlusDraw() {
        m_currentScorePlusDrawTime += App::GetApp()->GetElapsedTime();
        for (int i = 0; i < m_count; i++) {
            m_scoreUIs[i]->GetComponent<PCTSpriteDraw>()->SetDrawActive(true);
        }
        if (m_currentScorePlusDrawTime >= m_maxScorePlusDrawTime) {
            for (int i = 0; i < m_count; i++) {
                m_scoreUIs[i]->GetComponent<PCTSpriteDraw>()->SetDrawActive(false);
                auto a = GetComponent<Transform>()->GetPosition();
                m_isScorePlusUIActive = false;
            }
            m_currentScorePlusDrawTime = 0;
        }
    }

    void ScoreUIPanel::AdjustPosition(Vec3 playerPos) {
        //座標調整
        float adjustXpos = 115;
        float adjustYpos = 80;
        //プレイヤーからどの程度浮かすか
        float upPos = 60;
        auto transPtr = GetComponent<Transform>();
        m_position = Vec3(playerPos.x * adjustXpos, playerPos.y * adjustYpos + upPos, transPtr->GetPosition().z);
        InitializeTransfrom();
    }

}
//end basecross

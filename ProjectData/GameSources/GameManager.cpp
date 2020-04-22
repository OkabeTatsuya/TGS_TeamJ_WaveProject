/*!
@file GameManager.cpp
@brief ゲームを管理するオブジェクト
*/

#include "stdafx.h"
#include "Project.h"
#include <iostream>
#include <fstream>
using namespace std;

namespace basecross {
	void GameManager::AddJumpScore(float magnification, float comboMagnification,bool isGreat) {
        comboMagnification += 1;
        if (isGreat) {
            float greatJumpMagnification = 2.0f;
            m_gameScore += (int)(m_baseJumpScore * magnification * comboMagnification * greatJumpMagnification);
        }
        else
	        m_gameScore += (int)(m_baseJumpScore * magnification * comboMagnification);
        m_scoreUpUIPanel->ScoreDraw(m_baseJumpScore * magnification * comboMagnification);
        m_scoreUIPanel->ScoreDraw(m_gameScore);
	}

	void GameManager::AddActionScore(float magnification, float comboMagnification) {
        comboMagnification += 1;
		m_gameScore += (int)(m_baseActionScore * magnification * comboMagnification);
        m_scoreUpUIPanel->ScoreDraw(m_baseJumpScore * magnification * comboMagnification);
        m_scoreUIPanel->ScoreDraw(m_gameScore);
	}

	void GameManager::DrawScore() {
		m_scoreUIPanel->ScoreDraw(m_gameScore);
	}
}
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
		int addScore = 0;
        if (isGreat) {
            float greatJumpMagnification = 2.0f;
			addScore = (int)(m_baseJumpScore * magnification * comboMagnification * greatJumpMagnification);
        }
        else
			addScore = (int)(m_baseJumpScore * magnification * comboMagnification);
 
		m_gameScore += addScore;
		m_scoreUpUIPanel->ScoreDraw(addScore);
        m_scoreUIPanel->ScoreDraw(m_gameScore);

		m_specialCount += addScore;
		SpecialCheck();
	}

	void GameManager::AddActionScore(float magnification, float comboMagnification) {
        comboMagnification += 1;
		m_gameScore += (int)(m_baseActionScore * magnification * comboMagnification);
        m_scoreUpUIPanel->ScoreDraw(m_baseJumpScore * magnification * comboMagnification);
        m_scoreUIPanel->ScoreDraw(m_gameScore);

		m_specialCount += (int)(m_baseActionScore * magnification * comboMagnification);
		SpecialCheck();
	}

	void GameManager::AddItemScore() {
		m_gameScore += m_itemScore;
		m_scoreUpUIPanel->ScoreDraw(m_itemScore);
		SpecialCheck();
	}

	void GameManager::DrawScore() {
		m_scoreUIPanel->ScoreDraw(m_gameScore);
	}

	void GameManager::SpecialCheck() {
		if (m_specialCount > m_maxSpecialCount) {
			m_isSpecialTime = true;
			m_specialCount = 0;
		}
	}

	void GameManager::ResetGame() {
		m_gameScore = 0;
		m_specialCount = 0;
		m_perfectJumpCount = 0;
		m_goodJumpCount = 0;
		m_isGameEnd = false;
		m_isStopSpawner = true;
		m_isSpecialTime = false;
	}

}
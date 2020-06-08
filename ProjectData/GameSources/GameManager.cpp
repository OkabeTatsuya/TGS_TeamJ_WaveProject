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
			AddJumpJudgeCount(JudgeName::en_Perfect);
		}
		else {
			addScore = (int)(m_baseJumpScore * magnification * comboMagnification);
			AddJumpJudgeCount(JudgeName::en_Good);
		}

		m_gameScore += addScore;
		m_scoreUpUIPanel->ScoreDraw(addScore);
        m_scoreUIPanel->ScoreDraw(m_gameScore);

		if (m_isSpecialTime) {
			m_specialJumpScore = addScore;
		}
		//SpecialCheck();
	}

	void GameManager::AddActionScore(float magnification, float comboMagnification, JumpActionType jumpActionType) {
        comboMagnification += 1;

		int addScore = (int)(m_baseActionScore[0] * magnification * comboMagnification);

		switch (jumpActionType)
		{
		case JumpActionType::en_ActionX:
			addScore = (int)(m_baseActionScore[0] * magnification * comboMagnification);
			break;
		case JumpActionType::en_ActionY:
			addScore = (int)(m_baseActionScore[1] * magnification * comboMagnification);
			break;
		case JumpActionType::en_ActionZ:
			addScore = (int)(m_baseActionScore[2] * magnification * comboMagnification);
			break;
		default:
			break;
		}

		m_gameScore += addScore;
        m_scoreUpUIPanel->ScoreDraw(addScore);
        m_scoreUIPanel->ScoreDraw(m_gameScore);

		if (m_isSpecialTime) {
			m_specialJumpScore += addScore;
		}
	}

	void GameManager::AddItemScore() {
		m_itemCount++;
		m_specialCount++;
		//SpecialCheck();
	}

	void GameManager::DrawScore() {
		m_scoreUIPanel->ScoreDraw(m_gameScore);
	}

	void GameManager::DrawClearScore(int stageNum) {
		m_scoreUIPanel->ScoreDraw(m_gameClearScore[stageNum]);
	}

	void GameManager::DrawJudgeCount(JudgeName judge) {
		switch (judge)
		{
		case basecross::en_Perfect:
			m_scoreUIPanel->ScoreDraw(m_perfectJumpCount);
			break;
		case basecross::en_Good:
			m_scoreUIPanel->ScoreDraw(m_goodJumpCount);
			break;
		default:
			break;
		}
	}

	void GameManager::DrawStageNum() {
		m_scoreUIPanel->ScoreDraw(m_selectStageNum + 1);
	}

	void GameManager::DrawNum(int num) {
		m_scoreUIPanel->ScoreDraw(num);
	}

	void GameManager::SpecialCheck() {
		if (m_specialCount >= m_maxSpecialCount) {
			m_isSpecialTime = true;
			m_specialCount -= m_maxSpecialCount;
		}
	}

	void GameManager::ResetGame() {
		m_gameScore = 0;
		m_specialCount = 0;
		m_perfectJumpCount = 0;
		m_goodJumpCount = 0;
		m_itemCount = 0;
		m_isGameEnd = false;
		m_isStopSpawner = true;
		m_isSpecialTime = false;
	}

	void GameManager::AddJumpJudgeCount(JudgeName judge) {
		if (judge == JudgeName::en_Perfect) {
			m_perfectJumpCount++;
		}
		else if (judge == JudgeName::en_Good) {
			m_goodJumpCount++;
		}
	}

}
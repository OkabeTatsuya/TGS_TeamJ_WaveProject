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
	void GameManager::AddJumpScore(float magnification, int combo) {
		float com = (float)combo;
		if (combo <= 0) {
			com = 1;
		}
		m_gameScore += (int)(m_baseJumpScore * magnification * com);
	}

	void GameManager::AddActionScore(float magnification, int combo) {
		float com = (float)combo;
		if (combo <= 0) {
			com = 1;
		}
		m_gameScore += (int)(m_baseActionScore * magnification * com);
	}


}
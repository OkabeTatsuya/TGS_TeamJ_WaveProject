/*!
@file GameManager.h
@brief ゲームを管理するオブジェクト
*/

#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	enum FlagName {
		en_GameStop = 0x0000,
		en_GameClear = 0x0001,
		en_GamePuse = 0X0002
	};

	class GameManager final {
	private:
		GameManager() {
			//m_isFrastStop = true;
			//m_isStopSpawner = true;
		}
		GameManager(const GameManager&);
		GameManager& operator = (const GameManager&);
		~GameManager() {};

		float m_gameSpeed;
		float m_startTimeCount;
		float m_maxStartTime;

		float m_saveNum;
		float m_stageNum;

		bool m_isFrastStop;
		bool m_isStopSpawner;
		bool m_isGameEnd;


	public :
		static GameManager& GetInstance() {
			static GameManager inst;
			return inst;
		}

		//ゲッター
		float GetGameSpeed() { return m_gameSpeed; }
		bool GetIsStopSpawner() { return m_isFrastStop; }
		bool GetIsGameEnd() { return m_isGameEnd; }


		//セッター
		void SetIsGameEnd(bool set) { m_isGameEnd = set; }

	};

}

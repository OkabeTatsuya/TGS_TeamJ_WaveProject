/*!
@file GameManager.h
@brief ゲームを管理するオブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum FlagName {
		en_GameStop = 0x0000,
		en_GameClear = 0x0001,
		en_GamePuse = 0X0002
	};

	class GameManager : public GameObject {

		UINT Game = 0;

	public:
		float m_gameSpeed;
		float m_startTimeCount;
		float m_maxStartTime;

		float m_saveNum;
		float m_stageNum;

		bool m_isFrastStop;
		bool m_isStopSpawner;
		bool m_isGameEnd;

		GameManager(const shared_ptr<Stage>& StagePtr);

		~GameManager() {};

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//デバッグ用の文字列表示を表示するために必要
		virtual void OnUpdate2() override;

		//ゲッター
		bool GetGameEnd() { return m_isGameEnd; }

		//セッター
		void SetGameEnd(bool set) { m_isGameEnd = set; }

		void LoadResultStage();

		void SaveGameData();

		void ReadGameData();

		void FrastTimeCount();

		void DebugHander();

		//デバッグ用の文字列表示処理
		void DebugString();
	};
}

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
			m_gameScore = 0;
			m_baseJumpScore = 100;
			m_baseActionScore = 200;
			m_selectStageNum = 0;

			m_isFirstStop = true;
			m_isStopSpawner = false;

		}
		GameManager(const GameManager&);
		GameManager& operator = (const GameManager&);
		~GameManager() {};

        //スコアパネル
        shared_ptr<ScoreUIPanel> m_scoreUIPanel;
        //スコアアップパネル
        shared_ptr<ScoreUIPanel> m_scoreUpUIPanel;

		//スコア
		int m_gameScore;

		//スコア加算の基準になる
		int m_baseJumpScore;
		int m_baseActionScore;

		float m_gameSpeed;


		float m_saveNum;

		//選ばれたステージの番号
		int m_selectStageNum;

		bool m_isFirstStop;
		bool m_isStopSpawner;
		bool m_isGameEnd;

	public :
		static GameManager& GetInstance() {
			static GameManager inst;
			return inst;
		}

		//ゲッター
		int GetGameScore() { return m_gameScore; }
		float GetGameSpeed() { return m_gameSpeed; }
		bool GetIsStopSpawner() { return m_isStopSpawner; }
		bool GetIsGameEnd() { return m_isGameEnd; }
		int GetSelectStageNum() { return m_selectStageNum; }

		//セッター
		void SetIsGameEnd(bool set) { m_isGameEnd = set; }
		void SetGameSpeed(float set ) { m_gameSpeed = set; }
		void SetIsStopSpawner(bool set) { m_isStopSpawner = set; }
        void SetScoreUIPanel(shared_ptr<ScoreUIPanel> set) { m_scoreUIPanel = set; }
        void SetScoreUpUIPanel(shared_ptr<ScoreUIPanel> set) { m_scoreUpUIPanel = set; }
		void ReSetGameScore() { m_gameScore = 0; }
		void SetSelectStageNum(int set) { m_selectStageNum = set; }

		//ジャンプのスコア加算処理
		///magnification 倍率、　combo 続けてジャンプした回数
        void AddJumpScore(float magnification, float comboMagnification, bool isGreat);

		//ジャンプアクションのスコア加算処理
		///magnification 倍率、　combo 続けてアクションした回数
		void AddActionScore(float magnification, float comboMagnification);

		//リザルトで使うスコアを写す処理
		void DrawScore();
	};

}

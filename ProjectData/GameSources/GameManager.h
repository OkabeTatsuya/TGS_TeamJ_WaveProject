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

	enum JudgeName {
		en_Perfect,
		en_Good
	};

	class GameManager final {
	private:
		GameManager() {
			m_gameScore = 0;
			m_gameClearScore = { 6000,7000,9000,10000 };

			m_baseJumpScore = 100;
			m_baseActionScore = 200;
			m_itemScore = 100;

			m_selectStageNum = 0;
			m_clearStageNum = 0;

			m_maxSpecialCount = 1000;

			m_isFirstStop = true;
			m_isStopSpawner = false;
			m_isSpecialJump = false;

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
		vector<int> m_saveScore;
		vector<int> m_gameClearScore;

		//スコア加算の基準になる
		int m_baseJumpScore;
		int m_baseActionScore;
		int m_itemScore;

		float m_gameSpeed;

		float m_saveNum;

		//スペシャルジャンプスコア計算用
		int m_specialCount;
		int m_maxSpecialCount;

		//スペシャルジャンプが出来る
		bool m_isSpecialTime;
		//スペシャルジャンプ中
		bool m_isSpecialJump;

		//ジャンプカウント
		int m_perfectJumpCount;
		int m_goodJumpCount;

		//アイテムカウント
		int m_itemCount;

		//選ばれたステージの番号
		int m_selectStageNum;
		//クリアしたステージの番号
		int m_clearStageNum;

		bool m_isFirstStop;
		bool m_isStopSpawner;
		bool m_isGameEnd;
		bool m_isGameClear;

	public :
		static GameManager& GetInstance() {
			static GameManager inst;
			return inst;
		}

		//ゲッター
		int GetGameScore()const { return m_gameScore; }
		int GetGameClearScore(int itr)const { return m_gameClearScore[itr]; }
		float GetGameSpeed()const { return m_gameSpeed; }
		bool GetIsStopSpawner()const { return m_isStopSpawner; }
		bool GetIsGameEnd()const { return m_isGameEnd; }
		int GetSelectStageNum() { return m_selectStageNum; }
		int GetClearStageNum()const { return m_clearStageNum; }
		vector<int> GetSaveScore() { return m_saveScore; }
		bool GetIsGameClear() { return m_isGameClear; }
		bool GetIsSpecialTime() { return m_isSpecialTime; }
		bool GetIsSpecialJump()const { return m_isSpecialJump; }
		int GetPerfectJumpCount()const { return m_perfectJumpCount; }
		int GetGoodJumpCount()const { return m_goodJumpCount; }
		int GetItemCount()const { return m_itemCount; }

		//セッター
		void SetIsGameEnd(bool set) { m_isGameEnd = set; }
		void SetGameSpeed(float set ) { m_gameSpeed = set; }
		void SetIsStopSpawner(bool set) { m_isStopSpawner = set; }
        void SetScoreUIPanel(shared_ptr<ScoreUIPanel> set) { m_scoreUIPanel = set; }
        void SetScoreUpUIPanel(shared_ptr<ScoreUIPanel> set) { m_scoreUpUIPanel = set; }
		void SetSelectStageNum(int set) { m_selectStageNum = set; }
		void SetClearStageNum(int set) { m_clearStageNum = set; }
		void SetSaveScore(vector<int> set) { m_saveScore = set; }
		void SetIsGameClear(bool set) { m_isGameClear = set; }
		void SetIsSpecialJump(bool set) { m_isSpecialJump = set; }
		void SetIsSpecialTime(bool set) { m_isSpecialTime = set; }
		void SetItemCount(int set) {  m_itemCount = set; }

		//ジャンプのスコア加算処理
		///magnification 倍率、　combo 続けてジャンプした回数
        void AddJumpScore(float magnification, float comboMagnification, bool isGreat);

		//ジャンプアクションのスコア加算処理
		///magnification 倍率、　combo 続けてアクションした回数
		void AddActionScore(float magnification, float comboMagnification);

		void AddItemScore();

		//リザルトで使うスコアを写す処理
		void DrawScore();

		//目標スコアを写す
		void DrawClearScore(int stageNum);

		//スペシャルジャンプ状態になったか確かめる
		void SpecialCheck();

		//ゲームの状態をリセットする
		void ResetGame();

		//ジャンプ回数を加算する（１回）
		//judge		判定の名前
		void AddJumpJudgeCount(JudgeName judge);
	};

}

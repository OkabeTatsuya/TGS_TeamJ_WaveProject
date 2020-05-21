/*!
@file GameManager.h
@brief �Q�[�����Ǘ�����I�u�W�F�N�g
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

        //�X�R�A�p�l��
        shared_ptr<ScoreUIPanel> m_scoreUIPanel;
        //�X�R�A�A�b�v�p�l��
        shared_ptr<ScoreUIPanel> m_scoreUpUIPanel;

		//�X�R�A
		int m_gameScore;
		vector<int> m_saveScore;
		vector<int> m_gameClearScore;

		//�X�R�A���Z�̊�ɂȂ�
		int m_baseJumpScore;
		int m_baseActionScore;
		int m_itemScore;

		float m_gameSpeed;

		float m_saveNum;

		//�X�y�V�����W�����v�X�R�A�v�Z�p
		int m_specialCount;
		int m_maxSpecialCount;

		//�X�y�V�����W�����v���o����
		bool m_isSpecialTime;
		//�X�y�V�����W�����v��
		bool m_isSpecialJump;

		//�W�����v�J�E���g
		int m_perfectJumpCount;
		int m_goodJumpCount;

		//�A�C�e���J�E���g
		int m_itemCount;

		//�I�΂ꂽ�X�e�[�W�̔ԍ�
		int m_selectStageNum;
		//�N���A�����X�e�[�W�̔ԍ�
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

		//�Q�b�^�[
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

		//�Z�b�^�[
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

		//�W�����v�̃X�R�A���Z����
		///magnification �{���A�@combo �����ăW�����v������
        void AddJumpScore(float magnification, float comboMagnification, bool isGreat);

		//�W�����v�A�N�V�����̃X�R�A���Z����
		///magnification �{���A�@combo �����ăA�N�V����������
		void AddActionScore(float magnification, float comboMagnification);

		void AddItemScore();

		//���U���g�Ŏg���X�R�A���ʂ�����
		void DrawScore();

		//�ڕW�X�R�A���ʂ�
		void DrawClearScore(int stageNum);

		//�X�y�V�����W�����v��ԂɂȂ������m���߂�
		void SpecialCheck();

		//�Q�[���̏�Ԃ����Z�b�g����
		void ResetGame();

		//�W�����v�񐔂����Z����i�P��j
		//judge		����̖��O
		void AddJumpJudgeCount(JudgeName judge);
	};

}

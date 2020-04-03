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

	class GameManager final {
	private:
		GameManager() {
			m_gameScore = 0;
			m_baseJumpScore = 100;
			m_baseActionScore = 200;

			m_isFirstStop = true;
			m_isStopSpawner = false;

		}
		GameManager(const GameManager&);
		GameManager& operator = (const GameManager&);
		~GameManager() {};

        //�X�R�A�p�l��
        shared_ptr<ScoreUIPanel> m_scoreUIPanel;

		//�X�R�A
		int m_gameScore;

		//�X�R�A���Z�̊�ɂȂ�
		int m_baseJumpScore;
		int m_baseActionScore;


		float m_gameSpeed;

		//�Q�[�����X�^�[�g�������̍d������
		float m_startTimeCount;
		float m_maxStartTime;

		float m_saveNum;
		float m_stageNum;

		bool m_isFirstStop;
		bool m_isStopSpawner;
		bool m_isGameEnd;


	public :
		static GameManager& GetInstance() {
			static GameManager inst;
			return inst;
		}

		//�Q�b�^�[
		int GetGameScore() { return m_gameScore; }
		float GetGameSpeed() { return m_gameSpeed; }
		bool GetIsStopSpawner() { return m_isStopSpawner; }
		bool GetIsGameEnd() { return m_isGameEnd; }


		//�Z�b�^�[
		void SetIsGameEnd(bool set) { m_isGameEnd = set; }
		void SetGameSpeed(float set ) { m_gameSpeed = set; }
		void SetIsStopSpawner(bool set) { m_isStopSpawner = set; }
        void SetScoreUIPanel(shared_ptr<ScoreUIPanel> set) { m_scoreUIPanel = set; }

		//�W�����v�̃X�R�A���Z����
		///magnification �{���A�@combo �����ăW�����v������
        void AddJumpScore(float magnification, float comboMagnification, bool isGreat);

		//�W�����v�A�N�V�����̃X�R�A���Z����
		///magnification �{���A�@combo �����ăA�N�V����������
		void AddActionScore(float magnification, float comboMagnification);
	};

}
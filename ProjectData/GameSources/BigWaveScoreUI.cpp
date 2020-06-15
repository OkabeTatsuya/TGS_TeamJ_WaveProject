/*!
@file BigWaveScoreUI.cpp
@brief BigWaveScoreUI‚ÌŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	BigWaveScoreUI::BigWaveScoreUI(const shared_ptr<Stage>& stage,
		Vec3& rotation,
		Vec3& scale,
		Vec2& position,
		float& layer,
		wstring tex):
		ImageUI(stage, rotation,
			scale,
			position,
			layer,
			tex)
	{
		m_isAnimUI = false;
		m_isPlaySE = false;
		m_animTimer = 0;
		m_animEndTime = 1.5f;
	}

	void BigWaveScoreUI::OnCreate() {
		DrawingImage();
		InitializeTransfrom();

		m_drawPtr = GetComponent<PCTSpriteDraw>();
		m_drawPtr->SetDrawActive(false);
		m_scoreUI = GetStage()->AddGameObject<ScoreUIPanel>(Vec3(0.0f), Vec3(100.0f, 100.0f, 1.0f), Vec2(100.0f, 0.0f), float(6.0f), L"GoldenNumbers.png", 4, false, true);

		m_scoreUI->SetDrawActive(false);
		auto scoreUI = m_scoreUI->GetScoreUIs();
		for each (auto ui in scoreUI)
		{
			ui->SetDrawActive(false);
		}

		for (int i = 0; i < 2; i++) {
			m_SE.push_back(nullptr);
		}
	}

	void BigWaveScoreUI::OnUpdate() {
		AnimUI();
		PlaySE();
	}

	void BigWaveScoreUI::OnDestroy() {
		for each ( auto se in m_SE)
		{
			auto audioManager = App::GetApp()->GetXAudio2Manager();
			audioManager->Stop(se);
		}
	}

	void BigWaveScoreUI::AnimUI() {
		auto& gm = GameManager::GetInstance();

		if (m_isAnimUI && m_animTimer < m_animEndTime) {
			m_animTimer += App::GetApp()->GetElapsedTime();
			auto color = m_drawPtr->GetDiffuse();
			int setDrawNum = gm.GetSpecialJumpScore();

			m_scoreUI->ScoreDraw(setDrawNum);

			m_drawPtr->SetDrawActive(true);
			m_scoreUI->SetDrawActive(true);
			auto scoreUI = m_scoreUI->GetScoreUIs();
		}
		else {
			m_drawPtr->SetDrawActive(false);
			m_scoreUI->SetDrawActive(false);
			auto scoreUI = m_scoreUI->GetScoreUIs();
			for each (auto ui in scoreUI)
			{
				ui->SetDrawActive(false);
			}
			m_animTimer = 0;
			m_isAnimUI = false;

		}

		if (!gm.GetIsSpecialTime() && !m_isAnimUI) {
			gm.SetSpecialJumpScore(0);
		}
	};

	void BigWaveScoreUI::PlaySE() {
		if (m_isPlaySE) {
			vector<wstring> audienceSE = { L"se_GameClear.wav" , L"se_GameOver.wav" };
			vector<wstring> seStr = { audienceSE[1], L"decision16.wav" };
			if (GameManager::GetInstance().GetSpecialJumpScore() != 0) {
				seStr = { audienceSE[0], L"decision16.wav" };
			}

			vector<float> seVol = { 0.9f, 0.9f };
			auto audioManager = App::GetApp()->GetXAudio2Manager();
			for (int i = 0; i < m_SE.size(); i++) {
				m_SE[i] = audioManager->Start(seStr[i], 0, seVol[i]);
			}
			m_isPlaySE = false;
		}
	}

	void BigWaveScoreUI::ResetState() {
		m_isAnimUI = true;
		m_isPlaySE = true;
	}

}
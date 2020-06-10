/*!
@file CutInUI.cpp
@brief ÉXÉRÉAUIÇÃé¿ëÃ
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	CutInUI::CutInUI(const shared_ptr<Stage>& stage,
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
		m_SE = { nullptr, nullptr };
		m_isPlaySE = { false, false };

		m_isAnimUI = false;
		m_animTimer = 0;
		m_animPlayTime = 0.5f;
		m_animEndTime = 2.0f;
	}

	void CutInUI::OnCreate() {
		DrawingImage();
		InitializeTransfrom();

		auto drawPtr = GetComponent<PCTSpriteDraw>();
		drawPtr->SetDrawActive(false);
	}

	void CutInUI::OnUpdate() {
		AnimUI();
	}

	void CutInUI::OnDestroy() {

	}

	void CutInUI::AnimUI() {
		auto drawPtr = GetComponent<PCTSpriteDraw>();
		if (m_isAnimUI) {
			m_animTimer += App::GetApp()->GetElapsedTime();
			if (m_animTimer > m_animPlayTime) {
				if (m_animTimer < m_animEndTime) {
					auto color = drawPtr->GetDiffuse();
					PlaySE(0, L"decision16.wav", 1.0f);
					PlaySE(1, L"Voice1_11.wav", 1.0f);
					drawPtr->SetDrawActive(true);
				}
				else {
					drawPtr->SetDrawActive(false);
					m_animTimer = 0;
					m_isAnimUI = false;
				}
			}
		}
	};

	void CutInUI::PlaySE(int seNum, wstring seName, float seVol) {
		if (m_isPlaySE[seNum] == false) {
			auto audioManager = App::GetApp()->GetXAudio2Manager();
			m_SE[seNum] = audioManager->Start(seName, 0, seVol);
			m_isPlaySE[seNum] = true;
		}
	}

	void CutInUI::ResetState() {
		m_isAnimUI = true;

		for(int i = 0; i < m_isPlaySE.size(); i++)
		{
			m_isPlaySE[i] = false;
		}
	}

}
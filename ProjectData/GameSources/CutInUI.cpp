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
		m_isAnimUI = false;
		m_animTimer = 0;
		m_animEndTime = 1.5f;
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

		if (m_isAnimUI && m_animTimer < m_animEndTime) {
			m_animTimer += App::GetApp()->GetElapsedTime();
			auto color = drawPtr->GetDiffuse();

			drawPtr->SetDrawActive(true);
		}
		else {
			drawPtr->SetDrawActive(false);
			m_animTimer = 0;
			m_isAnimUI = false;
		}
	};

	void CutInUI::ResetState() {
		m_isAnimUI = true;
	}

}
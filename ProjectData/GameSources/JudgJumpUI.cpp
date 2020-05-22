/*!
@file JudgJumpUI.cpp
@brief ƒWƒƒƒ“ƒv‚Ì”»’è‚ð•\Ž¦‚·‚éUI
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	JudgJumpUI::JudgJumpUI(const shared_ptr<Stage>& stage,
		Vec3& rotation,
		Vec3& scale,
		Vec2& position,
		float& layer,
		wstring tex) :

		UIBase(stage, rotation,
			scale,
			position,
			layer,
			tex)
	{
		m_visibleTimer = 0.0f;
		m_maxVisibleTime = 1.0f;
		m_visibleColor = Col4(1.0f);
		m_AdjustPos = Vec3(80.0f, 80.0f, 0.0f);
	}

	void JudgJumpUI::OnCreate() {
		DrawingImage();
		InitializeTransfrom();

		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 0.0f));
	}

	void JudgJumpUI::OnUpdate() {
		VisibleController();
	}

	void JudgJumpUI::SetingPos(Vec3 pos) {
		m_position = Vec2(pos.x * m_AdjustPos.x, pos.y * m_AdjustPos.y);
		InitializeTransfrom();
	}

	void JudgJumpUI::VisibleUI(wstring imageName, Vec3 pos) {
		auto drawPtr = GetComponent<PCTSpriteDraw>();
		drawPtr->SetTextureResource(imageName);
		drawPtr->SetDiffuse(m_visibleColor);
		SetingPos(pos);
		m_isVisible = true;
	}

	void JudgJumpUI::VisibleController() {
		if (m_isVisible) {
			if (m_visibleTimer < m_maxVisibleTime) {
				m_visibleTimer += App::GetApp()->GetElapsedTime();
			}
			else {
				m_visibleTimer = 0.0f;
				auto drawPtr = GetComponent<PCTSpriteDraw>();
				drawPtr->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 0.0f));
				m_isVisible = false;
			}
		}
	}
}
/*!
@file FlashingUI.cpp
@brief スコアUIの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	FlashingUI::FlashingUI(const shared_ptr<Stage>& stage,
		Vec3& rotation,
		Vec3& scale,
		Vec2& position,
		float& layer,
		wstring tex,
		float flashingSpeed) :

		UIBase(stage, rotation,
			scale,
			position,
			layer,
			tex),
		m_flashSpeed(flashingSpeed)
	{
		m_totalTime = 0.0f;
		m_nowColor = Col4(1.0f);
	}

	void FlashingUI::OnCreate() {
		DrawingImage();
	}

	void FlashingUI::OnUpdate() {
		FlashingImage();
	}

	//画像を点滅させる処理
	void FlashingUI::FlashingImage() {
		auto ptrDraw = GetComponent<PCTSpriteDraw>();

		m_totalTime += App::GetApp()->GetElapsedTime() * m_flashSpeed;

		if (m_totalTime >= XM_PI) {
			m_totalTime = 0;
		}

		m_nowColor.w = sinf(m_totalTime) * 0.9f;

		ptrDraw->SetDiffuse(m_nowColor);
	}
}
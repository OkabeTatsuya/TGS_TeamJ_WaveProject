/*!
@file SpecialJumpUI.cpp
@brief スコアUIの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	SpecialJumpUI::SpecialJumpUI(const shared_ptr<Stage>& stage,
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
		m_totalTime = 0.0f;
		m_nowColor = Col4(1.0f);
		m_maxColorA = 0.7f;
		m_speed = 2.0f;
	}

	void SpecialJumpUI::OnCreate() {
		DrawingImage();
		InitializeTransfrom();

		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		ptrDraw->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 0.0f));
	}

	void SpecialJumpUI::OnUpdate() {
		FlashingImage();
	}

	//画像を点滅させる処理
	void SpecialJumpUI::FlashingImage() {
		auto ptrDraw = GetComponent<PCTSpriteDraw>();
		auto color = ptrDraw->GetDiffuse();
		bool isSpecialTime = GameManager::GetInstance().GetIsSpecialTime();
		float delta = App::GetApp()->GetElapsedTime();

		if (isSpecialTime) {
			if (color.w < m_maxColorA) {
				color.w += delta * m_speed;
			}
			else {
				color.w = m_maxColorA;
			}
		}
		else {
			if (color.w > 0.0f) {
				color.w -= delta * m_speed;
			}
			else {
				color.w = 0.0f;
			}
		}

		ptrDraw->SetDiffuse(color);
	}
}
/*!
@file FlashingUI.h
@brief “_–Å‚·‚éUI
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class FlashingUI : public UIBase {
		float m_totalTime;
		float m_flashSpeed;
		Col4 m_nowColor;

	public:
		FlashingUI(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& scale,
			Vec2& position,
			float& layer,
			wstring tex,
			float flashingSpeed);

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//‰æ‘œ‚ğ“_–Å‚³‚¹‚éˆ—
		void FlashingImage();
	};
}
//end basecross

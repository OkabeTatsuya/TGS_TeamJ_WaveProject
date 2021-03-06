/*!
@file FlashingUI.h
@brief 点滅するUI
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class FlashingUI : public UIBase {
	protected:
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

		//画像を点滅させる処理
		void FlashingImage();
	};
}
//end basecross

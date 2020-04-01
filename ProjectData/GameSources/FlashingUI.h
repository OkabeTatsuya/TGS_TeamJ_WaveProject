/*!
@file FlashingUI.h
@brief �_�ł���UI
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

		//�摜��_�ł����鏈��
		void FlashingImage();
	};
}
//end basecross

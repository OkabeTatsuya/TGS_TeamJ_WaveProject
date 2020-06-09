/*!
@file SpecialJumpUI.h
@brief �_�ł���UI
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SpecialJumpUI : public UIBase {
	protected:
		float m_totalTime;
		Col4 m_nowColor;
		bool m_isSpecialJump;
		float m_maxColorA;
		float m_speed;
	public:
		SpecialJumpUI(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& scale,
			Vec2& position,
			float& layer,
			wstring tex);

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		//�摜��_�ł����鏈��
		void FlashingImage();
	};
}
//end basecross

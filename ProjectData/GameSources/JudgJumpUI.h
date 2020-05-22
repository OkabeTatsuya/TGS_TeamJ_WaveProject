/*!
@file JudgJumpUI.h
@brief ƒWƒƒƒ“ƒv”»’è•\Ž¦UI
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class JudgJumpUI : public UIBase {
	protected:
		float m_visibleTimer;
		float m_maxVisibleTime;

		Col4 m_visibleColor;
		bool m_isSpecialJump;
		Vec3 m_AdjustPos;
		bool m_isVisible;

	public:
		JudgJumpUI(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& scale,
			Vec2& position,
			float& layer,
			wstring tex);

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void SetingPos(Vec3 pos);

		void VisibleUI(wstring imageName, Vec3 pos);

		void VisibleController();
	};
}
//end basecross

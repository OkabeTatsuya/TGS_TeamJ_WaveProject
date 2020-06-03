/*!
@file CutInUI.h
@brief ÉXÉRÉAUI
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class CutInUI : public ImageUI {
		shared_ptr<SoundItem> m_voiceSE;

		bool m_isAnimUI;
		float m_animSpeed;
		float m_animTimer;
		float m_animEndTime;
	public:
		CutInUI(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& scale,
			Vec2& position,
			float& layer,
			wstring tex);

		virtual void OnCreate() override;

		virtual void OnUpdate() override;

		virtual void OnDestroy() override;

		void AnimUI();

		void ResetState();
	};
}
//end basecross

#pragma once
#include "stdafx.h"

namespace basecross {
	class TitleAnimationUI : public ImageUI {

	public:
		TitleAnimationUI(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& scale,
			Vec2& position,
			float& layer,
			wstring tex);

		Vec3 m_defaultPos;

		bool m_isMoveContll;

		void MoveUI();

		virtual void OnCreate() override;

		virtual void OnUpdate() override;

	};
}
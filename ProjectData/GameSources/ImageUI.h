/*!
@file ScoreUI.h
@brief ÉXÉRÉAUI
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ImageUI : public UIBase {

	public:
		ImageUI(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& scale,
			Vec2& position,
			float& layer,
			wstring tex);

		virtual void OnCreate() override;

		void ChangeImage(wstring tex);
	};
}
//end basecross

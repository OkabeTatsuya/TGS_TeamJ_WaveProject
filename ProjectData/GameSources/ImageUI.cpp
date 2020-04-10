/*!
@file Character.cpp
@brief ÉXÉRÉAUIÇÃé¿ëÃ
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	ImageUI::ImageUI(const shared_ptr<Stage>& stage,
		Vec3& rotation,
		Vec3& scale,
		Vec2& position,
		float& layer,
		wstring tex):
		UIBase(stage, rotation,
			scale,
			position,
			layer,
			tex)
	{}

	void ImageUI::OnCreate() {
		DrawingImage();
		InitializeTransfrom();
	}
}
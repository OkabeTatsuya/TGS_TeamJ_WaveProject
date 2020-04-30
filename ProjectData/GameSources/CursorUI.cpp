#include "stdafx.h"
#include "Project.h"

namespace basecross {

	CursorUI::CursorUI(const shared_ptr<Stage>& stage,

		Vec3& rotation,
		Vec3& scale,
		Vec2& position,
		float& layer,
		wstring tex,
		float flashingSpeed):

		FlashingUI(stage, rotation,
			scale,
			position,
			layer,
			tex,
			flashingSpeed)

	{
		m_totalTime = 0.0f;
		m_nowColor = Col4(1.0f);
	}

	void CursorUI::OnUpdate(){
		FlashingImage();//“_–Å
	}

	void CursorUI::OnCreate() {
		DrawingImage();
		InitializeTransfrom();
	}


}
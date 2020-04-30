#pragma once
#include "stdafx.h"

namespace basecross {

	class CursorUI : public FlashingUI{  //public FlashingUIでFlashingUIを継承する
	protected:
		float m_FlashingCursorUI;//オブジェクト化


	public:
		CursorUI(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& scale,
			Vec2& position,
			float& layer,
			wstring tex,
			float flashingSpeed);


		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};

}
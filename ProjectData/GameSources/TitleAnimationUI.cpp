#include "stdafx.h"
#include "Project.h"

namespace basecross {
	TitleAnimationUI::TitleAnimationUI(const shared_ptr<Stage>& stage,
		Vec3& rotation,
		Vec3& scale,
		Vec2& position,
		float& layer,
		wstring tex) :
		ImageUI(stage, rotation,
			scale,
			position,
			layer,
			tex)
	{
		m_isMoveContll = true;
	}

	void TitleAnimationUI::MoveUI() {
		//移動上限を決める(右に移動する）
		if (m_isMoveContll) {
			//スピード調整
			m_position.x += 3.0f;
			auto ptrTransform = GetComponent<Transform>();
			ptrTransform->SetPosition(m_position.x, m_position.y, 0.0f);
			//移動処理
			if (m_position.x >= m_defaultPos.x + 1040.0f) {
				m_isMoveContll = false;
			}
		}
		//下限まで動く処理（左に移動する）
		else {
			//スピード調整
			m_position.x -= 3.0f;
			auto ptrTransform = GetComponent<Transform>();
			ptrTransform->SetPosition(m_position.x, m_position.y, 0.0f);
			//移動処理
			if (m_position.x <= m_defaultPos.x - 50.0f) {
				m_isMoveContll = true;
			}
		}
	}

	void TitleAnimationUI::OnCreate() {
		DrawingImage();
		InitializeTransfrom();
		m_defaultPos = m_position;
	}

	void TitleAnimationUI::OnUpdate() {
		MoveUI();
	}
}
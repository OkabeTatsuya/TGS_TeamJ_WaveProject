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
		//�ړ���������߂�
		if (m_isMoveContll) {
			//�X�s�[�h����
			m_position.y += 3.0f;
			auto ptrTransform = GetComponent<Transform>();
			ptrTransform->SetPosition(m_position.x, m_position.y, 0.0f);
			//�ړ�����
			if (m_position.y >= m_defaultPos.y + 300.0f) {
				m_isMoveContll = false;
			}
		}
		//�����܂œ�������
		else {
			//�X�s�[�h����
			m_position.y -= 3.0f;
			auto ptrTransform = GetComponent<Transform>();
			ptrTransform->SetPosition(m_position.x, m_position.y, 0.0f);
			//�ړ�����
			if (m_position.y <= m_defaultPos.y - 100.0f) {
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
/*!
@file MoveBG.cpp
@brief �����g�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MoveBG::MoveBG(const shared_ptr<Stage>& stage,
		Vec3& rotation,
		Vec3& scale,
		Vec3& position) :
		MoveSpriteBase(stage,
			rotation, scale, position
		)
	{
		m_isMove = true;
		m_offScreenX = -10.0f;
	}

	void MoveBG::OnCreate() {
		DrawingImage(L"BGImage.png");
		auto transComp = GetComponent<Transform>();
		transComp->SetScale(m_scale);
		transComp->SetRotation(m_rotation);
		transComp->SetPosition(m_position);

	}

	void MoveBG::OnUpdate() {
		Move();
		OffScreen();
	}

	//��ʊO����
	void MoveBG::OffScreen() {
		if (GetComponent<Transform>()->GetPosition().x <= m_offScreenX) {
			SetIsMove(false);
		}
	}

	//�X�v���C�g���̂̈ړ�����
	//void MoveBG::Movement(shared_ptr<Transform> transPtr) {
	//	auto pos = transPtr->GetPosition();
	//	pos.x -= GameManager::GetInstance().GetGameSpeed() * App::GetApp()->GetElapsedTime();
	//	GetComponent<Transform>()->SetPosition(pos);
	//	//auto collision = AddComponent<CollisionObb>();
	//	//collision->SetAfterCollision(AfterCollision::None);
	//
	//	//collision->SetDrawActive(true);
	//}

	//�ړ�����
	void MoveBG::Move() {
		if (m_isMove) {
			Movement(GetComponent<Transform>());
		}
	}

	//�ړ�����̃Q�b�^�[
	bool MoveBG::GetIsMove() {
		return m_isMove;
	}

	//�ړ�����̃Z�b�^�[
	void MoveBG::SetIsMove(bool move) {
		m_isMove = move;
	}

}
//end basecross

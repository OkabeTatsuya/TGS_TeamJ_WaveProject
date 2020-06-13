/*!
@file MoveBG.cpp
@brief �����g�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MoveBG::MoveBG(const shared_ptr<Stage>& stage,
		Vec3& rotation,
		Vec3& position,
		Vec2& image,
		int&  layer,
		wstring tex,
		float offScreenX,
		float moveSpeed) :
		MoveSpriteBase(stage,
			rotation, Vec3(1.0f), position, layer),
		m_texture(tex),
		m_offScreenX(offScreenX),
		m_imageSize(image)
	{
		m_isMove = true;
		m_objSpeed = moveSpeed;
		m_offScreenX = -10.0f;

		m_coordinate = {
			0.0f,
			1.0f,
			0.0f,
			1.0f
		};
	}

	void MoveBG::OnCreate() {
		DrawingImage(m_texture, m_imageSize);
		auto transComp = GetComponent<Transform>();
		transComp->SetScale(m_scale);
		transComp->SetRotation(m_rotation);
		transComp->SetPosition(m_position);

	}

	void MoveBG::OnUpdate() {
		//Move();
		MoveTexture();
		OffScreen();
	}

	//��ʊO����
	void MoveBG::OffScreen() {
		if (GetComponent<Transform>()->GetPosition().x <= m_offScreenX) {
			SetIsMove(false);
		}
	}

	void MoveBG::MoveTexture() {
		Col4 color(1, 1, 1, 1);

		for (int i = 0; i < m_vertices.size(); i++)
		{
			m_coordinate[i] += GameManager::GetInstance().GetGameSpeed() * App::GetApp()->GetElapsedTime() * m_objSpeed;
			m_vertices[i].textureCoordinate.x = m_coordinate[i];
		}

		vector<uint16_t> indices =
		{
			0,1,2,
			2,1,3,
		};

		auto drawComp = GetComponent<PCTStaticDraw>();
		drawComp->CreateOriginalMesh<VertexPositionColorTexture>(m_vertices, indices);
	}

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

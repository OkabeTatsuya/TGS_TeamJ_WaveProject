/*!
@file UIBase.cpp
@brief �Q�[���I�u�W�F�N�g�e�N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	UIBase::UIBase(const shared_ptr<Stage>& stage,
		Vec3& rotation,
		Vec3& scale,
		Vec2& position,
		float& layer) :
		GameObject(stage),
		m_rotation(rotation),
		m_scale(scale),
		m_position(Vec3(position.x, position.y, layer))
	{
		//�G���[���N���Ȃ��悤������
		m_textureName = L"trace.png";
	}

	void UIBase::DrawingImage() {
		Col4 color(1, 1, 1, 1);
		Vec2 tipSize = Vec2(1.0f, 1.0f);

		float halfSize = 0.5f;
		vector<VertexPositionColorTexture> vertices = {
			{VertexPositionColorTexture(Vec3(0,halfSize,0),Col4(1.0f,1.0f,1.0f,1.0f),Vec2(0.0f,0.0f))},
			{VertexPositionColorTexture(Vec3(halfSize*2.0f,halfSize,0),Col4(1.0f,1.0f,1.0f,1.0f),Vec2(1.0f,0.0f))},
			{VertexPositionColorTexture(Vec3(0,-halfSize,0),Col4(1.0f,1.0f,1.0f,1.0f),Vec2(0.0f,1.0f))},
			{VertexPositionColorTexture(Vec3(halfSize*2.0f,-halfSize,0),Col4(1.0f,1.0f,1.0f,1.0f),Vec2(1.0f,1.0f))}
		};
		vector<uint16_t> indices = { 0,1,2,1,3,2 };
		// �e�N�X�`���̓\��t��
		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);
		drawComp->SetSamplerState(SamplerState::LinearWrap);

		///�e�N�X�`���̎擾�A�\��t��
		m_textureName = L"trace.png";
		drawComp->SetTextureResource(m_textureName);
		this->SetAlphaActive(true);
	}

	void UIBase::OnCreate() {
		DrawingImage();

		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_scale);
		ptrTransform->SetRotation(0, 0, 0);
		ptrTransform->SetPosition(m_position);

		ptrTransform->SetPivot(0.0f, 0.0f, 0.0f);

	}

}
//end basecross

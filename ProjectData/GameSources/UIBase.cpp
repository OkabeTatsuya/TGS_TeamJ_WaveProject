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
		float& layer,
		wstring tex) :
		GameObject(stage),
		m_rotation(rotation),
		m_scale(scale),
		m_position(position),
		m_layer(layer),
		m_textureName(tex)
	{
		//�G���[���N���Ȃ��悤������
		//m_textureName = L"trace.png";
	}

	void UIBase::DrawingImage() {
		Col4 color(1, 1, 1, 1);
		Vec2 tipSize = Vec2(1.0f, 1.0f);

		float halfSize = 0.5f;
		vector<VertexPositionColorTexture> vertices = {
			{VertexPositionColorTexture(Vec3(-halfSize,halfSize,0),color,Vec2(0.0f,0.0f))},
			{VertexPositionColorTexture(Vec3(halfSize,halfSize,0),color,Vec2(1.0f,0.0f))},
			{VertexPositionColorTexture(Vec3(-halfSize,-halfSize,0),color,Vec2(0.0f,1.0f))},
			{VertexPositionColorTexture(Vec3(halfSize,-halfSize,0),color,Vec2(1.0f,1.0f))}
		};
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };

		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetPivot(0.0f, 0.0f, 0.0f);

		// �e�N�X�`���̓\��t��
		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);
		drawComp->SetSamplerState(SamplerState::LinearWrap);

		///�e�N�X�`���̎擾�A�\��t��
		drawComp->SetTextureResource(m_textureName);
		this->SetAlphaActive(true);

		//auto defColor = Col4(1, 1, 1, 1);
		//drawComp->SetDiffuse(defColor);
		SetDrawLayer((int)m_layer);
	}

	//�g�����X�t�H�[����ݒ�
	void UIBase::InitializeTransfrom() {
		auto ptrTransform = GetComponent<Transform>();
		ptrTransform->SetScale(m_scale);
		ptrTransform->SetRotation(m_rotation);
		ptrTransform->SetPosition(m_position.x, m_position.y, 0.0f);
	}


	void UIBase::OnCreate() {
		DrawingImage();
		InitializeTransfrom();
	}

}
//end basecross

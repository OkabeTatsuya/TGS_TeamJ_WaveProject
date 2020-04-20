/*!
@file ObjectBase.cpp
@brief �Q�[���I�u�W�F�N�g�e�N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	ObjectBase::ObjectBase(const shared_ptr<Stage>& stage,
		Vec3& rotation,
		Vec3& scale,
		Vec3& position) :
	GameObject(stage),
		m_rotation(rotation),
		m_scale(scale),
		m_position(position)
	{
		//�G���[���N���Ȃ��悤������
		m_textureName = L"trace.png";
	}

	void ObjectBase::DrawingImage(wstring texStr) {
        m_textureName = texStr;
		Col4 color(1, 1, 1, 1);
		Vec2 tipSize = Vec2(1.0f, 1.0f);

		m_vertices =
		{
			{Vec3(-0.5f,+0.5f,0.0f),color,Vec2(0		,0)},
			{Vec3(+0.5f,+0.5f,0.0f),color,Vec2(tipSize.x,0)},
			{Vec3(-0.5f,-0.5f,0.0f),color,Vec2(0		,tipSize.y)},
			{Vec3(+0.5f,-0.5f,0.0f),color,Vec2(tipSize.x,tipSize.y)},
		};

		vector<uint16_t> indices =
		{
			0,1,2,
			2,1,3,
		};

		auto drawComp = AddComponent<PCTStaticDraw>();
		drawComp->CreateOriginalMesh<VertexPositionColorTexture>(m_vertices, indices);
		drawComp->SetOriginalMeshUse(true);

		///�e�N�X�`���̎擾�A�\��t��
		auto &app = App::GetApp();
		auto texDir = app->GetDataDirWString();

		//�A���t�@�l��L���ɂ���
		drawComp->SetTextureResource(m_textureName);
		this->SetAlphaActive(true);

		float Layer = m_position.z * (-1.0f);
		SetDrawLayer((int)Layer);
	}

	//�摜�T�C�Y��ς�����`�揈��
	void ObjectBase::DrawingImage(wstring texStr, Vec2 imageSize) {
		m_textureName = texStr;
		Col4 color(1, 1, 1, 1);
		float maxTipSize = 1.0f;
		float mimTipSize = 0.0f;

		m_vertices =
		{
			{Vec3(-imageSize.x,+imageSize.y,0.0f),color,Vec2(mimTipSize,mimTipSize)},
			{Vec3(+imageSize.x,+imageSize.y,0.0f),color,Vec2(maxTipSize,mimTipSize)},
			{Vec3(-imageSize.x,-imageSize.y,0.0f),color,Vec2(mimTipSize,maxTipSize)},
			{Vec3(+imageSize.x,-imageSize.y,0.0f),color,Vec2(maxTipSize,maxTipSize)},
		};

		vector<uint16_t> indices =
		{
			0,1,2,
			2,1,3,
		};

		auto drawComp = AddComponent<PCTStaticDraw>();
		drawComp->CreateOriginalMesh<VertexPositionColorTexture>(m_vertices, indices);
		drawComp->SetOriginalMeshUse(true);

		///�e�N�X�`���̎擾�A�\��t��
		auto &app = App::GetApp();
		auto texDir = app->GetDataDirWString();

		//�A���t�@�l��L���ɂ���
		drawComp->SetTextureResource(m_textureName);
		this->SetAlphaActive(true);

		float Layer = m_position.z * (-1.0f);
		SetDrawLayer((int)Layer);
	}

}
//end basecross

/*!
@file ObjectBase.h
@brief �I�u�W�F�N�g�̐e�N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ObjectBase : public GameObject {
		vector<VertexPositionColorTexture> m_vertices;
		wstring m_textureName;


	public:
		const Vec3& m_rotation;
		const Vec3& m_scale;
		const Vec3& m_position;

		ObjectBase(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& scale,
			Vec3& position);

		//�Z�b�^�[
		//�͂����e�N�X�`�����w��
		void SetTexture(wstring texStr) {
			m_textureName = texStr;
			auto drawComp = AddComponent<PCTStaticDraw>();
			drawComp->SetTextureResource(m_textureName);

		};

		//�e�N�X�`���𒣂�t����
		void DrawingImage(wstring texStr);

	};
}

//end basecross

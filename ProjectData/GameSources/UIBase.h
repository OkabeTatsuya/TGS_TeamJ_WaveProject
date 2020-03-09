/*!
@file ObjectBase.h
@brief �I�u�W�F�N�g�̐e�N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class UIBase : public GameObject {
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;
		wstring m_textureName;

	public:
		const Vec3& m_rotation;
		const Vec3& m_scale;
		const Vec3& m_position;

		UIBase(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& scale,
			Vec2& position,
			float& layer);

		//�Z�b�^�[
		//�͂����e�N�X�`�����w��
		void SetTexture(wstring texStr) {
			m_textureName = texStr;
		};

		//�e�N�X�`���𒣂�t����
		void DrawingImage();

		virtual void OnCreate() override;

	};
}

//end basecross

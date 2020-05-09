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
		Vec3 m_rotation;
		Vec3 m_scale;
		Vec2 m_position;
		float m_layer;

		UIBase(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& scale,
			Vec2& position,
			float layer,
			wstring tex);

		//�͂����e�N�X�`�����w��
		void ResetTexture(wstring texStr);

		//�e�N�X�`���𒣂�t����
		void DrawingImage();

		//�g�����X�t�H�[����ݒ�
		void InitializeTransfrom();

		virtual void OnCreate() override;

	};
}

//end basecross

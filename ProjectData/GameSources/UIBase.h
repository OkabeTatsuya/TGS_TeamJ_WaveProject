/*!
@file ObjectBase.h
@brief オブジェクトの親クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class UIBase : public GameObject {
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;

	public:
		Vec3 m_rotation;
		Vec3 m_scale;
		Vec2 m_position;
		float m_layer;
		wstring m_textureName;

		UIBase(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& scale,
			Vec2& position,
			float layer,
			wstring tex);

		//はりつけるテクスチャを指定
		void ResetTexture(wstring texStr);

		//テクスチャを張り付ける
		void DrawingImage();

		//トランスフォームを設定
		void InitializeTransfrom();

		virtual void OnCreate() override;

	};
}

//end basecross

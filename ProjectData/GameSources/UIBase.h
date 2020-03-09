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

		//セッター
		//はりつけるテクスチャを指定
		void SetTexture(wstring texStr) {
			m_textureName = texStr;
		};

		//テクスチャを張り付ける
		void DrawingImage();

		virtual void OnCreate() override;

	};
}

//end basecross

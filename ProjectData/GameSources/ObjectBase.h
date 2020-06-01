/*!
@file ObjectBase.h
@brief オブジェクトの親クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ObjectBase : public GameObject {
	protected:
		vector<VertexPositionColorTexture> m_vertices;
		wstring m_textureName;

	public:
		Vec3 m_rotation;
		Vec3 m_scale;
		Vec3 m_position;
		int m_layer;

		ObjectBase(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& scale,
			Vec3& position,
			int& Layer);

		ObjectBase(const shared_ptr<Stage>& stage,
			Vec3& rotation,
			Vec3& scale,
			Vec3& position);

		//セッター
		//はりつけるテクスチャを指定
		void SetTexture(wstring texStr) {
			m_textureName = texStr;
			auto drawComp = AddComponent<PCTStaticDraw>();
			drawComp->SetTextureResource(m_textureName);
		};

		//テクスチャを張り付ける
		void DrawingImage(wstring texStr);

		//テクスチャを張り付ける
		void DrawingImage(wstring texStr, Vec2 imageSize);

		void CreateDrawString();

		void DrawStrings();
	};
}

//end basecross

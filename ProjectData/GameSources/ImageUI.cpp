/*!
@file Character.cpp
@brief スコアUIの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	ImageUI::ImageUI(const shared_ptr<Stage>& stage,
		Vec3& rotation,
		Vec3& scale,
		Vec2& position,
		float& layer,
		wstring tex):
		UIBase(stage, rotation,
			scale,
			position,
			layer,
			tex)
	{}

	void ImageUI::OnCreate() {
		DrawingImage();
		InitializeTransfrom();
	}

	void ImageUI::ChangeImage(wstring tex) {
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

		// テクスチャの貼り付け
		auto drawComp = GetComponent<PCTSpriteDraw>();
		//drawComp->SetSamplerState(SamplerState::LinearWrap);

		///テクスチャの取得、貼り付け
		drawComp->SetTextureResource(tex);
		this->SetAlphaActive(true);
	}
}
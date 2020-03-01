/*!
@file ObjectBase.cpp
@brief ゲームオブジェクト親クラスの実態
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
		//エラーが起きないよう初期化
		m_textureName = L"trace.png";
	}

	void ObjectBase::DrawingImage() {
		Col4 color(1, 1, 1, 1);
		Vec2 tipSize = Vec2(1.0f, 1.0f);

		m_vertices =
		{
			{Vec3(-0.1f,+0.1f,0.0f),color,Vec2(0		,0)},
			{Vec3(+0.1f,+0.1f,0.0f),color,Vec2(tipSize.x,0)},
			{Vec3(-0.1f,-0.1f,0.0f),color,Vec2(0		,tipSize.y)},
			{Vec3(+0.1f,-0.1f,0.0f),color,Vec2(tipSize.x,tipSize.y)},
		};

		vector<uint16_t> indices =
		{
			0,1,2,
			2,1,3,
		};

		auto drawComp = AddComponent<PCTStaticDraw>();
		drawComp->CreateOriginalMesh<VertexPositionColorTexture>(m_vertices, indices);
		drawComp->SetOriginalMeshUse(true);

		///テクスチャの取得、貼り付け
		auto &app = App::GetApp();
		auto texDir = app->GetDataDirWString();

		drawComp->SetTextureResource(m_textureName);
		this->SetAlphaActive(true);
	}

	void ObjectBase::OnCreate() {
		DrawingImage();
	}

}
//end basecross

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
		Vec3& position,
		int& layer) :
	GameObject(stage),
		m_rotation(rotation),
		m_scale(scale),
		m_position(position),
		m_layer(layer)
	{
		//�G���[���N���Ȃ��悤������
		m_textureName = L"ScoreUP1.png";
	}

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
		m_textureName = L"ScoreUP1.png";
		m_layer = 1;
	}

	void ObjectBase::DrawingImage(wstring texStr) {
        m_textureName = texStr;
		Col4 color(1, 1, 1, 1);
		Vec2 tipSize = Vec2(1.0f, 1.0f);

		m_vertices =
		{
			{Vec3(-1.0f,+1.0f,0.0f),color,Vec2(0		,0)},
			{Vec3(+1.0f,+1.0f,0.0f),color,Vec2(tipSize.x,0)},
			{Vec3(-1.0f,-1.0f,0.0f),color,Vec2(0		,tipSize.y)},
			{Vec3(+1.0f,-1.0f,0.0f),color,Vec2(tipSize.x,tipSize.y)},
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

		SetDrawLayer(m_layer);
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
		drawComp->SetSamplerState(SamplerState::PointWrap);
		drawComp->CreateOriginalMesh<VertexPositionColorTexture>(m_vertices, indices);
		drawComp->SetOriginalMeshUse(true);

		///�e�N�X�`���̎擾�A�\��t��
		auto &app = App::GetApp();
		auto texDir = app->GetDataDirWString();

		//�A���t�@�l��L���ɂ���
		drawComp->SetTextureResource(m_textureName);
		this->SetAlphaActive(true);

		SetDrawLayer(m_layer);

	}

	void ObjectBase::CreateDrawString() {
		//�����������
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));
	}

	//������̕\��
	void ObjectBase::DrawStrings() {

		//������\��
		wstring strMess(L"�o�C�i���f�[�^\n");
		//�I�u�W�F�N�g��
		auto ObjCount = GetStage()->GetGameObjectVec().size();
		wstring  strObjCount(L"");
		auto bodyCount = GameManager::GetInstance().GetSaveScore();

		for (int i = 0; i < bodyCount.size(); i++) {
			strObjCount += L"�X�e�[�W";
			strObjCount += 
				Util::FloatToWStr((float)i, 1, Util::FloatModify::Fixed) + L"�F"
				+ Util::FloatToWStr((float)bodyCount[i], 1, Util::FloatModify::Fixed) + L",\t";
			strObjCount += L"\n";
		}


		wstring str = strMess + strObjCount;
		//�����������
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);
	}

}
//end basecross
